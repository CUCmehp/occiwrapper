#include "Environment.h"
#include "Connection.h"
#include "ConnectionInfo.h"
#include "ConnectionPool.h"
#include <assert.h>
#include "DbConfig.h"


/***
*	@brief: this function test occiwrapper's connection management.
*	@add by CUCmehp, since 2012-07-09
*/
void TestConnectionPool()
{
	occiwrapper::ConnectionInfo info;
	occiwrapper::ConnectionPool connPool;
	test_db_config::DbConfig config;
	assert( config.Init() );
	info.ip = config.GetStrIp();
	info.username = config.GetUserName();
	info.password = config.GetPassword();
	info.sid = config.GetSid();

	shared_ptr< occiwrapper::Connection > p = connPool.GetConnection( info );
	assert( p != NULL);
	assert( p->GetValidity() == occiwrapper::VALID );
	shared_ptr< occiwrapper::Connection > other = connPool.GetConnection( info );
	assert( connPool.GetConnMapSize() == 1 );
}
