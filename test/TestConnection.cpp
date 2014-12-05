#include "OcciWrapper/Environment.h"
#include "OcciWrapper/Connection.h"
#include "OcciWrapper/ConnectionInfo.h"
#include <assert.h>
#include "DbConfig.h"


/***
*	@brief: this function test how to create an oracle connection.
*	@add by CUCmehp, since 2012-07-09
*/
void TestCreateConnection()
{
	shared_ptr< occiwrapper::Environment > pEnv = occiwrapper::Environment::CreateEnvironment();
	assert( pEnv->CreateEnvironment() != NULL );

	//#define TEST_UNEXIST_CONNECTTION
#ifdef TEST_UNEXIST_CONNECTTION
	occiwrapper::ConnectionInfo not_exist_info;
	not_exist_info.ip = "192.168.92.122";			// 该IP上没有server
	assert( occiwrapper::Connection::CreateConnection( shared_ptr< occiwrapper::Environment >( pEnv ), not_exist_info ) == NULL );
#endif

	occiwrapper::ConnectionInfo info;
	test_db_config::DbConfig config;
	bool bRet = config.Init();
	assert( bRet );
	info.ip = config.GetStrIp();
	info.username = config.GetUserName();
	info.password = config.GetPassword();
	info.sid = config.GetSid();
	{
		shared_ptr< occiwrapper::Connection > pConn1( occiwrapper::Connection::CreateConnection( shared_ptr< occiwrapper::Environment >( pEnv ), info ) );
	}
	{
		shared_ptr< occiwrapper::Connection > pConn2( occiwrapper::Connection::CreateConnection( shared_ptr< occiwrapper::Environment >( pEnv ), info ) );
	}
}
