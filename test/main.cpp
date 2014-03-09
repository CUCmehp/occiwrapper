#include "TestConnection.h"
#include "TestConnectionPool.h"
#include "TestEnviroment.h"
#include "TestSessionFactory.h"
#include <iostream>

/***
*	@brief: run all test function.
*		before run all test, you must find a oracle database, and running the script in the direct "db".
*		as the oracle's SID in my computer names "ORCL", if yours are different, please change the sid in all 
*		test file to yours.
*	@add by CUCmehp, since 2012-07-09
*/
int main( int argc, char* argv[] )
{
	std::cout << "start to run all test!" << std::endl;

	// test create oracle environment
	std::cout << "start to run TestEnviroment:" << std::endl;
	TestEnviroment();
	std::cout << "TestEnviroment finish" << std::endl;

	////// test create oracle connection
	std::cout << "start to run TestCreateConnection:" << std::endl;
	TestCreateConnection();
	std::cout << "TestCreateConnection finish" << std::endl;

	////// test connection pool
	std::cout << "start to run TestConnectionPool:" << std::endl;
	TestConnectionPool();
	std::cout << "TestConnectionPool finish" << std::endl;

	// test DDL operation.
	std::cout << "start to run TestDDL:" << std::endl;
	TestDDL();
	std::cout << "TestDDL finish" << std::endl;

	// test insert operation
	std::cout << "start to run TestSimpleInsert:" << std::endl;
	TestSimpleInsert();
	std::cout << "TestSimpleInsert finish" << std::endl;

	// test insert for some times with same session
	std::cout << "start to run TestSimpleInsertTimes:" << std::endl;
	TestSimpleInsertTimes();
	std::cout << "TestSimpleInsertTimes finish" << std::endl;

	// test simple binding
	std::cout << "start to run TestSimpleBinding:" << std::endl;
	TestSimpleBinding();
	std::cout << "TestSimpleBinding finish" << std::endl;

	// test simple binding, execute for many times, with the same session.
	std::cout << "start to run TestSimpleBindingTimes:" << std::endl;
	TestSimpleBindingTimes();
	std::cout << "TestSimpleBindingTimes finish" << std::endl;
	
	// test simple batched bind
	std::cout << "start to run TestSimpleBatchedBind:" << std::endl;
	TestSimpleBatchedBind();
	std::cout << "TestSimpleBatchedBind finish" << std::endl;

	// test batched bind two vector and a vector< tuple >
	std::cout << "start to run TestBindTwoColumns:" << std::endl;
	TestBindTwoColumns();
	std::cout << "TestBindTwoColumns finish" << std::endl;

	// test update operation
	std::cout << "start to run TestUpdate:" << std::endl;
	TestUpdate();
	std::cout << "TestUpdate finish" << std::endl;

	// test deal with date
	std::cout << "start to run TestDate:" << std::endl;
	TestDate();
	std::cout << "TestDate finish" << std::endl;

	// test occiwrapper's commit and rollback operation
	std::cout << "start to run TestRollbackAndCommit:" << std::endl;
	TestRollbackAndCommit();
	std::cout << "TestRollbackAndCommit finish" << std::endl;

	// test occiwrapper's bind tuple, the tuple has another tuple inside.
	std::cout << "start to run TestBindTuple:" << std::endl;
	TestBindTuple();
	std::cout << "TestBindTuple finish" << std::endl;

	// test procedure calling
	std::cout << "start to run TestProcedure:" << std::endl;
	TestProcedure();
	std::cout << "TestProcedure finish" << std::endl;

	// test function calling
	std::cout << "start to run TestFunction:" << std::endl;
	TestFunction();
	std::cout << "TestFunction finish" << std::endl;

	// test function retrieve different value.
	std::cout << "start to run TestFunctionRetrieveAll:" << std::endl;
	TestFunctionRetrieveAll();
	std::cout << "TestFunctionRetrieveAll finish" << std::endl;

	// test function call, pass different values.
	std::cout << "start to run TestFunctionPassIntoAll:" << std::endl;
	TestFunctionPassIntoAll();
	std::cout << "TestFunctionPassIntoAll finish" << std::endl;

	// test select into
	std::cout << "start to run TestBatchedInsertAndSelect:" << std::endl;
	TestBatchedInsertAndSelect();
	std::cout << "TestBatchedInsertAndSelect finish" << std::endl;

	// test select with limit
	std::cout << "start to run TestSelectWithLimit:" << std::endl;
	TestSelectWithLimit();
	std::cout << "TestSelectWithLimit finish" << std::endl;

	// test select with single step
	std::cout << "start to run TestSelectSingleStep:" << std::endl;
	TestSelectSingleStep();
	std::cout << "TestSelectSingleStep finish" << std::endl;

	// test select for different type
	std::cout << "start to run TestDifferentTypeSelect:" << std::endl;
	TestDifferentTypeSelect();
	std::cout << "TestDifferentTypeSelect finish" << std::endl;

	// test empty value
	std::cout << "start to run TestEmptyValue:" << std::endl;
	TestEmptyValue();
	std::cout << "TestEmptyValue finish" << std::endl;

	// test million data process
	std::cout << "start to run TestMillionDataProcess:" << std::endl;
	TestMillionDataProcess();
	std::cout << "TestMillionDataProcess finish" << std::endl;

	std::cout << "finish running all test!" << std::endl;
	getchar();
}