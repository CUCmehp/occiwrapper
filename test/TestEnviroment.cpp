#include "OcciWrapper/Environment.h"
#include "OcciWrapper/ConnectionInfo.h"
#include <assert.h>
#include <iostream>

/***
*	@brief: this function test how to create Environment
*	@add by CUCmehp, since 2012-07-09
*/
void TestEnviroment()
{
	assert( occiwrapper::Environment::CreateEnvironment() != NULL );
	string strErrMsg = "";
}
