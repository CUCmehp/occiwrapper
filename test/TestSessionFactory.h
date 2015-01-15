#pragma once

/***
*	@brief: this function test occiwrapper's DDL operation,
*			first create a table with only one colunm, then truncate the table, at last drop table table.
*	@add by CUCmehp, since 2012-07-11
*/
void TestDDL();

/***
*	@brief: this function test occiwrapper's insert operation
*	@add by CUCmehp, since 2012-07-11
*/
void TestSimpleInsert();

/***
*	@brief: this function test occiwrapper's insert operation some times with the same session.
*	@add by CUCmehp, since 2012-07-11
*/
void TestSimpleInsertTimes();

/***
*	@brief: this function test occiwrapper's insert binding operation.
*	@add by CUCmehp, since 2012-07-11
*/
void TestSimpleBinding();

/***
*	@brief: this function test occiwrapper's insert binding operation. excute many times.
*	@add by CUCmehp, since 2012-07-14
*/
void TestSimpleBindingTimes();

/***
*	@brief: this function test occiwrapper's insert binding operation, bind for oracle::occi::Number
*	@add by CUCmehp, since 2012-07-14
*/
void TestBindOcciNumber();

/***
*	@brief: test simple batched bind.
*	@add by CUCmehp, since 2012-07-14
*/
void TestSimpleBatchedBind();


/***
*	@brief: test batched bind two vector and a vector< tuple >
*	@add by CUCmehp, since 2012-07-14
*/
void TestBindTwoColumns();

/***
*	@brief: this function test occiwrapper's commit and rollback operation
*	@add by CUCmehp, since 2012-07-12
*/
void TestRollbackAndCommit();

/***
*	@brief: this function test occiwrapper's date operation
*	@add by CUCmehp, since 2012-07-14
*/
void TestDate();

/***
*	@brief: this function test occiwrapper's update operation.
*	@add by CUCmehp, since 2012-07-14
*/
void TestUpdate();

/***
*	@brief: this function test occiwrapper's insert operation, bind tuple inner tuple
*	@add by CUCmehp, since 2012-07-14
*/
void TestBindTuple();

/***
*	@brief: this function test procedure calling
*	@add by CUCmehp, since 2012-07-14
*/
void TestProcedure();

/***
*	@brief: this function test funciton calling
*	@add by CUCmehp, since 2012-07-14
*/
void TestFunction();

/***
*	@brief: test function call, retrieve different values.
*	@add by CUCmehp, since 2012-07-15
*/
void TestFunctionRetrieveAll();

/***
*	@brief: test function call, pass parameter into the function
*/
void TestFunctionPassIntoAll();

/***
*	@brief: test batched insert and select
*	@add by CUCmehp, since 2012-08-05
*/
void TestBatchedInsertAndSelect();

/***
*	@brief: test select user tables
*	@add by CUCmehp, since 2014-12-10
*/
void TestUserTableSelect();
/***
*	@brief: test select with limit
*	@add by CUCmehp, since 2012-08-05
*/
void TestSelectWithLimit();

/***
*	@brief: test select with single step
*	@add by CUCmehp, since 2014-01-01
*/
void TestSelectSingleStep();

/***
*	@brief: test select for different type
*	@add by CUCmehp, since 2012-08-05
*/
void TestDifferentTypeSelect();

/***
*	@brief: test select for different type
*	@add by CUCmehp, since 2012-08-05
*/
void TestEmptyValue();

/***
*	@brief: test million data process with vector
*	@add by CUCmehp, since 2012-08-05
*/
void TestMillionDataProcess();

/***
*	@brief: test million data process with list
*	@add by CUCmehp, since 2015-01-07
*/
void TestMillionDataProcessList();

/***
*	@brief: test select into single data
*	@add by CUCmehp, since 2014-12-28
*/
void TestSingleRowSelect();



