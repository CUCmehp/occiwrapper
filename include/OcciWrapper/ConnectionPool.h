#pragma once
#include <sstream>
#include <string>
#include <map>
#include "OcciWrapper/Connection.h"
#include "OcciWrapper/ConnectionInfo.h"

using namespace std;
//using namespace stdext;

namespace occiwrapper
{
	/*
	* @brief: save all oracle connection in a connection pool
	* @add by CUCmehp
	*/
	class __OCCI_WRAPPER_API ConnectionPool
	{
	public:
		/***
		*	@brief: create a connection pool
		*	@add by CUCmehp
		*/
		ConnectionPool( string strCharset = "", string strNCharset = "" );

		/***
		*	@brief: destroyed connection pool
		*/
		~ConnectionPool();

	public:

		/***
		*	@brief: get connection from pool
		*	@add by CUCmehp
		*	@parameters:
		*		connInfo: connection information
		*	@return:
		*		return the Connection, if the connection is saved in the pool, return the one saved for reusing.
		*		else then created the connection, return share_ptr< Connection >() for failed.
		*/
		shared_ptr< Connection > GetConnection( const ConnectionInfo& connInfo );

		/***
		*	@brief: get connection from pool
		*	@add by CUCmehp
		*	@parameters:
		*		strIp: ip address
		*		nPort: port
		*		strUserName: user name
		*		strPassword: password
		*		strSid: oracle sid
		*	@return:
		*		return the Connection, if the connection is saved in the pool, return the one saved for reusing.
		*		else then created the connection, return share_ptr< Connection >() for failed.
		*/
		shared_ptr< Connection > GetConnection( const string& strIp = "127.0.0.1", const UInt32& nPort = 1521, const string& strUserName = "sa", const string& strPassword = "sa", const string& strSid = "orcl" );

		/***
		*	@brief: get connection map size
		*	@return:
		*		return connection map size.
		*/
		size_t GetConnMapSize();

	private:
		//occi environment
		shared_ptr< Environment > m_pEnviroment;

		//occi connection map
		map< string, shared_ptr< Connection > > m_mapConnection;
	};
}