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
	${OBJECTDIR}/src/http_auth.o \
	${OBJECTDIR}/src/http_client.o \
	${OBJECTDIR}/src/options.o \
	${OBJECTDIR}/src/pam_account.o \
	${OBJECTDIR}/src/pam_auth.o \
	${OBJECTDIR}/src/pam_password.o \
	${OBJECTDIR}/src/pam_session.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f3 \
	${TESTDIR}/TestFiles/f1

# Test Object Files
TESTOBJECTFILES= \
	${TESTDIR}/tests/gtest_main.o \
	${TESTDIR}/tests/http_auth_test.o \
	${TESTDIR}/tests/http_client_test.o \
	${TESTDIR}/tests/options_test.o

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
LDLIBSOPTIONS=-lcurl

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libpam-http.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libpam-http.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libpam-http.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/http_auth.o: src/http_auth.c
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -g -DDEBUG -Iinclude -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/http_auth.o src/http_auth.c

${OBJECTDIR}/src/http_client.o: src/http_client.c
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -g -DDEBUG -Iinclude -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/http_client.o src/http_client.c

${OBJECTDIR}/src/options.o: src/options.c
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -g -DDEBUG -Iinclude -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/options.o src/options.c

${OBJECTDIR}/src/pam_account.o: src/pam_account.c
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -g -DDEBUG -Iinclude -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/pam_account.o src/pam_account.c

${OBJECTDIR}/src/pam_auth.o: src/pam_auth.c
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -g -DDEBUG -Iinclude -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/pam_auth.o src/pam_auth.c

${OBJECTDIR}/src/pam_password.o: src/pam_password.c
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -g -DDEBUG -Iinclude -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/pam_password.o src/pam_password.c

${OBJECTDIR}/src/pam_session.o: src/pam_session.c
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -g -DDEBUG -Iinclude -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/pam_session.o src/pam_session.c

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-tests-subprojects .build-conf ${TESTFILES}
.build-tests-subprojects:

${TESTDIR}/TestFiles/f3: ${TESTDIR}/tests/gtest_main.o ${TESTDIR}/tests/http_auth_test.o ${TESTDIR}/tests/http_client_test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f3 $^ ${LDLIBSOPTIONS} -pthread  -Lexternal/googletest/googletest -lgtest -lpam -lpam_misc -Lexternal/httpmockserver/build/src -lhttpmockserver -lmicrohttpd -lcurl 

${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/options_test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} -pthread  -Lexternal/googletest/googletest -lgtest -lpam -lpam_misc 


${TESTDIR}/tests/gtest_main.o: tests/gtest_main.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -Iexternal/googletest/googletest/include -I. -Iexternal/httpmockserver/include -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/gtest_main.o tests/gtest_main.cpp


${TESTDIR}/tests/http_auth_test.o: tests/http_auth_test.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -Iexternal/googletest/googletest/include -I. -Iexternal/httpmockserver/include -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/http_auth_test.o tests/http_auth_test.cpp


${TESTDIR}/tests/http_client_test.o: tests/http_client_test.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -Iexternal/googletest/googletest/include -I. -Iexternal/httpmockserver/include -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/http_client_test.o tests/http_client_test.cpp


${TESTDIR}/tests/options_test.o: tests/options_test.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -Iexternal/googletest/googletest/include -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/options_test.o tests/options_test.cpp


${OBJECTDIR}/src/http_auth_nomain.o: ${OBJECTDIR}/src/http_auth.o src/http_auth.c 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/http_auth.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -DDEBUG -Iinclude -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/http_auth_nomain.o src/http_auth.c;\
	else  \
	    ${CP} ${OBJECTDIR}/src/http_auth.o ${OBJECTDIR}/src/http_auth_nomain.o;\
	fi

${OBJECTDIR}/src/http_client_nomain.o: ${OBJECTDIR}/src/http_client.o src/http_client.c 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/http_client.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -DDEBUG -Iinclude -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/http_client_nomain.o src/http_client.c;\
	else  \
	    ${CP} ${OBJECTDIR}/src/http_client.o ${OBJECTDIR}/src/http_client_nomain.o;\
	fi

${OBJECTDIR}/src/options_nomain.o: ${OBJECTDIR}/src/options.o src/options.c 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/options.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -DDEBUG -Iinclude -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/options_nomain.o src/options.c;\
	else  \
	    ${CP} ${OBJECTDIR}/src/options.o ${OBJECTDIR}/src/options_nomain.o;\
	fi

${OBJECTDIR}/src/pam_account_nomain.o: ${OBJECTDIR}/src/pam_account.o src/pam_account.c 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/pam_account.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -DDEBUG -Iinclude -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/pam_account_nomain.o src/pam_account.c;\
	else  \
	    ${CP} ${OBJECTDIR}/src/pam_account.o ${OBJECTDIR}/src/pam_account_nomain.o;\
	fi

${OBJECTDIR}/src/pam_auth_nomain.o: ${OBJECTDIR}/src/pam_auth.o src/pam_auth.c 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/pam_auth.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -DDEBUG -Iinclude -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/pam_auth_nomain.o src/pam_auth.c;\
	else  \
	    ${CP} ${OBJECTDIR}/src/pam_auth.o ${OBJECTDIR}/src/pam_auth_nomain.o;\
	fi

${OBJECTDIR}/src/pam_password_nomain.o: ${OBJECTDIR}/src/pam_password.o src/pam_password.c 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/pam_password.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -DDEBUG -Iinclude -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/pam_password_nomain.o src/pam_password.c;\
	else  \
	    ${CP} ${OBJECTDIR}/src/pam_password.o ${OBJECTDIR}/src/pam_password_nomain.o;\
	fi

${OBJECTDIR}/src/pam_session_nomain.o: ${OBJECTDIR}/src/pam_session.o src/pam_session.c 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/pam_session.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -DDEBUG -Iinclude -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/pam_session_nomain.o src/pam_session.c;\
	else  \
	    ${CP} ${OBJECTDIR}/src/pam_session.o ${OBJECTDIR}/src/pam_session_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f3 || true; \
	    ${TESTDIR}/TestFiles/f1 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
