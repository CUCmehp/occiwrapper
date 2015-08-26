### src/bar/Makefile.am ###
lib_LTLIBRARIES=libocciwrapper.la
libocciwrapper_la_LDFLAGS = -version-info 1:5:0    #current:revision:age
libocciwrapper_la_SOURCES=AbstractBinder.cpp AbstractExtraction.cpp Common.cpp ConnectionInfo.cpp Environment.cpp Limit.cpp SessionFactory.cpp StatementImpl.cpp AbstractBinding.cpp Binder.cpp Connection.cpp ConnectionPool.cpp Extractor.cpp Session.cpp Statement.cpp BinaryReader.cpp BinaryWriter.cpp BlobStream.cpp Lob.cpp LobBase.cpp
libocciwrapperincludedir=$(includedir)/OcciWrapper
#libocciwrapperinclude_HEADERS=AbstractBinder.h AbstractExtraction.h Binder.h Common.h ConnectionInfo.h Environment.h Extraction.h Limit.h SessionFactory.h Statement.h Type.h AbstractBinding.h AbstractExtractor.h Binding.h Connection.h ConnectionPool.h Exception.h Extractor.h OcciWrapper.h Session.h StatementImpl.h TypeHandler.h BinaryReader.h BinaryWriter.h BlobStream.h Lob.h LobBase.h
libocciwrapperinclude_HEADERS=$(top_srcdir)/include/OcciWrapper/*.h
#AM_CPPFLAGS=-std=c++11
#AM_CPPFLAGS=-std=c++0x
AM_CPPFLAGS=-std=gnu++0x
SUBDIRS=. test
INCLUDES=-I$(top_srcdir) -I$(top_srcdir)/include -I/usr/local/instantclient_11_2/sdk/include/
