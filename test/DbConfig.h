#pragma once
#include "DbConfig.h"
#include "Config.h"

namespace test_db_config
{
	class DbConfig
	{
	public:
		/***
		*	@init a DbConfig object
		*/
		DbConfig();

		/***
		*	@destroy DbConfig object
		*/
		~DbConfig();

		/***
		*	@init config
		*/
		bool Init();

		/***
		*	@get ip address
		*/
		string GetStrIp();

		/***
		*	@brief: get user name of oracle database
		*/
		string GetUserName();

		/***
		*	@brief: get password for oracle user
		*/
		string GetPassword();

		/***
		*	@brief: get oracle sid
		*/
		string GetSid();

	private:
		common::Config*			m_pConf;
		string					m_strIp;
		string					m_strUserName;
		string					m_strPassword;
		string					m_strSid;
	};
}
