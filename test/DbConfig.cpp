#include "DbConfig.h"


test_db_config::DbConfig::DbConfig()
{
	m_pConf = new common::Config( "db_config.ini" );
	m_strIp = "";
	m_strPassword = "";
	m_strSid = "";
	m_strUserName = "";
}

bool test_db_config::DbConfig::Init()
{
	if( m_pConf->valid() )
	{
		m_strIp = m_pConf->getProperty( "ip" );
		m_strUserName = m_pConf->getProperty( "username" );
		m_strPassword = m_pConf->getProperty( "password" );
		m_strSid = m_pConf->getProperty( "sid" );
		return true;
	}
	else
	{
		return false;
	}
}

test_db_config::DbConfig::~DbConfig()
{
	delete m_pConf;
}

string test_db_config::DbConfig::GetStrIp()
{
	return m_strIp;
}

string test_db_config::DbConfig::GetUserName()
{
	return m_strUserName;
}

string test_db_config::DbConfig::GetPassword()
{
	return m_strPassword;
}

string test_db_config::DbConfig::GetSid()
{
	return m_strSid;
}