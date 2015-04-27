#include "TestTuple.h"
#include "OcciWrapper/OcciWrapper.h"
#include "DbConfig.h"
#include "Test.h"

const string strCreateTable = 
	"create table tbl_test_tuple_elements( t1 int,  "
	"									 t2 float, "
	"									 t3 varchar2( 50 ),  "
	"									 t4 date,			  "
	"									 t5 timestamp,		  "
	"									 t6 float,			  "
	"									 t7 number,		  "
	"									 t8 varchar2( 50 ),  "
	"									 t9 varchar2( 50 ),  "
	"									 t10 varchar2( 50 )  "
	" )					  ";

void TestSingleTupleInsertAndSelect()
{
	test_db_config::DbConfig config;
	bool bRet = config.Init();
	assert( bRet == true );
	occiwrapper::ConnectionInfo info( config.GetStrIp(), 1521, config.GetUserName(), config.GetPassword(), config.GetSid() );
	occiwrapper::SessionFactory sf;
	occiwrapper::Session s = sf.Create( info );
	string strErrMsg;

	struct tm objTm;
	objTm.tm_year = 2014 - 1900;
	objTm.tm_mon = 11;
	objTm.tm_mday = 30;
	objTm.tm_hour = 10;
	objTm.tm_min = 43;
	objTm.tm_sec = 0;
	string str = "123";
	//tuple< float, string, struct tm, int, double > obj = make_tuple( 2.0, str, objTm, 20, 2.0 ); // g++ 4.3 not supported!
	tuple< float, string, struct tm, int, double > obj( 2.0, str, objTm, 20, 2.0 );
	s << "truncate table test_batched_table", now, bRet, strErrMsg;
	assert( bRet );
	s << "insert into test_batched_table( float_value, string_value, date_value, int_value, number_value ) values ( :1, :2, :3, :4, :5 )", use( obj ), now, bRet, strErrMsg;
	assert( bRet );

	tuple< float > tOut1;
	s << "select float_value from test_batched_table", into( tOut1 ), now, bRet, strErrMsg;
	assert( get< 0 >( tOut1 ) == 2.0 );

	tuple< float, string > tOut2;
	s << "select float_value, string_value from test_batched_table", into( tOut2 ), now, bRet, strErrMsg;
	assert( get< 0 >( tOut2 ) == 2.0 );
	assert( get< 1 >( tOut2 ) == "123" );

	tuple< struct tm, int, double > tOut3;
	s << "select date_value, int_value, number_value from test_batched_table", into( tOut3 ), now, bRet, strErrMsg;
	assert( get< 0 >( tOut3 ).tm_year == objTm.tm_year  );
	assert( get< 0 >( tOut3 ).tm_mon == objTm.tm_mon  );
	assert( get< 0 >( tOut3 ).tm_mday == objTm.tm_mday  );
	assert( get< 0 >( tOut3 ).tm_hour == objTm.tm_hour  );
	assert( get< 0 >( tOut3 ).tm_min == objTm.tm_min  );
	assert( get< 0 >( tOut3 ).tm_sec == objTm.tm_sec  );
	assert( get< 1 >( tOut3 ) == 20 );
	assert( get< 2 >( tOut3 ) == 2.0 );

	tuple< float, string, int, double > tOut4;
	s << "select float_value, string_value, int_value, number_value from test_batched_table", into( tOut4 ), now, bRet, strErrMsg;
	assert( bRet );
	assert( get< 0 >( tOut4 ) == 2.0 );
	assert( get< 1 >( tOut4 ) == "123" );
	assert( get< 2 >( tOut4 ) == 20 );
	assert( get< 3 >( tOut4 ) == 2.0 );

	tuple< float, string > tOut2Part;
	tuple< struct tm, int, double > tOut3Part;
	s << "select float_value, string_value, date_value, int_value, number_value from test_batched_table", into( tOut2Part ), into( tOut3Part), now, bRet, strErrMsg;
	assert( bRet );
	assert( get< 0 >( tOut2Part ) == 2.0 );
	assert( get< 1 >( tOut2Part ) == "123"  );
	assert( get< 0 >( tOut3Part ).tm_year == objTm.tm_year  );
	assert( get< 0 >( tOut3Part ).tm_mon == objTm.tm_mon  );
	assert( get< 0 >( tOut3Part ).tm_mday == objTm.tm_mday  );
	assert( get< 0 >( tOut3Part ).tm_hour == objTm.tm_hour  );
	assert( get< 0 >( tOut3Part ).tm_min == objTm.tm_min  );
	assert( get< 0 >( tOut3Part ).tm_sec == objTm.tm_sec  );
	assert( get< 1 >( tOut3Part ) == 20 );
	assert( get< 2 >( tOut3Part ) == 2.0 );

	tuple< float, string, struct tm, int, double > objReadOut;
	s << "select float_value, string_value, date_value, int_value, number_value from test_batched_table", into( objReadOut ), now, bRet, strErrMsg;
	assert( bRet );
	assert( get< 0 >( objReadOut ) == 2.0 );
	assert( get< 1 >( objReadOut ) == "123"  );
	assert( get< 2 >( objReadOut ).tm_year == objTm.tm_year  );
	assert( get< 2 >( objReadOut ).tm_mon == objTm.tm_mon  );
	assert( get< 2 >( objReadOut ).tm_mday == objTm.tm_mday  );
	assert( get< 2 >( objReadOut ).tm_hour == objTm.tm_hour  );
	assert( get< 2 >( objReadOut ).tm_min == objTm.tm_min  );
	assert( get< 2 >( objReadOut ).tm_sec == objTm.tm_sec  );
	assert( get< 3 >( objReadOut ) == 20 );
	assert( get< 4 >( objReadOut ) == 2.0 );
}

void TestMultipleRecordForTuple()
{
	test_db_config::DbConfig config;
	bool bRet = config.Init();
	assert( bRet == true );
	occiwrapper::ConnectionInfo info( config.GetStrIp(), 1521, config.GetUserName(), config.GetPassword(), config.GetSid() );
	occiwrapper::SessionFactory sf;
	occiwrapper::Session s = sf.Create( info );
	string strErrMsg;

	struct tm objTm;
	objTm.tm_year = 2014 - 1900;
	objTm.tm_mon = 11;
	objTm.tm_mday = 30;
	objTm.tm_hour = 10;
	objTm.tm_min = 43;
	objTm.tm_sec = 0;
	string str = "123";
	vector< tuple< float, string, struct tm, int, double > > vObj;
	//vObj.push_back( make_tuple( 1.0, "str1", objTm, 10, 1.0 ) );		// not supported in g++ 4.3
	//vObj.push_back( make_tuple( 2.0, "str2", objTm, 20, 2.0 ) );		// not supported in g++ 4.3
	//vObj.push_back( make_tuple( 3.0, "str3", objTm, 30, 3.0 ) );		// not supported in g++ 4.3
	tuple< float, string, struct tm, int, double > t1( 1.0, "str1", objTm, 10, 1.0 );
	tuple< float, string, struct tm, int, double > t2( 2.0, "str2", objTm, 20, 2.0 );
	tuple< float, string, struct tm, int, double > t3( 3.0, "str3", objTm, 30, 3.0 );
	vObj.push_back( t1 );
	vObj.push_back( t2 );
	vObj.push_back( t3 );

	s << "truncate table test_batched_table", now, bRet, strErrMsg;
	assert( bRet );
	s << "insert into test_batched_table( float_value, string_value, date_value, int_value, number_value ) values ( :1, :2, :3, :4, :5 )", batched_use( vObj ), now, bRet, strErrMsg;
	assert( bRet );

	tuple< float > tOut1;
	s << "select float_value from test_batched_table order by float_value asc", into( tOut1 ), now, bRet, strErrMsg;
	assert( get< 0 >( tOut1 ) == 1.0 );

	tuple< float, string > tOut2;
	s << "select float_value, string_value from test_batched_table order by float_value asc", into( tOut2 ), now, bRet, strErrMsg;
	assert( get< 0 >( tOut2 ) == 1.0 );
	assert( get< 1 >( tOut2 ) == "str1" );

	tuple< struct tm, int, double > tOut3;
	s << "select date_value, int_value, number_value from test_batched_table order by int_value asc", into( tOut3 ), now, bRet, strErrMsg;
	assert( get< 0 >( tOut3 ).tm_year == objTm.tm_year  );
	assert( get< 0 >( tOut3 ).tm_mon == objTm.tm_mon  );
	assert( get< 0 >( tOut3 ).tm_mday == objTm.tm_mday  );
	assert( get< 0 >( tOut3 ).tm_hour == objTm.tm_hour  );
	assert( get< 0 >( tOut3 ).tm_min == objTm.tm_min  );
	assert( get< 0 >( tOut3 ).tm_sec == objTm.tm_sec  );
	assert( get< 1 >( tOut3 ) == 10 );
	assert( get< 2 >( tOut3 ) == 1.0 );

	tuple< float, string, int, double > tOut4;
	s << "select float_value, string_value, int_value, number_value from test_batched_table order by float_value asc", into( tOut4 ), now, bRet, strErrMsg;
	assert( bRet );
	assert( get< 0 >( tOut4 ) == 1.0 );
	assert( get< 1 >( tOut4 ) == "str1" );
	assert( get< 2 >( tOut4 ) == 10 );
	assert( get< 3 >( tOut4 ) == 1.0 );

	tuple< float, string > tOut2Part;
	tuple< struct tm, int, double > tOut3Part;
	s << "select float_value, string_value, date_value, int_value, number_value from test_batched_table order by float_value asc", into( tOut2Part ), into( tOut3Part), now, bRet, strErrMsg;
	assert( bRet );
	assert( get< 0 >( tOut2Part ) == 1.0 );
	assert( get< 1 >( tOut2Part ) == "str1"  );
	assert( get< 0 >( tOut3Part ).tm_year == objTm.tm_year  );
	assert( get< 0 >( tOut3Part ).tm_mon == objTm.tm_mon  );
	assert( get< 0 >( tOut3Part ).tm_mday == objTm.tm_mday  );
	assert( get< 0 >( tOut3Part ).tm_hour == objTm.tm_hour  );
	assert( get< 0 >( tOut3Part ).tm_min == objTm.tm_min  );
	assert( get< 0 >( tOut3Part ).tm_sec == objTm.tm_sec  );
	assert( get< 1 >( tOut3Part ) == 10 );
	assert( get< 2 >( tOut3Part ) == 1.0 );

	tuple< float, string, struct tm, int, double > objReadOut;
	s << "select float_value, string_value, date_value, int_value, number_value from test_batched_table order by float_value asc", into( objReadOut ), now, bRet, strErrMsg;
	assert( bRet );
	assert( get< 0 >( objReadOut ) == 1.0 );
	assert( get< 1 >( objReadOut ) == "str1"  );
	assert( get< 2 >( objReadOut ).tm_year == objTm.tm_year  );
	assert( get< 2 >( objReadOut ).tm_mon == objTm.tm_mon  );
	assert( get< 2 >( objReadOut ).tm_mday == objTm.tm_mday  );
	assert( get< 2 >( objReadOut ).tm_hour == objTm.tm_hour  );
	assert( get< 2 >( objReadOut ).tm_min == objTm.tm_min  );
	assert( get< 2 >( objReadOut ).tm_sec == objTm.tm_sec  );
	assert( get< 3 >( objReadOut ) == 10 );
	assert( get< 4 >( objReadOut ) == 1.0 );

	vector< tuple< float, string, struct tm, int, double > > vObjOut;
	s << "select float_value, string_value, date_value, int_value, number_value from test_batched_table order by float_value asc", into( vObjOut ), now, bRet, strErrMsg;
	assert( bRet );
	assert( vObj.size() == 3 );
}

void TestTuple6()
{
	test_db_config::DbConfig config;
	bool bRet = config.Init();
	assert( bRet == true );
	occiwrapper::ConnectionInfo info( config.GetStrIp(), 1521, config.GetUserName(), config.GetPassword(), config.GetSid() );
	occiwrapper::SessionFactory sf;
	occiwrapper::Session s = sf.Create( info );
	string strErrMsg;

	struct tm objTm;
	objTm.tm_year = 2014 - 1900;
	objTm.tm_mon = 11;
	objTm.tm_mday = 30;
	objTm.tm_hour = 10;
	objTm.tm_min = 43;
	objTm.tm_sec = 0;
	string str = "123";

	s << strCreateTable, now, bRet, strErrMsg;
	s << "truncate table tbl_test_tuple_elements", now, bRet, strErrMsg;
	assert( bRet );

	// test 6 elements
	//tuple< int, float, string, struct tm, struct tm, double > t6 = make_tuple( 1, 1.1, "str1", objTm, objTm, 1.2 );
	tuple< int, float, string, struct tm, struct tm, double > t6( 1, 1.1, "str1", objTm, objTm, 1.2 );
	s << "insert into tbl_test_tuple_elements( t1, t2, t3, t4, t5, t6 ) values ( :1, :2, :3, :4, :5, :6 )", use( t6 ), now, bRet, strErrMsg;
	assert( bRet );

	tuple< int, float, string, struct tm, struct tm, double > t6Out;
	s << "select t1, t2, t3, t4, t5, t6 from tbl_test_tuple_elements", into( t6Out ), now, bRet, strErrMsg;
	assert( bRet );
	assert( get< 0 >( t6Out ) == 1 );
	assert( get< 1 >( t6Out ) == ( float )1.1 );
	assert( get< 2 >( t6Out ) == "str1" );
	assert( get< 3 >( t6Out ).tm_mon == 11 );
	assert( get< 4 >( t6Out ).tm_min == 43 );
	//assert( get< 3 >( t6Out ) == get< 4 >( t6Out ) );
	assert( get< 5 >( t6Out ) == 1.2 );

	s << "drop table tbl_test_tuple_elements", now, bRet, strErrMsg;
	assert( bRet );
}

void TestTuple7()
{
	test_db_config::DbConfig config;
	bool bRet = config.Init();
	assert( bRet == true );
	occiwrapper::ConnectionInfo info( config.GetStrIp(), 1521, config.GetUserName(), config.GetPassword(), config.GetSid() );
	occiwrapper::SessionFactory sf;
	occiwrapper::Session s = sf.Create( info );
	string strErrMsg;

	struct tm objTm;
	objTm.tm_year = 2014 - 1900;
	objTm.tm_mon = 11;
	objTm.tm_mday = 30;
	objTm.tm_hour = 10;
	objTm.tm_min = 43;
	objTm.tm_sec = 0;
	string str = "123";

	s << strCreateTable, now, bRet, strErrMsg;
	s << "truncate table tbl_test_tuple_elements", now, bRet, strErrMsg;
	assert( bRet );

	// test 6 elements
	tuple< int, float, string, struct tm, struct tm, double, double > t7( 1, 1.1, "str1", objTm, objTm, 1.2, 2.5 );
	s << "insert into tbl_test_tuple_elements( t1, t2, t3, t4, t5, t6, t7 ) values ( :1, :2, :3, :4, :5, :6, :7 )", use( t7 ), now, bRet, strErrMsg;
	assert( bRet );

	tuple< int, float, string, struct tm, struct tm, double, double > t7Out;
	s << "select t1, t2, t3, t4, t5, t6, t7 from tbl_test_tuple_elements", into( t7Out ), now, bRet, strErrMsg;
	assert( bRet );
	assert( get< 0 >( t7Out ) == 1 );
	assert( get< 1 >( t7Out ) == ( float )1.1 );
	assert( get< 2 >( t7Out ) == "str1" );
	assert( get< 3 >( t7Out ).tm_mon == 11 );
	assert( get< 4 >( t7Out ).tm_min == 43 );
	//assert( get< 3 >( t7Out ) == get< 4 >( t7Out ) );
	assert( get< 5 >( t7Out ) == 1.2 );
	assert( get< 6 >( t7Out ) == 2.5 );

	s << "drop table tbl_test_tuple_elements", now, bRet, strErrMsg;
	assert( bRet );
}

void TestTuple8()
{
	test_db_config::DbConfig config;
	bool bRet = config.Init();
	assert( bRet == true );
	occiwrapper::ConnectionInfo info( config.GetStrIp(), 1521, config.GetUserName(), config.GetPassword(), config.GetSid() );
	occiwrapper::SessionFactory sf;
	occiwrapper::Session s = sf.Create( info );
	string strErrMsg;

	struct tm objTm;
	objTm.tm_year = 2014 - 1900;
	objTm.tm_mon = 11;
	objTm.tm_mday = 30;
	objTm.tm_hour = 10;
	objTm.tm_min = 43;
	objTm.tm_sec = 0;

	s << strCreateTable, now, bRet, strErrMsg;
	s << "truncate table tbl_test_tuple_elements", now, bRet, strErrMsg;
	assert( bRet );

	// test 6 elements
	tuple< int, float, string, struct tm, struct tm, double, double, string > t8( 1, 1.1, "str1", objTm, objTm, 1.2, 2.5, "str8" );
	s << "insert into tbl_test_tuple_elements( t1, t2, t3, t4, t5, t6, t7, t8 ) values ( :1, :2, :3, :4, :5, :6, :7, :8 )", use( t8 ), now, bRet, strErrMsg;
	assert( bRet );

	tuple< int, float, string, struct tm, struct tm, double, double, string > t8Out;
	s << "select t1, t2, t3, t4, t5, t6, t7, t8 from tbl_test_tuple_elements", into( t8Out ), now, bRet, strErrMsg;
	assert( bRet );
	assert( get< 0 >( t8Out ) == 1 );
	assert( get< 1 >( t8Out ) == ( float )1.1 );
	assert( get< 2 >( t8Out ) == "str1" );
	assert( get< 3 >( t8Out ).tm_mon == 11 );
	assert( get< 4 >( t8Out ).tm_min == 43 );
	//assert( get< 3 >( t8Out ) == get< 4 >( t8Out ) );
	assert( get< 5 >( t8Out ) == 1.2 );
	assert( get< 6 >( t8Out ) == 2.5 );
	assert( get< 7 >( t8Out ) == "str8" );

	s << "drop table tbl_test_tuple_elements", now, bRet, strErrMsg;
	assert( bRet );
}

void TestTuple9()
{
	test_db_config::DbConfig config;
	bool bRet = config.Init();
	assert( bRet == true );
	occiwrapper::ConnectionInfo info( config.GetStrIp(), 1521, config.GetUserName(), config.GetPassword(), config.GetSid() );
	occiwrapper::SessionFactory sf;
	occiwrapper::Session s = sf.Create( info );
	string strErrMsg;

	struct tm objTm;
	objTm.tm_year = 2014 - 1900;
	objTm.tm_mon = 11;
	objTm.tm_mday = 30;
	objTm.tm_hour = 10;
	objTm.tm_min = 43;
	objTm.tm_sec = 0;

	s << strCreateTable, now, bRet, strErrMsg;
	s << "truncate table tbl_test_tuple_elements", now, bRet, strErrMsg;
	assert( bRet );

	// test 6 elements
	tuple< int, float, string, struct tm, struct tm, double, double, string, string > t9( 1, 1.1, "str1", objTm, objTm, 1.2, 2.5, "str8", "str9" );
	s << "insert into tbl_test_tuple_elements( t1, t2, t3, t4, t5, t6, t7, t8, t9 ) values ( :1, :2, :3, :4, :5, :6, :7, :8, :9 )", use( t9 ), now, bRet, strErrMsg;
	assert( bRet );

	tuple< int, float, string, struct tm, struct tm, double, double, string, string > t9Out;
	s << "select t1, t2, t3, t4, t5, t6, t7, t8, t9 from tbl_test_tuple_elements", into( t9Out ), now, bRet, strErrMsg;
	assert( bRet );
	assert( get< 0 >( t9Out ) == 1 );
	assert( get< 1 >( t9Out ) == ( float )1.1 );
	assert( get< 2 >( t9Out ) == "str1" );
	assert( get< 3 >( t9Out ).tm_mon == 11 );
	assert( get< 4 >( t9Out ).tm_min == 43 );
	//assert( get< 3 >( t9Out ) == get< 4 >( t9Out ) );
	assert( get< 5 >( t9Out ) == 1.2 );
	assert( get< 6 >( t9Out ) == 2.5 );
	assert( get< 7 >( t9Out ) == "str8" );
	assert( get< 8 >( t9Out ) == "str9" );

	s << "drop table tbl_test_tuple_elements", now, bRet, strErrMsg;
	assert( bRet );
}

void TestTuple10()
{
	test_db_config::DbConfig config;
	bool bRet = config.Init();
	assert( bRet == true );
	occiwrapper::ConnectionInfo info( config.GetStrIp(), 1521, config.GetUserName(), config.GetPassword(), config.GetSid() );
	occiwrapper::SessionFactory sf;
	occiwrapper::Session s = sf.Create( info );
	string strErrMsg;

	struct tm objTm;
	objTm.tm_year = 2014 - 1900;
	objTm.tm_mon = 11;
	objTm.tm_mday = 30;
	objTm.tm_hour = 10;
	objTm.tm_min = 43;
	objTm.tm_sec = 0;

	s << strCreateTable, now, bRet, strErrMsg;
	s << "truncate table tbl_test_tuple_elements", now, bRet, strErrMsg;
	assert( bRet );

	// test 10 elements
	tuple< int, float, string, struct tm, struct tm, double, double, string, string, string > t10( 1, 1.1, "str1", objTm, objTm, 1.2, 2.5, "str8", "str9", "str10" );
	s << "insert into tbl_test_tuple_elements( t1, t2, t3, t4, t5, t6, t7, t8, t9, t10 ) values ( :1, :2, :3, :4, :5, :6, :7, :8, :9, :10 )", use( t10 ), now, bRet, strErrMsg;
	s << "insert into tbl_test_tuple_elements( t1, t2, t3, t4, t5, t6, t7, t8, t9, t10 ) values ( :1, :2, :3, :4, :5, :6, :7, :8, :9, :10 )", use( t10 ), now, bRet, strErrMsg;
	assert( bRet );

	tuple< int, float, string, struct tm, struct tm, double, double, string, string, string > t10Out;
	s << "select t1, t2, t3, t4, t5, t6, t7, t8, t9, t10 from tbl_test_tuple_elements", into( t10Out ), now, bRet, strErrMsg;
	assert( bRet );
	assert( get< 0 >( t10Out ) == 1 );
	assert( get< 1 >( t10Out ) == ( float )1.1 );
	assert( get< 2 >( t10Out ) == "str1" );
	assert( get< 3 >( t10Out ).tm_mon == 11 );
	assert( get< 4 >( t10Out ).tm_min == 43 );
	//assert( get< 3 >( t10Out ) == get< 4 >( t10Out ) );			// not supported in g++ 4.3
	assert( get< 5 >( t10Out ) == 1.2 );
	assert( get< 6 >( t10Out ) == 2.5 );
	assert( get< 7 >( t10Out ) == "str8" );
	assert( get< 8 >( t10Out ) == "str9" );
	assert( get< 9 >( t10Out ) == "str10" );

	s << "drop table tbl_test_tuple_elements", now, bRet, strErrMsg;
	assert( bRet );
}

/***
*	@brief: test element for 6 to 50
*/
void TestTupleElement()
{
	TestTuple6();
	TestTuple7();
	TestTuple8();
	TestTuple9();
	TestTuple10();
}


void TestTupleVector()
{
	test_db_config::DbConfig config;
	bool bRet = config.Init();
	assert( bRet == true );
	occiwrapper::ConnectionInfo info( config.GetStrIp(), 1521, config.GetUserName(), config.GetPassword(), config.GetSid() );
	occiwrapper::SessionFactory sf;
	occiwrapper::Session s = sf.Create( info );
	string strErrMsg;

	struct tm objTm;
	objTm.tm_year = 2014 - 1900;
	objTm.tm_mon = 11;
	objTm.tm_mday = 30;
	objTm.tm_hour = 10;
	objTm.tm_min = 43;
	objTm.tm_sec = 0;

	s << strCreateTable, now, bRet, strErrMsg;

	// test 6 elements
	s << "truncate table tbl_test_tuple_elements", now, bRet, strErrMsg;
	assert( bRet );
	tuple< int, float, string, struct tm, struct tm, double > t6[ 2 ];
	t6[ 0 ] = make_tuple( 1, 1.1, "str1", objTm, objTm, 1.2 );
	t6[ 1 ] = make_tuple( 2, 2.1, "str2", objTm, objTm, 2.2 );
	vector< tuple< int, float, string, struct tm, struct tm, double > > v6( t6, t6 + 2 );
	s << "insert into tbl_test_tuple_elements( t1, t2, t3, t4, t5, t6 ) values ( :1, :2, :3, :4, :5, :6 )", batched_use( v6 ), now, bRet, strErrMsg;
	assert( bRet );
	vector< tuple< int, float, string, struct tm, struct tm, double > > v6Out;
	s << "select t1, t2, t3, t4, t5, t6 from tbl_test_tuple_elements", into( v6Out ), now, bRet, strErrMsg;
	assert( bRet );
	assert( v6Out.size() == 2 );

	// test 7 element
	s << "truncate table tbl_test_tuple_elements", now, bRet, strErrMsg;
	assert( bRet );
	tuple< int, float, string, struct tm, struct tm, double, double > t7[ 2 ];
	t7[ 0 ] = make_tuple( 1, 1.1, "str1", objTm, objTm, 1.2, 3.1 );
	t7[ 1 ] = make_tuple( 2, 2.1, "str2", objTm, objTm, 2.2, 3.2 );
	vector< tuple< int, float, string, struct tm, struct tm, double, double > > v7( t7, t7 + 2 );
	s << "insert into tbl_test_tuple_elements( t1, t2, t3, t4, t5, t6, t7 ) values ( :1, :2, :3, :4, :5, :6, :7 )", batched_use( v7 ), now, bRet, strErrMsg;
	assert( bRet );
	vector< tuple< int, float, string, struct tm, struct tm, double, double > > v7Out;
	s << "select t1, t2, t3, t4, t5, t6, t7 from tbl_test_tuple_elements", into( v7Out ), now, bRet, strErrMsg;
	assert( bRet );
	assert( v7Out.size() == 2 );

	// test 8 element
	s << "truncate table tbl_test_tuple_elements", now, bRet, strErrMsg;
	assert( bRet );
	tuple< int, float, string, struct tm, struct tm, double, double, string > t8[ 2 ];
	t8[ 0 ] = make_tuple( 1, 1.1, "str1", objTm, objTm, 1.2, 3.1, "str8_1" );
	t8[ 1 ] = make_tuple( 2, 2.1, "str2", objTm, objTm, 2.2, 3.2, "str8_2" );
	vector< tuple< int, float, string, struct tm, struct tm, double, double, string > > v8( t8, t8 + 2 );
	s << "insert into tbl_test_tuple_elements( t1, t2, t3, t4, t5, t6, t7, t8 ) values ( :1, :2, :3, :4, :5, :6, :7, :8 )", batched_use( v8 ), now, bRet, strErrMsg;
	assert( bRet );
	vector< tuple< int, float, string, struct tm, struct tm, double, double, string > > v8Out;
	s << "select t1, t2, t3, t4, t5, t6, t7, t8 from tbl_test_tuple_elements", into( v8Out ), now, bRet, strErrMsg;
	assert( bRet );
	assert( v8Out.size() == 2 );

	// test 9 element
	s << "truncate table tbl_test_tuple_elements", now, bRet, strErrMsg;
	assert( bRet );
	tuple< int, float, string, struct tm, struct tm, double, double, string, string > t9[ 2 ];
	t9[ 0 ] = make_tuple( 1, 1.1, "str1", objTm, objTm, 1.2, 3.1, "str8_1", "str9_1" );
	t9[ 1 ] = make_tuple( 2, 2.1, "str2", objTm, objTm, 2.2, 3.2, "str8_2", "str9_2" );
	vector< tuple< int, float, string, struct tm, struct tm, double, double, string, string > > v9( t9, t9 + 2 );
	s << "insert into tbl_test_tuple_elements( t1, t2, t3, t4, t5, t6, t7, t8, t9 ) values ( :1, :2, :3, :4, :5, :6, :7, :8, :9 )", batched_use( v9 ), now, bRet, strErrMsg;
	assert( bRet );
	vector< tuple< int, float, string, struct tm, struct tm, double, double, string, string > > v9Out;
	s << "select t1, t2, t3, t4, t5, t6, t7, t8, t9 from tbl_test_tuple_elements", into( v9Out ), now, bRet, strErrMsg;
	assert( bRet );
	assert( v9Out.size() == 2 );

	// test 10 element
	s << "truncate table tbl_test_tuple_elements", now, bRet, strErrMsg;
	assert( bRet );
	tuple< int, float, string, struct tm, struct tm, double, double, string, string, string > t10[ 2 ];
	t10[ 0 ] = make_tuple( 1, 1.1, "str1", objTm, objTm, 1.2, 3.1, "str8_1", "str9_1", "str10_1" );
	t10[ 1 ] = make_tuple( 2, 2.1, "str2", objTm, objTm, 2.2, 3.2, "str8_2", "str9_2", "str10_2" );
	vector< tuple< int, float, string, struct tm, struct tm, double, double, string, string, string > > v10( t10, t10 + 2 );
	s << "insert into tbl_test_tuple_elements( t1, t2, t3, t4, t5, t6, t7, t8, t9, t10 ) values ( :1, :2, :3, :4, :5, :6, :7, :8, :9, :10 )", batched_use( v10 ), now, bRet, strErrMsg;
	assert( bRet );
	vector< tuple< int, float, string, struct tm, struct tm, double, double, string, string, string > > v10Out;
	s << "select t1, t2, t3, t4, t5, t6, t7, t8, t9, t10 from tbl_test_tuple_elements", into( v10Out ), now, bRet, strErrMsg;
	assert( bRet );
	assert( v10Out.size() == 2 );

	s << "drop table tbl_test_tuple_elements", now, bRet, strErrMsg;
	assert( bRet );
}

void TestTupleList()
{
	test_db_config::DbConfig config;
	bool bRet = config.Init();
	assert( bRet == true );
	occiwrapper::ConnectionInfo info( config.GetStrIp(), 1521, config.GetUserName(), config.GetPassword(), config.GetSid() );
	occiwrapper::SessionFactory sf;
	occiwrapper::Session s = sf.Create( info );
	string strErrMsg;

	struct tm objTm;
	objTm.tm_year = 2014 - 1900;
	objTm.tm_mon = 11;
	objTm.tm_mday = 30;
	objTm.tm_hour = 10;
	objTm.tm_min = 43;
	objTm.tm_sec = 0;

	s << strCreateTable, now, bRet, strErrMsg;

	// test 1 elements
	s << "truncate table tbl_test_tuple_elements", now, bRet, strErrMsg;
	assert( bRet );
	tuple< int > t1[ 2 ];
	t1[ 0 ] = make_tuple( 1 );
	t1[ 1 ] = make_tuple( 2 );
	list< tuple< int > > v1( t1, t1 + 2 );
	s << "insert into tbl_test_tuple_elements( t1 ) values ( :1 )", batched_use( v1 ), now, bRet, strErrMsg;
	assert( bRet );
	list< tuple< int > > v1Out;
	s << "select t1 from tbl_test_tuple_elements", into( v1Out ), now, bRet, strErrMsg;
	assert( bRet );
	assert( v1Out.size() == 2 );

	// test 2 elements
	s << "truncate table tbl_test_tuple_elements", now, bRet, strErrMsg;
	assert( bRet );
	tuple< int, float > t2[ 2 ];
	t2[ 0 ] = make_tuple( 1, 1.1 );
	t2[ 1 ] = make_tuple( 2, 2.1 );
	list< tuple< int, float > > v2( t2, t2 + 2 );
	s << "insert into tbl_test_tuple_elements( t1, t2 ) values ( :1, :2 )", batched_use( v2 ), now, bRet, strErrMsg;
	assert( bRet );
	list< tuple< int, float > > v2Out;
	s << "select t1, t2 from tbl_test_tuple_elements", into( v2Out ), now, bRet, strErrMsg;
	assert( bRet );
	assert( v2Out.size() == 2 );

	// test 3 elements
	s << "truncate table tbl_test_tuple_elements", now, bRet, strErrMsg;
	assert( bRet );
	tuple< int, float, string > t3[ 2 ];
	t3[ 0 ] = make_tuple( 1, 1.1, "str1" );
	t3[ 1 ] = make_tuple( 2, 2.1, "str2" );
	list< tuple< int, float, string > > v3( t3, t3 + 2 );
	s << "insert into tbl_test_tuple_elements( t1, t2, t3 ) values ( :1, :2, :3 )", batched_use( v3 ), now, bRet, strErrMsg;
	assert( bRet );
	list< tuple< int, float, string > > v3Out;
	s << "select t1, t2, t3 from tbl_test_tuple_elements", into( v3Out ), now, bRet, strErrMsg;
	assert( bRet );
	assert( v3Out.size() == 2 );

	// test 4 elements
	s << "truncate table tbl_test_tuple_elements", now, bRet, strErrMsg;
	assert( bRet );
	tuple< int, float, string, struct tm > t4[ 2 ];
	t4[ 0 ] = make_tuple( 1, 1.1, "str1", objTm );
	t4[ 1 ] = make_tuple( 2, 2.1, "str2", objTm );
	list< tuple< int, float, string, struct tm > > v4( t4, t4 + 2 );
	s << "insert into tbl_test_tuple_elements( t1, t2, t3, t4 ) values ( :1, :2, :3, :4 )", batched_use( v4 ), now, bRet, strErrMsg;
	assert( bRet );
	list< tuple< int, float, string, struct tm > > v4Out;
	s << "select t1, t2, t3, t4 from tbl_test_tuple_elements", into( v4Out ), now, bRet, strErrMsg;
	assert( bRet );
	assert( v4Out.size() == 2 );

	// test 5 elements
	s << "truncate table tbl_test_tuple_elements", now, bRet, strErrMsg;
	assert( bRet );
	tuple< int, float, string, struct tm, struct tm > t5[ 2 ];
	t5[ 0 ] = make_tuple( 1, 1.1, "str1", objTm, objTm );
	t5[ 1 ] = make_tuple( 2, 2.1, "str2", objTm, objTm );
	list< tuple< int, float, string, struct tm, struct tm > > v5( t5, t5 + 2 );
	s << "insert into tbl_test_tuple_elements( t1, t2, t3, t4, t5 ) values ( :1, :2, :3, :4, :5 )", batched_use( v5 ), now, bRet, strErrMsg;
	assert( bRet );
	list< tuple< int, float, string, struct tm, struct tm > > v5Out;
	s << "select t1, t2, t3, t4, t5 from tbl_test_tuple_elements", into( v5Out ), now, bRet, strErrMsg;
	assert( bRet );
	assert( v5Out.size() == 2 );

	
	// test 6 elements
	s << "truncate table tbl_test_tuple_elements", now, bRet, strErrMsg;
	assert( bRet );
	tuple< int, float, string, struct tm, struct tm, double > t6[ 2 ];
	t6[ 0 ] = make_tuple( 1, 1.1, "str1", objTm, objTm, 1.2 );
	t6[ 1 ] = make_tuple( 2, 2.1, "str2", objTm, objTm, 2.2 );
	list< tuple< int, float, string, struct tm, struct tm, double > > v6( t6, t6 + 2 );
	s << "insert into tbl_test_tuple_elements( t1, t2, t3, t4, t5, t6 ) values ( :1, :2, :3, :4, :5, :6 )", batched_use( v6 ), now, bRet, strErrMsg;
	assert( bRet );
	list< tuple< int, float, string, struct tm, struct tm, double > > v6Out;
	s << "select t1, t2, t3, t4, t5, t6 from tbl_test_tuple_elements", into( v6Out ), now, bRet, strErrMsg;
	assert( bRet );
	assert( v6Out.size() == 2 );

	// test 7 element
	s << "truncate table tbl_test_tuple_elements", now, bRet, strErrMsg;
	assert( bRet );
	tuple< int, float, string, struct tm, struct tm, double, double > t7[ 2 ];
	t7[ 0 ] = make_tuple( 1, 1.1, "str1", objTm, objTm, 1.2, 3.1 );
	t7[ 1 ] = make_tuple( 2, 2.1, "str2", objTm, objTm, 2.2, 3.2 );
	list< tuple< int, float, string, struct tm, struct tm, double, double > > v7( t7, t7 + 2 );
	s << "insert into tbl_test_tuple_elements( t1, t2, t3, t4, t5, t6, t7 ) values ( :1, :2, :3, :4, :5, :6, :7 )", batched_use( v7 ), now, bRet, strErrMsg;
	assert( bRet );
	list< tuple< int, float, string, struct tm, struct tm, double, double > > v7Out;
	s << "select t1, t2, t3, t4, t5, t6, t7 from tbl_test_tuple_elements", into( v7Out ), now, bRet, strErrMsg;
	assert( bRet );
	assert( v7Out.size() == 2 );

	// test 8 element
	s << "truncate table tbl_test_tuple_elements", now, bRet, strErrMsg;
	assert( bRet );
	tuple< int, float, string, struct tm, struct tm, double, double, string > t8[ 2 ];
	t8[ 0 ] = make_tuple( 1, 1.1, "str1", objTm, objTm, 1.2, 3.1, "str8_1" );
	t8[ 1 ] = make_tuple( 2, 2.1, "str2", objTm, objTm, 2.2, 3.2, "str8_2" );
	list< tuple< int, float, string, struct tm, struct tm, double, double, string > > v8( t8, t8 + 2 );
	s << "insert into tbl_test_tuple_elements( t1, t2, t3, t4, t5, t6, t7, t8 ) values ( :1, :2, :3, :4, :5, :6, :7, :8 )", batched_use( v8 ), now, bRet, strErrMsg;
	assert( bRet );
	list< tuple< int, float, string, struct tm, struct tm, double, double, string > > v8Out;
	s << "select t1, t2, t3, t4, t5, t6, t7, t8 from tbl_test_tuple_elements", into( v8Out ), now, bRet, strErrMsg;
	assert( bRet );
	assert( v8Out.size() == 2 );

	// test 9 element
	s << "truncate table tbl_test_tuple_elements", now, bRet, strErrMsg;
	assert( bRet );
	tuple< int, float, string, struct tm, struct tm, double, double, string, string > t9[ 2 ];
	t9[ 0 ] = make_tuple( 1, 1.1, "str1", objTm, objTm, 1.2, 3.1, "str8_1", "str9_1" );
	t9[ 1 ] = make_tuple( 2, 2.1, "str2", objTm, objTm, 2.2, 3.2, "str8_2", "str9_2" );
	list< tuple< int, float, string, struct tm, struct tm, double, double, string, string > > v9( t9, t9 + 2 );
	s << "insert into tbl_test_tuple_elements( t1, t2, t3, t4, t5, t6, t7, t8, t9 ) values ( :1, :2, :3, :4, :5, :6, :7, :8, :9 )", batched_use( v9 ), now, bRet, strErrMsg;
	assert( bRet );
	list< tuple< int, float, string, struct tm, struct tm, double, double, string, string > > v9Out;
	s << "select t1, t2, t3, t4, t5, t6, t7, t8, t9 from tbl_test_tuple_elements", into( v9Out ), now, bRet, strErrMsg;
	assert( bRet );
	assert( v9Out.size() == 2 );

	// test 10 element
	s << "truncate table tbl_test_tuple_elements", now, bRet, strErrMsg;
	assert( bRet );
	tuple< int, float, string, struct tm, struct tm, double, double, string, string, string > t10[ 2 ];
	t10[ 0 ] = make_tuple( 1, 1.1, "str1", objTm, objTm, 1.2, 3.1, "str8_1", "str9_1", "str10_1" );
	t10[ 1 ] = make_tuple( 2, 2.1, "str2", objTm, objTm, 2.2, 3.2, "str8_2", "str9_2", "str10_2" );
	list< tuple< int, float, string, struct tm, struct tm, double, double, string, string, string > > v10( t10, t10 + 2 );
	s << "insert into tbl_test_tuple_elements( t1, t2, t3, t4, t5, t6, t7, t8, t9, t10 ) values ( :1, :2, :3, :4, :5, :6, :7, :8, :9, :10 )", batched_use( v10 ), now, bRet, strErrMsg;
	assert( bRet );
	list< tuple< int, float, string, struct tm, struct tm, double, double, string, string, string > > v10Out;
	s << "select t1, t2, t3, t4, t5, t6, t7, t8, t9, t10 from tbl_test_tuple_elements", into( v10Out ), now, bRet, strErrMsg;
	assert( bRet );
	assert( v10Out.size() == 2 );

	s << "drop table tbl_test_tuple_elements", now, bRet, strErrMsg;
	assert( bRet );
}