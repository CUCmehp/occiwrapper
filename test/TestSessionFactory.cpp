#include "OcciWrapper/OcciWrapper.h"
#include <time.h>
#include "DbConfig.h"

#pragma warning( disable : 4244 )

void TestSingleRowSelect()
{
	test_db_config::DbConfig config;
	bool bRet = config.Init();
	assert( bRet == true );
	occiwrapper::ConnectionInfo info( config.GetStrIp(), 1521, config.GetUserName(), config.GetPassword(), config.GetSid() );
	occiwrapper::SessionFactory sf;
	occiwrapper::Session s = sf.Create( info );
	string strErrMsg = "";
	string strProcedure = 
	"declare \
		v_count  number(8); \
		v_sql    varchar2( 1024 ); \
	begin \
		select count( 1 ) into v_count from user_tables where table_name = 'TBL_TEST';   \
		if v_count = 1 then \
			v_sql := 'drop table tbl_test'; \
			execute immediate v_sql; \
		end if; \
	exception \
		when others then \
		dbms_output.put_line( 'error : ' || SQLERRM ); \
	end;";
	s << strProcedure, now, bRet, strErrMsg;
	assert( bRet == true );
	s << "create table tbl_test( x int )", now, bRet, strErrMsg;
	assert( bRet == true );
	// test select into int variable
	int nCount;
	s << "select count(1) from user_tables where lower( table_name ) = 'tbl_test'", into( nCount ), now, bRet, strErrMsg;
	assert( bRet == true );
	assert( nCount == 1 );
	// test select into string variable
	string strValue = "";
	s << "select table_name from user_tables where lower( table_name ) = 'tbl_test'", into( strValue ), now, bRet, strErrMsg;
	assert( bRet == true );
	assert( strValue == "TBL_TEST" );
	s << "select 'this is a test for long string. hello Mr DanDan.' from dual", into( strValue ), now, bRet, strErrMsg;
	assert( bRet );
	assert( strValue == "this is a test for long string. hello Mr DanDan." );
	// test select into struct tm 
	struct tm objStructTm;
	s << "select to_date( '2014-12-30 10:43:00', 'yyyy-mm-dd hh24:mi:ss') from dual", into( objStructTm ), now, bRet, strErrMsg;
	assert( bRet == true );
	assert( objStructTm.tm_year == 2014 - 1900 );
	assert( objStructTm.tm_mon == 11 );
	assert( objStructTm.tm_mday == 30 );
	assert( objStructTm.tm_hour == 10 );
	assert( objStructTm.tm_min == 43 );
	assert( objStructTm.tm_sec == 0 );
	s << "drop table tbl_test", now, bRet, strErrMsg;
	assert( bRet == true );
	assert( strErrMsg.empty() );
}

void TestUserTableSelect()
{
	test_db_config::DbConfig config;
	bool bRet = config.Init();
	assert( bRet == true );
	occiwrapper::ConnectionInfo info( config.GetStrIp(), 1521, config.GetUserName(), config.GetPassword(), config.GetSid() );
	occiwrapper::SessionFactory sf;
	occiwrapper::Session s = sf.Create( info );
	string strErrMsg = "";
	s << "create table tbl_test( x int )", now, bRet, strErrMsg;
	assert( bRet == true );
	vector< int > vCount;
	s << "select count(1) from user_tables where lower( table_name ) = 'tbl_test'", into( vCount ), now, bRet, strErrMsg;
	assert( bRet == true );
	assert( vCount.size() == 1 );
	assert( vCount[ 0 ] == 1 );
	s << "drop table tbl_test", now, bRet, strErrMsg;
	assert( bRet == true );
	assert( strErrMsg.empty() );
}

void TestDDL( )
{
	test_db_config::DbConfig config;
	bool bRet = config.Init();
	assert( bRet == true );
	occiwrapper::ConnectionInfo info( config.GetStrIp(), 1521, config.GetUserName(), config.GetPassword(), config.GetSid() );
	occiwrapper::SessionFactory sf;
	occiwrapper::Session s = sf.Create( info );
	string strErrMsg = "";
	s << "create table tbl_test( x int )", now, bRet, strErrMsg;
	assert( bRet == true );
	s << "truncate table tbl_test", now, bRet, strErrMsg;
	assert( bRet == true );
	s << "drop table tbl_test", now, bRet, strErrMsg;
	assert( bRet == true );
	assert( strErrMsg.empty() );
}


void TestSimpleInsert()
{
	test_db_config::DbConfig config;
	bool bRet = config.Init();
	assert( bRet == true );
	occiwrapper::ConnectionInfo info( config.GetStrIp(), 1521, config.GetUserName(), config.GetPassword(), config.GetSid() );
	occiwrapper::SessionFactory sf;
	occiwrapper::Session s = sf.Create( info );
	string strErrMsg = "";
	s << "truncate table tbl_test1", now, bRet, strErrMsg;
	assert( bRet == true );
	s << "insert into tbl_test1( x ) values ( 10004 )", now, bRet, strErrMsg;
	assert( bRet == true );
	assert( strErrMsg.empty() );
}

void TestSimpleInsertTimes()
{
	test_db_config::DbConfig config;
	bool bRet = config.Init();
	assert( bRet == true );
	occiwrapper::ConnectionInfo info( config.GetStrIp(), 1521, config.GetUserName(), config.GetPassword(), config.GetSid() );
	occiwrapper::SessionFactory sf;
	occiwrapper::Session s = sf.Create( info );
	s << "delete from tbl_test1", now;
	s.Commit();
	int i = 0;
	occiwrapper::Statement stmt = ( s << "insert into tbl_test1( x ) values ( 10005 )" );
	for (i = 0; i < 2; ++i)
	{
		stmt.Execute();
	}
	s.Commit();
}

void TestSimpleBinding()
{
	test_db_config::DbConfig config;
	bool bRet = config.Init();
	assert( bRet == true );
	occiwrapper::ConnectionInfo info( config.GetStrIp(), 1521, config.GetUserName(), config.GetPassword(), config.GetSid() );
	occiwrapper::SessionFactory sf;
	occiwrapper::Session s = sf.Create( info );
	string strErrMsg;
	s << "truncate table tbl_test1", now;
	s << "truncate table test_string", now;
	s << "truncate table test_number", now;
	s << "insert into tbl_test1( x ) values ( :1 )", use( 2 ), now, bRet, strErrMsg;
	assert( bRet );

	s << "insert into test_string( id, string_val ) values( :1, :2 )", use( 2 ), use( "CUCmehp" ), now, bRet, strErrMsg;
	assert( bRet );

	s << "insert into test_number( id, number_value ) values( :1, :2 )", use( 1 ), use( 3.5 ), now, bRet, strErrMsg;
	assert( bRet );
}


void TestSimpleBindingTimes()
{
	test_db_config::DbConfig config;
	bool bRet = config.Init();
	assert( bRet == true );
	occiwrapper::ConnectionInfo info( config.GetStrIp(), 1521, config.GetUserName(), config.GetPassword(), config.GetSid() );
	occiwrapper::SessionFactory sf;
	occiwrapper::Session s = sf.Create( info );
	string strErrMsg;
	s << "truncate table tbl_test1", now;
	occiwrapper::Statement stmt = s << "insert into tbl_test1( x ) values( :1 )";
	for( int i = 0; i < 10; ++ i )
	{
		stmt, use( i ), now, bRet;
		assert( bRet );
	}
}


void TestRollbackAndCommit()
{
	test_db_config::DbConfig config;
	bool bRet = config.Init();
	assert( bRet == true );
	occiwrapper::ConnectionInfo info( config.GetStrIp(), 1521, config.GetUserName(), config.GetPassword(), config.GetSid() );
	occiwrapper::SessionFactory sf;
	occiwrapper::Session s = sf.Create( info, false );
	s << "truncate table tbl_test1", now;
	s.Commit();

	string strErrMsg = "";
	s << "insert into tbl_test1( x ) values ( 10005 )", now, bRet, strErrMsg;
	s.Rollback();

	occiwrapper::Statement stmt2 = ( s << "insert into tbl_test1( x ) values ( 10005 )" );

	for ( int i = 0; i < 2; ++i)
	{
		stmt2.Execute();
	}
	s.Commit();
}


// test bind Number
void TestBindOcciNumber()
{
	test_db_config::DbConfig config;
	bool bRet = config.Init();
	assert( bRet == true );
	occiwrapper::ConnectionInfo info( config.GetStrIp(), 1521, config.GetUserName(), config.GetPassword(), config.GetSid() );
	occiwrapper::SessionFactory sf;
	occiwrapper::Session s = sf.Create( info );
	string strErrMsg;
	oracle::occi::Number number( 100.234 );
	s << "insert into test_number( id, number_value ) values( :1, :2 )", use( 1 ), use( number ), now, bRet, strErrMsg;
	assert( bRet );
}

// test simple batched binding
void TestSimpleBatchedBind()
{
	test_db_config::DbConfig config;
	bool bRet = config.Init();
	assert( bRet == true );
	occiwrapper::ConnectionInfo info( config.GetStrIp(), 1521, config.GetUserName(), config.GetPassword(), config.GetSid() );
	occiwrapper::SessionFactory sf;
	occiwrapper::Session s = sf.Create( info );
	string strErrMsg;

	s << "truncate table tbl_test1", now, bRet;
	assert( bRet );
	
	int a[5] = { 20, 21, 22, 23, 24 };
	vector< int > vec( a, a + 5 );

	s << "insert into tbl_test1( x ) values ( :1 )", batched_use( vec ), now, bRet, strErrMsg;
	assert( bRet );
}

// test batched binding
void TestBindTwoColumns()
{
	test_db_config::DbConfig config;
	bool bRet = config.Init();
	assert( bRet == true );
	occiwrapper::ConnectionInfo info( config.GetStrIp(), 1521, config.GetUserName(), config.GetPassword(), config.GetSid() );
	occiwrapper::SessionFactory sf;
	occiwrapper::Session s = sf.Create( info );
	string strErrMsg;

	int a[5] = { 20, 21, 22, 23, 24 };
	vector< int > vec( a, a + 5 );

	string strArray[5] = { "message1", "message2", "message3", "message4", "message5" };
	vector< string > vecStr( strArray, strArray + 5 );

	s << "insert into test_string( id, string_val ) values ( :1, :2 )", batched_use( vec ), batched_use( vecStr ), now, bRet, strErrMsg;
	assert( bRet );

	s << "truncate table test_string", now, bRet;
	assert( bRet );

	vector< tuple< int, string > > vecTuple;
	for( size_t i = 0; i < 5; ++ i )
	{
		vecTuple.push_back( make_tuple( vec[ i ], vecStr[ i ] ) );
	}
	s << "insert into test_string( id, string_val ) values ( :1, :2 )", batched_use( vecTuple ), now, bRet, strErrMsg;
	assert( bRet );
}

// test date
void TestDate()
{
	test_db_config::DbConfig config;
	bool bRet = config.Init();
	assert( bRet == true );
	occiwrapper::ConnectionInfo info( config.GetStrIp(), 1521, config.GetUserName(), config.GetPassword(), config.GetSid() );
	occiwrapper::SessionFactory sf;
	occiwrapper::Session s = sf.Create( info );
	string strErrMsg;

	struct tm tmValue;
	time_t nowTime = time( NULL );
#ifdef WIN32
	localtime_s( &tmValue, &nowTime );
#else
	localtime_r( &nowTime, &tmValue );
#endif // WIN32
	s << "truncate table test_date", now, bRet, strErrMsg;
	assert( bRet );

	s << "insert into test_date( date_val ) values ( :1 )", use( tmValue ), now, bRet, strErrMsg;
	assert( bRet );

	vector< struct tm > vTmDb;
	for( int i = 0; i < 10000; ++ i )
	{
		vTmDb.push_back( tmValue );
	}
	s << "insert into test_date( date_val ) values ( :1 )", batched_use( vTmDb ), now, bRet, strErrMsg;
	assert( bRet );

	vTmDb.clear();
	s << "select date_val from test_date", into( vTmDb ), now, bRet, strErrMsg;
	assert( bRet );
	assert( vTmDb.size() == 10001 );
	assert( vTmDb[ 0 ].tm_year == tmValue.tm_year );
	assert( vTmDb[ 0 ].tm_mon == tmValue.tm_mon );
	assert( vTmDb[ 0 ].tm_mday == tmValue.tm_mday );
	assert( vTmDb[ 0 ].tm_hour == tmValue.tm_hour );
	assert( vTmDb[ 0 ].tm_min == tmValue.tm_min );
	assert( vTmDb[ 0 ].tm_sec == tmValue.tm_sec );
}

// test update
void TestUpdate()
{
	test_db_config::DbConfig config;
	bool bRet = config.Init();
	assert( bRet == true );
	occiwrapper::ConnectionInfo info( config.GetStrIp(), 1521, config.GetUserName(), config.GetPassword(), config.GetSid() );
	occiwrapper::SessionFactory sf;
	occiwrapper::Session s = sf.Create( info );
	string strErrMsg = "";
	s << "truncate table tbl_test1", now, bRet, strErrMsg;
	assert( bRet == true );
	s << "insert into tbl_test1( x ) values ( 10004 )", now, bRet, strErrMsg;
	assert( bRet == true );
	s << "update tbl_test1 set x = :1 where x = 10004", use( 10005 ), now, bRet, strErrMsg;
	assert( bRet );
};

// test bind tuple
void TestBindTuple()
{
	test_db_config::DbConfig config;
	bool bRet = config.Init();
	assert( bRet == true );
	occiwrapper::ConnectionInfo info( config.GetStrIp(), 1521, config.GetUserName(), config.GetPassword(), config.GetSid() );
	occiwrapper::SessionFactory sf;
	occiwrapper::Session s = sf.Create( info );
	string strErrMsg;
	tuple< int, tuple< int > > a[5] = { make_tuple( 20, make_tuple( 30 ) ), make_tuple( 21, make_tuple( 31 ) ), make_tuple( 22, make_tuple( 32 ) ), make_tuple( 23, make_tuple( 33 ) ), make_tuple( 24, make_tuple( 34 ) ) };	
	vector< tuple< int, tuple< int > > > vec( a, a + 5 );
	s << "truncate table tbl_test2", now, bRet, strErrMsg;
	assert( bRet );
	s << "insert into tbl_test2( x, y ) values ( :1, :2 )", batched_use( vec ), now, bRet, strErrMsg;
	assert( bRet );
}

// test procedure calling
void TestProcedure()
{
	test_db_config::DbConfig config;
	bool bRet = config.Init();
	assert( bRet == true );
	occiwrapper::ConnectionInfo info( config.GetStrIp(), 1521, config.GetUserName(), config.GetPassword(), config.GetSid() );
	occiwrapper::SessionFactory sf;
	occiwrapper::Session s = sf.Create( info );
	string strErrMsg;

	int nParIn = 1000;
	string strParOut = "";
	s << "begin p_test_procedure( :1,:2 ); end;", use( nParIn, occiwrapper::PAR_IN ), use( strParOut, occiwrapper::PAR_OUT ), now, bRet, strErrMsg;
	assert( bRet );
	assert( strParOut == "1000" );
}

//test function call1
void TestFunction()
{
	test_db_config::DbConfig config;
	bool bRet = config.Init();
	assert( bRet == true );
	occiwrapper::ConnectionInfo info( config.GetStrIp(), 1521, config.GetUserName(), config.GetPassword(), config.GetSid() );
	occiwrapper::SessionFactory sf;
	occiwrapper::Session s = sf.Create( info );
	string strErrMsg;

	int a;
	s << "begin :1 := f_ins_tbl_test1( :2 ); end;", use( a, occiwrapper::PAR_OUT ), use( 2, occiwrapper::PAR_IN ) , now, bRet, strErrMsg;
	assert( bRet );

	int b;
	s << "begin :1 := f_test2( :2, :3 ); end;", use( a, occiwrapper::PAR_OUT ), use( 2 ), use( b, occiwrapper::PAR_OUT ), now, bRet, strErrMsg;
	assert( bRet );
}

//test function call, retrieve different values.
void TestFunctionRetrieveAll()
{
	test_db_config::DbConfig config;
	bool bRet = config.Init();
	assert( bRet == true );
	occiwrapper::ConnectionInfo info( config.GetStrIp(), 1521, config.GetUserName(), config.GetPassword(), config.GetSid() );
	occiwrapper::SessionFactory sf;
	occiwrapper::Session s = sf.Create( info );
	string strErrMsg;

	int ret;
	int a1;
	string a2;
	struct tm a3;
	float a4;
	occiwrapper::Int64 a5;

	s << "begin :1 := f_test3( :2, :3, :4, :5, :6 ); end;", use( ret, occiwrapper::PAR_OUT ), use( a1, occiwrapper::PAR_OUT  ), use( a2, occiwrapper::PAR_OUT  ), use( a3, occiwrapper::PAR_OUT  ), use( a4, occiwrapper::PAR_OUT  ), use( a5, occiwrapper::PAR_OUT  ), now, bRet, strErrMsg;
	//if( bRet )
	//{
	//	cout << a1 << endl << a2 << endl << a3.tm_year + 1900 << "-" << a3.tm_mon + 1 << "-" << a3.tm_mday << " " << a3.tm_hour << ":" << a3.tm_min << ":" << a3.tm_sec << endl << a4 << endl << ( double )a5 << endl;
	//}
	assert( bRet );
}

//test function call, pass different values.
void TestFunctionPassIntoAll()
{
	test_db_config::DbConfig config;
	bool bRet = config.Init();
	assert( bRet == true );
	occiwrapper::ConnectionInfo info( config.GetStrIp(), 1521, config.GetUserName(), config.GetPassword(), config.GetSid() );
	occiwrapper::SessionFactory sf;
	occiwrapper::Session s = sf.Create( info );
	string strErrMsg;

	int ret;
	int a1 = 1;
	string a2 = "string message";
	time_t tNow = time( NULL );
	struct tm a3 = *localtime( &tNow );
	float a4 = 1.1;
	occiwrapper::Int64 a5 = 100;
	string strMsg;
	s << "begin :1 := f_test4( :2, :3, :4, :5, :6, :7 ); end;", use( ret, occiwrapper::PAR_OUT ), use( a1, occiwrapper::PAR_IN  ), use( a2, occiwrapper::PAR_IN  ), use( a3, occiwrapper::PAR_IN  ), use( a4, occiwrapper::PAR_IN  ), use( a5, occiwrapper::PAR_IN  ), use( strMsg, occiwrapper::PAR_OUT ), now, bRet, strErrMsg;
	assert( bRet );
}

// test batched insert and select
void TestBatchedInsertAndSelect()
{
	test_db_config::DbConfig config;
	bool bRet = config.Init();
	assert( bRet == true );
	occiwrapper::ConnectionInfo info( config.GetStrIp(), 1521, config.GetUserName(), config.GetPassword(), config.GetSid() );
	occiwrapper::SessionFactory sf;
	occiwrapper::Session s = sf.Create( info );
	string strErrMsg;
	s << "truncate table test_batched_table", now, bRet, strErrMsg;
	assert( bRet );

	struct tm tm_value;
	time_t now_time = time( NULL );
#ifdef WIN32
	localtime_s( &tm_value, &now_time );
#else
	localtime_r( &now_time, &tm_value );
#endif // WIN32
	vector< string > vec0;
	vec0.push_back( "123456" );
	vec0.push_back( "222222" );

	vector< struct tm >  vec1;
	vec1.push_back( tm_value );
	vec1.push_back( tm_value );

	vector< occiwrapper::Int8 > vec2;
	vec2.push_back( 1 );
	vec2.push_back( 2 );

	vector< float > vec3;
	vec3.push_back( 0.1 );
	vec3.push_back( 0.2 );

	vector< double > vec4;
	vec4.push_back( 10000 );
	vec4.push_back( 100 );

	s << "insert into test_batched_table( string_value, date_value, int_value, float_value, number_value ) values ( :1, :2, :3, :4, :5 )", batched_use( vec0 ), batched_use( vec1 ), batched_use( vec2 ), batched_use( vec3 ), batched_use( vec4 ), now, bRet, strErrMsg;
	assert( bRet );
	s << "insert into test_batched_table( string_value, date_value, int_value, float_value, number_value ) values ( :1, :2, :3, :4, :5 )", use( "hello world" ), use( tm_value ), use( 100 ), use( 1.2 ), use( 2000.12312 ), now, bRet, strErrMsg;
	assert( bRet );

	vector< string > vStr;
	vector< struct tm > vDate;
	vector< occiwrapper::UInt64 > vInt;
	vector< float > vFloat;
	vector< double > vDouble;
	s << "select string_value, date_value, int_value, float_value, number_value from test_batched_table", into( vStr ), into( vDate ), into( vInt ), into( vFloat ), into( vDouble ), now, bRet, strErrMsg;
	assert( bRet );
}

// test select into with upper limit
void TestSelectWithLimit()
{
	test_db_config::DbConfig config;
	bool bRet = config.Init();
	assert( bRet == true );
	occiwrapper::ConnectionInfo info( config.GetStrIp(), 1521, config.GetUserName(), config.GetPassword(), config.GetSid() );
	occiwrapper::SessionFactory sf;
	occiwrapper::Session s = sf.Create( info );
	string strErrMsg;

	tuple< int, tuple< int > > a[5] = { make_tuple( 20, make_tuple( 30 ) ), make_tuple( 21, make_tuple( 31 ) ), make_tuple( 22, make_tuple( 32 ) ), make_tuple( 23, make_tuple( 33 ) ), make_tuple( 24, make_tuple( 34 ) ) };
	vector< tuple< int, tuple< int > > > vec( a, a + 5 );

	s << "truncate table tbl_test2", now, bRet, strErrMsg;
	assert( bRet );
	s << "insert into tbl_test2( x, y ) values ( :1, :2 )", batched_use( vec ), now, bRet, strErrMsg;
	assert( bRet );

	vector< int > vec1;
	vector< int > vec2;
	// test limit select
	s << "select * from tbl_test2 t", into( vec1 ), into( vec2 ), limit( 3 ), now;
	assert( vec1.size() == 3 );
	assert( vec2.size() == 3 );
	vec1.clear();
	vec2.clear();
	// stupid test, for zero limit no crashing.
	s << "select * from tbl_test2 t", into( vec1 ), into( vec2 ), limit( 0 ), now, bRet;
	assert( bRet );
	assert( vec1.size() == 0 );
	assert( vec2.size() == 0 );
	vec1.clear();
	vec2.clear();
	// test unlimit select
	s << "select * from tbl_test2 t", into( vec1 ), into( vec2 ), now, bRet;
	assert( bRet );
	assert( vec1.size() == 5 );
	assert( vec2.size() == 5 );

	//test: select multiply value, but only first value into the number
	int nMaxNumber;
	s << "select x from tbl_test2 order by x desc", into( nMaxNumber ), now, bRet;
	assert( bRet );
	assert( nMaxNumber == 24);
}


//test statement
void TestStatement()
{
	test_db_config::DbConfig config;
	bool bRet = config.Init();
	assert( bRet == true );
	occiwrapper::ConnectionInfo info( config.GetStrIp(), 1521, config.GetUserName(), config.GetPassword(), config.GetSid() );
	occiwrapper::SessionFactory sf;
	occiwrapper::Session s = sf.Create( info );
	string strErrMsg = "";

	tuple< int, tuple< int > > a[5] = { make_tuple( 20, make_tuple( 30 ) ), make_tuple( 21, make_tuple( 31 ) ), make_tuple( 22, make_tuple( 32 ) ), make_tuple( 23, make_tuple( 33 ) ), make_tuple( 24, make_tuple( 34 ) ) };
	vector< tuple< int, tuple< int > > > vec( a, a + 5 );

	occiwrapper::Statement stat1 = s << "truncate table tbl_test2";
	bRet = stat1.Execute();
	strErrMsg = stat1.GetErrMsg();
	assert( bRet );
	assert( strErrMsg.empty() );

	occiwrapper::Statement stat2 = s << "insert into tbl_test2( x, y ) values ( :1, :2 )";
	stat2.AddBinding( batched_use( vec ) );
	bRet = stat2.Execute();
	strErrMsg = stat2.GetErrMsg();
	assert( bRet );
	assert( strErrMsg.empty() );

	occiwrapper::Statement stat3 = s << "insert into no_exists_test2( x, y ) values ( :1, :2 )";
	stat3.AddBinding( batched_use( vec ) );
	bRet = stat3.Execute();
	strErrMsg = stat3.GetErrMsg();
	assert( bRet == false );
	assert( !strErrMsg.empty() );

	vector< int > vec1;
	vector< int > vec2;
	// test limit select
	occiwrapper::Statement stat4 = s << "select * from tbl_test2 t";
	stat4.AddExtract( into( vec1 ) );
	stat4.AddExtract( into( vec2 ) );
	stat4.SetExtractionLimit( limit( 3 ) );
	bRet = stat4.Execute();
	assert( stat4.GetErrMsg().empty() );
	assert( vec1.size() == 3 );
	assert( vec2.size() == 3 );
	vec1.clear();
	vec2.clear();

	// stupid test, for zero limit no crashing.
	occiwrapper::Statement stat5 = s << "select * from tbl_test2 t";
	stat5.AddExtract( into( vec1 ) );
	stat5.AddExtract( into( vec2 ) );
	stat5.SetExtractionLimit( limit( 0 ) );
	bRet = stat5.Execute();
	assert( bRet );
	assert( stat5.GetErrMsg().empty() );
	assert( vec1.size() == 0 );
	assert( vec2.size() == 0 );
	vec1.clear();
	vec2.clear();

	// test unlimit select
	occiwrapper::Statement stat6 = s << "select * from tbl_test2 t";
	stat6.AddExtract( into( vec1 ) );
	stat6.AddExtract( into( vec2 ) );
	bRet = stat6.Execute();
	assert( bRet );
	assert( stat6.GetErrMsg().empty() );
	assert( vec1.size() == 5 );
	assert( vec2.size() == 5 );

	//test: select multiply value, but only first value into the number
	int nMaxNumber;
	occiwrapper::Statement stat7 = s << "select x from tbl_test2 order by x desc";
	stat7.AddExtract( into( nMaxNumber ) );
	bRet = stat7.Execute();
	assert( bRet );
	assert( stat7.GetErrMsg().empty() );
	assert( nMaxNumber == 24);
}

//test select with single step
void TestSelectSingleStep()
{
	test_db_config::DbConfig config;
	bool bRet = config.Init();
	assert( bRet == true );
	occiwrapper::ConnectionInfo info( config.GetStrIp(), 1521, config.GetUserName(), config.GetPassword(), config.GetSid() );
	occiwrapper::SessionFactory sf;
	occiwrapper::Session s = sf.Create( info );
	string strErrMsg;
	tuple< int, tuple< int > > a[5] = { make_tuple( 20, make_tuple( 30 ) ), make_tuple( 21, make_tuple( 31 ) ), make_tuple( 22, make_tuple( 32 ) ), make_tuple( 23, make_tuple( 33 ) ), make_tuple( 24, make_tuple( 34 ) ) };
	vector< tuple< int, tuple< int > > > vec( a, a + 5 );

	s << "truncate table tbl_test2", now, bRet, strErrMsg;
	assert( bRet );
	s << "insert into tbl_test2( x, y ) values ( :1, :2 )", batched_use( vec ), now, bRet, strErrMsg;
	assert( bRet );

	vector< int > vec1;
	vector< int > vec2;
	// test limit select, getting all of data to the vectors
	occiwrapper::Statement stmt = ( s << "select * from tbl_test2 t", into( vec1 ), into( vec2 ), limit( 2 ) );
	do
	{
		stmt.Execute();
	}
	while( stmt.HasNext() );
	assert( stmt.Done() == true );
	assert( vec1.size() == 5 && vec2.size() == 5 );

	// another test
	vec1.clear();
	vec2.clear();
	stmt = ( s << "select * from tbl_test2 t", into( vec1 ), into( vec2 ), limit( 2 ) );
	///< first select option, getting 2 items
	assert( stmt.Execute() == true );
	assert( stmt.HasNext() == true );
	assert( stmt.Done() == true );
	assert( vec1.size() == 2 && vec2.size() == 2 );
	///< second select option, getting 2 items
	assert( stmt.Execute() == true );
	assert( stmt.HasNext() == true );
	assert( stmt.Done() == true );
	assert( vec1.size() == 4 && vec2.size() == 4 );
	///< third select option, getting only 1 item.
	assert( stmt.Execute() == true );
	assert( stmt.Done() == true );
	assert( stmt.HasNext() == false );
	assert( vec1.size() == 5 && vec2.size() == 5 );
}


// test select into
void TestDifferentTypeSelect()
{
	test_db_config::DbConfig config;
	bool bRet = config.Init();
	assert( bRet == true );
	occiwrapper::ConnectionInfo info( config.GetStrIp(), 1521, config.GetUserName(), config.GetPassword(), config.GetSid() );
	occiwrapper::SessionFactory sf;
	occiwrapper::Session s = sf.Create( info );
	string strErrMsg;

	struct tm* pTm;
	time_t _time = time( NULL );
	pTm = localtime( &_time );
	tuple< float, string, struct tm, int, double > a[5];
	a[0] = make_tuple( 2.0, "1", *pTm, 20, 2.0 );
	a[1] = make_tuple( 2.1, "2", *pTm, 21, 2.1 );
	a[2] = make_tuple( 2.3, "3", *pTm, 23, 2.3 );
	a[3] = make_tuple( 2.4, "4", *pTm, 24, 2.4 );
	a[4] = make_tuple( 2.5, "5", *pTm, 25, 2.5 );
	vector< tuple< float, string, struct tm, int, double > > vec( a, a + 5 );
	s << "truncate table test_batched_table", now, bRet, strErrMsg;
	assert( bRet );
	s << "insert into test_batched_table( float_value, string_value, date_value, int_value, number_value ) values ( :1, :2, :3, :4, :5 )", batched_use( vec ), now, bRet, strErrMsg;
	assert( bRet );

	vector< string > vStr;
	vector< struct tm > vDate;
	vector< occiwrapper::Int32 > vInt;
	vector< float > vFloat;
	vector< double > vDouble;
	s << "select string_value, date_value, int_value, float_value, number_value from test_batched_table", into( vStr ), into( vDate ), into( vInt ), into( vFloat ), into( vDouble ), now, bRet, strErrMsg;
	assert( bRet );
	assert( vStr.size() == 5 );
	assert( vDate.size() == 5 );
	assert( vInt.size() == 5 );
	assert( vFloat.size() == 5 );
	assert( vDouble.size() == 5 );

	vector< tuple< float > > vOut1;
	s << "select float_value from test_batched_table", into( vOut1 ), now, bRet, strErrMsg;
	assert( bRet );
	assert( vOut1.size() == 5 ) ;

	vector< tuple< float, string > > vOut2;
	s << "select float_value, string_value from test_batched_table", into( vOut2 ), now, bRet, strErrMsg;
	assert( bRet );
	assert( vOut2.size() == 5 ) ;

	vector< tuple< struct tm, int, double > > vOut3;
	s << "select date_value, int_value, number_value from test_batched_table", into( vOut3 ), now, bRet, strErrMsg;
	assert( bRet );
	assert( vOut3.size() == 5 ) ;

	vOut2.clear();
	vOut3.clear();
	s << "select  float_value, string_value, date_value, int_value, number_value from test_batched_table", into( vOut2 ), into( vOut3 ), now, bRet, strErrMsg;
	assert( bRet );
	assert( vOut2.size() == 5 );
	assert( vOut3.size() == 5 );

	vector< tuple< float, string, struct tm, int > > vOut4;
	s << "select float_value, string_value, date_value, int_value from test_batched_table", into( vOut4 ), now, bRet, strErrMsg;
	assert( bRet );
	assert( vOut4.size() == 5 ) ;

	vector< tuple< float, string, struct tm, int, double > > vAll;
	s << "select float_value, string_value, date_value, int_value, number_value from test_batched_table", into( vAll ), now, bRet, strErrMsg;
	assert( bRet );
	assert( vAll.size() == 5 ) ;
}

// test empty
void TestEmptyValue()
{
	test_db_config::DbConfig config;
	bool bRet = config.Init();
	assert( bRet == true );
	occiwrapper::ConnectionInfo info( config.GetStrIp(), 1521, config.GetUserName(), config.GetPassword(), config.GetSid() );
	occiwrapper::SessionFactory sf;
	occiwrapper::Session s = sf.Create( info );
	string strErrMsg;
	s << "truncate table test_batched_table", now, bRet, strErrMsg;
	assert( bRet );

	vector< string > vec;
	vec.push_back( "1" );
	vec.push_back( "" );
	vec.push_back( "3" );

	list< int > listInt;
	listInt.push_back( 1 );
	listInt.push_back( 2 );
	listInt.push_back( 3 );

	s << "insert into test_batched_table( string_value, int_value ) values ( :1, :2 )", batched_use( vec ), batched_use( listInt ), now, bRet, strErrMsg;
	assert( bRet );

	vector< string > vStr;
	vector< struct tm > vDate;
	vector< occiwrapper::Int32 > vInt;
	vector< float > vFloat;
	vector< double > vDouble;
	s << "select string_value, date_value, int_value, float_value, number_value from test_batched_table", into( vStr ), into( vDate ), into( vInt ), into( vFloat ), into( vDouble ), now, bRet, strErrMsg;
	assert( bRet );
}

//test process large amount of data
void TestMillionDataProcess()
{
	test_db_config::DbConfig config;
	bool bRet = config.Init();
	assert( bRet == true );
	occiwrapper::ConnectionInfo info( config.GetStrIp(), 1521, config.GetUserName(), config.GetPassword(), config.GetSid() );
	occiwrapper::SessionFactory sf;
	occiwrapper::Session s = sf.Create( info );
	string strErrMsg;
	s << "truncate table test_batched_table", now, bRet, strErrMsg;
	assert( bRet );

	struct tm tm_value;
	time_t now_time = time( NULL );
#ifdef WIN32
	localtime_s( &tm_value, &now_time );
#else
	localtime_r( &now_time, &tm_value );
#endif // WIN32

	vector< string > vecStr;
	vector< struct tm >  vecTm;
	vector< occiwrapper::Int32 > vecInt32;
	vector< float > vecFloat;
	vector< double > vecDouble;

	char vBuf[1024] = "\0";
	const int nTocalBatchCount = 10;
	const int nTestCount = 10000;
	for( size_t k = 0; k < nTocalBatchCount; ++ k )
	{
		for( size_t i = k * nTestCount; i < k * nTestCount + nTestCount; ++ i )
		{
			//itoa( i, vBuf, 10 ); // as itoa is indeed non-standard, use sprintf instead
			sprintf( vBuf, "%d", i );
			vecStr.push_back( vBuf );
			vecTm.push_back( tm_value );
			vecInt32.push_back( i );
			vecFloat.push_back( ( double ) i / 2 );
			vecDouble.push_back( ( double ) i / 2 );
		}

		s << "insert into test_batched_table( string_value, date_value, int_value, float_value, number_value ) values ( :1, :2, :3, :4, :5 )", batched_use( vecStr ), batched_use( vecTm ), batched_use( vecInt32 ), batched_use( vecFloat ), batched_use( vecDouble ), now, bRet, strErrMsg;
		assert( bRet );
		vecStr.clear();
		vecTm.clear();
		vecInt32.clear();
		vecFloat.clear();
		vecDouble.clear();
	}

	vector< string > vStr;
	vector< struct tm > vDate;
	vector< occiwrapper::UInt64 > vInt;
	vector< float > vFloat;
	vector< double > vDouble;
	s << "select string_value, date_value, int_value, float_value, number_value from test_batched_table order by int_value asc", into( vStr ), into( vDate ), into( vInt ), into( vFloat ), into( vDouble ), limit( 20000 ), now, bRet, strErrMsg;
	assert( bRet );
}


//test process large amount of data for list
void TestMillionDataProcessList()
{
	test_db_config::DbConfig config;
	bool bRet = config.Init();
	assert( bRet == true );
	occiwrapper::ConnectionInfo info( config.GetStrIp(), 1521, config.GetUserName(), config.GetPassword(), config.GetSid() );
	occiwrapper::SessionFactory sf;
	occiwrapper::Session s = sf.Create( info );
	string strErrMsg;
	s << "truncate table test_batched_table", now, bRet, strErrMsg;
	assert( bRet );

	struct tm tm_value;
	time_t now_time = time( NULL );
#ifdef WIN32
	localtime_s( &tm_value, &now_time );
#else
	localtime_r( &now_time, &tm_value );
#endif // WIN32

	list< string > listStr;
	list< struct tm >  listTm;
	list< occiwrapper::Int32 > listInt32;
	list< float > listFloat;
	list< double > listDouble;

	char vBuf[1024] = "\0";
	const int nTocalBatchCount = 2; // as list push_back and clear is time wasted, setting it to 1, you can reset it yourself.
	const int nTestCount = 10000;
	for( size_t k = 0; k < nTocalBatchCount; ++ k )
	{
		for( size_t i = k * nTestCount; i < k * nTestCount + nTestCount; ++ i )
		{
			//itoa( i, vBuf, 10 ); // as itoa is indeed non-standard, use sprintf instead
			sprintf( vBuf, "%d", i );
			listStr.push_back( vBuf );
			listTm.push_back( tm_value );
			listInt32.push_back( i );
			listFloat.push_back( ( double ) i / 2 );
			listDouble.push_back( ( double ) i / 2 );
		}
		s << "insert into test_batched_table( string_value, date_value, int_value, float_value, number_value ) values ( :1, :2, :3, :4, :5 )", batched_use( listStr ), batched_use( listTm ), batched_use( listInt32 ), batched_use( listFloat ), batched_use( listDouble ), now, bRet, strErrMsg;
		assert( bRet );
		listStr.clear();
		listTm.clear();
		listInt32.clear();
		listFloat.clear();
		listDouble.clear();
	}
	list< string > vStr;
	list< struct tm > vDate;
	list< occiwrapper::UInt64 > vInt;
	list< float > vFloat;
	list< double > vDouble;
	s << "select string_value, date_value, int_value, float_value, number_value from test_batched_table order by int_value asc", into( vStr ), into( vDate ), into( vInt ), into( vFloat ), into( vDouble ), limit( 20000 ), now, bRet, strErrMsg;
	assert( bRet );
	assert( vStr.size() == 20000 );
	assert( vDate.size() == 20000 );
	assert( vInt.size() == 20000 );
	assert( vFloat.size() == 20000 );
	assert( vDouble.size() == 20000 );
}
