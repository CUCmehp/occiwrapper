### src/bar/Makefile.am ###
lib_LTLIBRARIES=libocciwrapper.la
libocciwrapper_la_SOURCES=AbstractBinder.cpp AbstractExtraction.cpp Common.cpp ConnectionInfo.cpp Environment.cpp Limit.cpp SessionFactory.cpp StatementImpl.cpp AbstractBinding.cpp Binder.cpp Connection.cpp ConnectionPool.cpp Extractor.cpp Session.cpp Statement.cpp
libocciwrapperincludedir=$(includedir)/occiwrapper
libocciwrapperinclude_HEADERS=AbstractBinder.h AbstractExtraction.h Binder.h Common.h ConnectionInfo.h Environment.h Extraction.h Limit.h SessionFactory.h Statement.h Type.h AbstractBinding.h AbstractExtractor.h Binding.h Connection.h ConnectionPool.h Exception.h Extractor.h OcciWrapper.h Session.h StatementImpl.h TypeHandler.h
#AM_CPPFLAGS=-std=c++11
#AM_CPPFLAGS=-std=c++0x
AM_CPPFLAGS=-std=gnu++0x
SUBDIRS=. test
INCLUDES=-I$(top_srcdir) -I/u01/install/oracle_client/instantclient_12_1/sdk/include/
