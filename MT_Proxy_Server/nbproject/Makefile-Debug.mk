#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Cache.o \
	${OBJECTDIR}/CacheEntry.o \
	${OBJECTDIR}/Client.o \
	${OBJECTDIR}/Downloader.o \
	${OBJECTDIR}/config.o \
	${OBJECTDIR}/libs/CondVar/CondVar.o \
	${OBJECTDIR}/libs/HTTPURIParser/HTTPURIParser.o \
	${OBJECTDIR}/libs/Logger/Logger.o \
	${OBJECTDIR}/libs/Mutex/Mutex.o \
	${OBJECTDIR}/libs/TCPSocket/TCPSocket.o \
	${OBJECTDIR}/libs/Thread/Thread.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lpthread

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mt_proxy_server

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mt_proxy_server: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mt_proxy_server ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Cache.o: Cache.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Cache.o Cache.cpp

${OBJECTDIR}/CacheEntry.o: CacheEntry.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CacheEntry.o CacheEntry.cpp

${OBJECTDIR}/Client.o: Client.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Client.o Client.cpp

${OBJECTDIR}/Downloader.o: Downloader.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Downloader.o Downloader.cpp

${OBJECTDIR}/config.o: config.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/config.o config.cpp

${OBJECTDIR}/libs/CondVar/CondVar.o: libs/CondVar/CondVar.cpp 
	${MKDIR} -p ${OBJECTDIR}/libs/CondVar
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libs/CondVar/CondVar.o libs/CondVar/CondVar.cpp

${OBJECTDIR}/libs/HTTPURIParser/HTTPURIParser.o: libs/HTTPURIParser/HTTPURIParser.cpp 
	${MKDIR} -p ${OBJECTDIR}/libs/HTTPURIParser
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libs/HTTPURIParser/HTTPURIParser.o libs/HTTPURIParser/HTTPURIParser.cpp

${OBJECTDIR}/libs/Logger/Logger.o: libs/Logger/Logger.cpp 
	${MKDIR} -p ${OBJECTDIR}/libs/Logger
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libs/Logger/Logger.o libs/Logger/Logger.cpp

${OBJECTDIR}/libs/Mutex/Mutex.o: libs/Mutex/Mutex.cpp 
	${MKDIR} -p ${OBJECTDIR}/libs/Mutex
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libs/Mutex/Mutex.o libs/Mutex/Mutex.cpp

${OBJECTDIR}/libs/TCPSocket/TCPSocket.o: libs/TCPSocket/TCPSocket.cpp 
	${MKDIR} -p ${OBJECTDIR}/libs/TCPSocket
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libs/TCPSocket/TCPSocket.o libs/TCPSocket/TCPSocket.cpp

${OBJECTDIR}/libs/Thread/Thread.o: libs/Thread/Thread.cpp 
	${MKDIR} -p ${OBJECTDIR}/libs/Thread
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libs/Thread/Thread.o libs/Thread/Thread.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mt_proxy_server

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
