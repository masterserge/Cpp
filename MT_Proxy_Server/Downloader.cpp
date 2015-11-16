#include "Downloader.h"

#include "libs/Thread/Thread.h"
#include "Cache.h"
#include <sstream>
#include <string> // upd
#include <iostream> // upd

Downloader::Downloader(CacheEntry* cache_entry) {
    try {
        _sock = new TCPSocket();
        _in = new VectorBuffer();
        _out = new VectorBuffer();
        _ce = cache_entry;
    } catch (SocketException &ex) {
        Logger::error("Downloader::Downlaoder() SocketException: %s", ex.what());
        throw;
    }
}

Downloader::~Downloader() {
    delete _in;
    delete _out;
    if (!_sock->is_closed())
        _sock->close();
    delete _sock;
}

Downloader * Downloader::dummy_downloader() {
    static Downloader d(NULL);
    return &d;
}

void Downloader::close_delete_exit() {
    _sock->close();
    delete this;
    Thread::exit(NULL);
}

void Downloader::remove_or_change_state(CacheEntry::CacheEntryState state) {
    CacheEntry *ce = this->_ce;
    ce->lock();
    ce->remove_downloader();
    if (ce->to_delete()) {
        ce->unlock();
        delete ce;
    } else {
        ce->set_state(state);
        ce->broadcast();
        ce->unlock();
    }
}

void *Downloader::run(void* downloader_ptr) {
    Downloader *d = static_cast<Downloader*> (downloader_ptr);

    CacheEntry *ce = d->_ce;
    Buffer *in = d->_in;
    Buffer *out = d->_out;
    TCPSocket *sock = d->_sock;

    ce->set_downloader(d);
    const BrokenUpHTTPRequest &request = ce->request();

    // forming query to send
    out->append(ce->request().request().c_str(), ce->request().request().size());

    // try to connect
    try {
        Logger::debug("Downloader connecting to %s:%d", request.host().c_str(), request.port());
        sock->connect(request.host(), request.port());
        // if fail -- set Entry status to CON_ERROR
        // and quit
    } catch (ConnectException &ex) {
        Logger::error("Downloader ConnectException: %s", ex.what());
        Cache::drop(request.url());
        d->remove_or_change_state(CacheEntry::CONNECTION_ERROR);
        d->close_delete_exit();
    } catch (DNSException &ex) {
        Logger::error("Downloader DNSException: %s", ex.what());
        Cache::drop(request.url());
        d->remove_or_change_state(CacheEntry::CONNECTION_ERROR);
        d->close_delete_exit();
    }

    // try to send request
    try {
        Logger::debug("Downloader sending request");
        sock->send(out, true);
        out->clear();
        // if fail -- set Entry status to SEND_ERROR
        // and quit
    } catch (SendException &ex) {
        Logger::error("Downloader SendException: %s", ex.what());
        Cache::drop(request.url());
        d->remove_or_change_state(CacheEntry::SEND_ERROR);
        d->close_delete_exit();
    }

    bool response_code_received = false;
    int clients_count = 0;

    while (1) {

        try {
            if (0 == sock->recv(in)) {
                Logger::debug("Downloader finished downloading");

                ce->lock();

                if (response_code_received) {
                    if (ce->get_state() == CacheEntry::CACHING)
                        ce->set_state(CacheEntry::CACHED);
                    else if (ce->get_state() == CacheEntry::DOWNLOADING)
                        ce->set_state(CacheEntry::FINISHED);
                    else
                        assert(false);
                }

                ce->remove_downloader();
                if (ce->to_delete()) {
                    ce->unlock();
                    delete ce;
                } else {
                    ce->broadcast();
                    ce->unlock();
                }

                d->close_delete_exit();

            }
        } catch (RecvException &ex) {
            Logger::error("Downloader RecvException: %s", ex.what());
            Cache::drop(request.url());
            d->remove_or_change_state(CacheEntry::RECV_ERROR);
            d->close_delete_exit();
        }

        ce->lock();
        while ((ce->get_state() == CacheEntry::DOWNLOADING) &&
                (ce->data()->size() > Cache::MAX_CACHE_ENTRY_SIZE) &&
                (ce->clients_count() > 0)) {
            ce->wait();
        }

        ce->add_data(in);
        clients_count = ce->clients_count();

        if (clients_count == 0) {
            Logger::debug("Downloader finishing due to the lack of clients");

            if (ce->get_state() == CacheEntry::CACHING)
                Cache::drop(ce->request().url());

            ce->remove_downloader();
            if (ce->to_delete()) {
                ce->unlock();
                delete ce;
            } else {
                assert(false);
            }

            d->close_delete_exit();
        }

        // TO STRING OP //
        
        std::string tmp = in->toStr();

        size_t s1 = tmp.find("Content-Type: ");

        if(s1 != std::string::npos)
        {
            size_t s2 = tmp.find("\r\n", s1);

            if(s2 != std::string::npos)
            {
                size_t begin = s1 + strlen("Content-Type: ");
                size_t len = s2 - begin;
                std::cout << "MIME type: " << tmp.substr(begin, len) << std::endl; 
            }
        }
        
        // TO STRING OP END //

        in->clear();

        // iCache::size() > Cache::MAX_CACHE_SIZE f CacheEntry exceeds size
        if ((ce->get_state() == CacheEntry::CACHING &&
                (Cache::size() > Cache::MAX_CACHE_SIZE || ce->data()->size() > Cache::MAX_CACHE_ENTRY_SIZE))) {
            Logger::info("Dropping CacheEntry due to size overflow");
            Cache::drop(ce->request().url());
            ce->set_state(CacheEntry::DOWNLOADING);
        }

        // strlen("HTTP/1.x 200") == 12
        if ((response_code_received == false) && (ce->get_state() == CacheEntry::CACHING) && (ce->data()->size() >= 12)) {
            Logger::debug("Downloader analyzing response");
            response_code_received = true;

            std::string response = *(ce->data());
            std::string word1;
            std::string word2;
            std::istringstream iss(response, std::istringstream::in);
            iss >> word1;
            iss >> word2;

            if ((word1 == "HTTP/1.0" || word1 == "HTTP/1.1") && word2 == "200") {
                Logger::debug("Downloader Valid 200 response, caching");
                Logger::info("Caching: code %s", word2.c_str()); // caching code 200
                ce->set_state(CacheEntry::CACHING);
            } else {
                Logger::debug("Downloader dropping due to non 200 response");
                Logger::info("Dropping: code %s", word2.c_str());

                Cache::drop(ce->request().url());
                ce->set_state(CacheEntry::DOWNLOADING);
            }
        }


        ce->broadcast();
        ce->unlock();
    }
}
