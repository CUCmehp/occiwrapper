#include "Environment.h"
#include "ConnectionInfo.h"
#include <assert.h>

/***
*	@brief: this function test how to create Environment
*	@add by CUCmehp, since 2012-07-09
*/
void TestEnviroment()
{
	assert( occiwrapper::Environment::CreateEnvironment() != NULL );
}
