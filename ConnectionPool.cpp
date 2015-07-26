#include "OcciWrapper/ConnectionPool.h"
#include "OcciWrapper/Common.h"
#include <iostream>

occiwrapper::ConnectionPool::ConnectionPool( string strCharset, string strNCharset )
{
	m_pEnviroment = shared_ptr< occiwrapper::Environment >( occiwrapper::Environment::CreateEnvironment( strCharset, strNCharset ) );
}

occiwrapper::ConnectionPool::~ConnectionPool()
{
	this->m_mapConnection.clear();
}

shared_ptr< occiwrapper::Connection > occiwrapper::ConnectionPool::GetConnection( const occiwrapper::ConnectionInfo& connInfo )
{
	//find in connectionMap
	string key = connInfo.GetHashString();
	map< string, shared_ptr< Connection > >::iterator it = m_mapConnection.find( key );
	if( it == m_mapConnection.end() )
	{
		shared_ptr< Connection > tempConn( Connection::CreateConnection( m_pEnviroment, connInfo ) );
		if( tempConn )
		{
			m_mapConnection.insert( make_pair( connInfo.GetHashString(), tempConn ) );
			return tempConn;
		}
		else
		{
			return shared_ptr< Connection >( );
		}
	}
	return it->second;
}

shared_ptr< occiwrapper::Connection > occiwrapper::ConnectionPool::GetConnection( const string& strIp /*= "127.0.0.1"*/, const UInt32& nPort /*= 1521*/, const string& strUserName /*= "sa"*/, const string& strPassword /*= "sa"*/, const string& strSid /*= "orcl" */ )
{
	occiwrapper::ConnectionInfo info( strIp, nPort, strUserName, strPassword, strSid );
	return GetConnection( info );
}

size_t occiwrapper::ConnectionPool::GetConnMapSize()
{
	return this->m_mapConnection.size();
}