#pragma once
#include <string>

class Buffer {
public:
    virtual void append(const Buffer &buffer) = 0;
    virtual void append(const Buffer *buffer) = 0;
    virtual void append(const char *buf, size_t length) = 0;
    virtual void append(const char *buf) = 0;
    virtual const char* buf() const = 0;
    virtual size_t size() const = 0;
    virtual bool is_empty() const = 0;
    virtual Buffer *subbuf(size_t start, size_t end) const = 0;
    virtual Buffer *first(size_t count) const = 0;
    virtual Buffer *last(size_t count) const = 0;
    virtual void drop_first(size_t count) = 0;
    virtual void drop_last(size_t count) = 0;
    virtual char at(size_t index) const = 0;
    virtual Buffer & operator+=(const Buffer &another) = 0;
    virtual Buffer & operator+=(const Buffer *another) = 0;
    virtual char operator[](size_t index) const = 0;
    virtual void clear() = 0;
    virtual operator std::string() const = 0;
    virtual std::string toStr() = 0; // for fut upd

    virtual ~Buffer() {
    }
};
