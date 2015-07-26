#include "OcciWrapper/Connection.h"
#include <iostream>
using namespace std;

occiwrapper::Connection* occiwrapper::Connection::CreateConnection( shared_ptr< occiwrapper::Environment > pParmEnviroment, const ConnectionInfo& connInfo )
{
	return new Connection( pParmEnviroment, connInfo );
}

oracle::occi::Environment* occiwrapper::Connection::GetEnvirnment()
{
	return this->m_pEnviroment->GetEnvirnment();
}

oracle::occi::Statement* occiwrapper::Connection::CreateStatement( const string strSql /*= "" */ )
{
	try
	{
		oracle::occi::Statement* p = NULL;
		if( m_eValidity == VALID && m_pEnviroment->m_eValidity == VALID && m_pOcciConnection )
		{
			p = m_pOcciConnection->createStatement( strSql.c_str() );
		}
		return p;
	}
	catch ( oracle::occi::SQLException exc )
	{
		stringstream ss;
		ss << "create statement failed," << exc.what();
		m_strErrMsg = ss.str();
	}
	catch( ... )
	{
		m_strErrMsg = "create statement failed, unknown exception.";
	}
	return NULL;
}

bool occiwrapper::Connection::TerminateStatement( oracle::occi::Statement* pOcciStat )
{
	try
	{
		if( m_eValidity == VALID && m_pEnviroment->m_eValidity == VALID && m_pOcciConnection )
		{
			if( pOcciStat != NULL )
			{
				this->m_pOcciConnection->terminateStatement( pOcciStat );
				return true;
			}
		}
	}
	catch ( oracle::occi::SQLException exc )
	{
		stringstream ss;
		ss << "terminate statement failed," << exc.what();
		m_strErrMsg = ss.str();
	}
	catch( ... )
	{
		m_strErrMsg = "terminate statement failed, unknown exception.";
		
	}
	return false;
	
}

bool occiwrapper::Connection::Commit()
{
	try
	{
		if( m_eValidity == VALID && m_pEnviroment->m_eValidity == VALID && m_pOcciConnection )
		{
			this->m_pOcciConnection->commit();
			return true;
		}
	}
	catch ( oracle::occi::SQLException exc )
	{
		stringstream ss;
		ss << "commit failed, failed," << exc.what();
		m_strErrMsg = ss.str();
		return false;
	}
	catch( ... )
	{
		m_strErrMsg = "commit failed, unknown exception.";
	}
	return false;
}

bool occiwrapper::Connection::Rollback()
{
	try
	{
		if( m_eValidity == VALID && m_pEnviroment->m_eValidity == VALID && m_pOcciConnection )
		{
			this->m_pOcciConnection->rollback();
		}
		return true;
	}
	catch ( oracle::occi::SQLException exc )
	{
		stringstream ss;
		ss << "rollback failed," << exc.what();
		m_strErrMsg = ss.str();
		return false;
	}
	catch( ... )
	{
		m_strErrMsg = "rollback failed, unknown exception.";
	}
	return false;
}

occiwrapper::Connection::~Connection()
{
	//close occiConnection
	if( m_eValidity == VALID && m_pEnviroment->m_eValidity == VALID && m_pOcciConnection )
	{
		try
		{
			m_pEnviroment->m_pOcciEnviroment->terminateConnection( this->m_pOcciConnection );
			//this->m_eValidity = INVALID;
			this->m_pOcciConnection = NULL;
		}
		catch (oracle::occi::SQLException exc)
		{
			stringstream ss;
			ss << "terminate connection failed," << exc.what();
			m_strErrMsg = ss.str();
		}
		catch( ... ) 
		{
			m_strErrMsg = "terminate connection unknown exception";
		}
	}
}

occiwrapper::Validity occiwrapper::Connection::GetValidity()
{
	return this->m_eValidity;
}

string occiwrapper::Connection::GetErrMsg()
{
	return m_strErrMsg;
}

occiwrapper::Connection::Connection( shared_ptr< occiwrapper::Environment >& pParmEnviroment, const ConnectionInfo& connInfo )
{
	this->m_eValidity = INVALID;
	m_objConnInfo = connInfo;
	this->m_pEnviroment = shared_ptr< occiwrapper::Environment >( pParmEnviroment );
	if( m_pEnviroment->m_pOcciEnviroment != NULL )
	{
		stringstream ss;
		ss<< m_objConnInfo.ip << "/" << m_objConnInfo.sid << ":" << m_objConnInfo.port;
		try
		{
			m_pOcciConnection = m_pEnviroment->m_pOcciEnviroment->createConnection( m_objConnInfo.username, m_objConnInfo.password, ss.str() );
			if( m_pOcciConnection )
			{
				this->m_eValidity = VALID;
			}
		}
		catch( oracle::occi::SQLException exc )
		{
			stringstream ss;
			ss << "connection database," << m_objConnInfo.GetHashString() << " failed," << exc.what();
			m_strErrMsg = ss.str();
		}
		catch( ... )
		{
			stringstream ss;
			ss << "connection database," << m_objConnInfo.GetHashString() << " failed, unknown exception";
			m_strErrMsg = ss.str();
		}
	}
}

oracle::occi::Connection* occiwrapper::Connection::GetOcciConnection()
{
	return m_pOcciConnection;
}

