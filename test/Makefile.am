### src/bar/Makefile.am ###
bin_PROGRAMS=test
configdir=$(prefix)/bin
config_DATA=db_config.ini
test_SOURCES=main.cpp TestConnection.cpp TestConnectionPool.cpp TestEnviroment.cpp TestSessionFactory.cpp Config.cpp DbConfig.cpp
#LIBS=-locciwrapper
#AM_CPPFLAGS=-std=c++11
#AM_CPPFLAGS=-std=c++0x
AM_CPPFLAGS=-std=gnu++0x
#AM_LDFLAGS=-locciwrapper
#LDFLAGS=-L/u01/oracle/product/11.2.0/dbhome_1/lib
LDFLAGS=-L$(top_srcdir) -locci -lclntsh -locciwrapper
INCLUDES=-I$(top_srcdir) -I/u01/install/oracle_client/instantclient_12_1/sdk/include/
test_LDFLAGS=-L/u01/install/oracle_client/instantclient_12_1/
