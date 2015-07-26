#include "TestClob.h"
#include <vector>
#include <assert.h>
#include "OcciWrapper/OcciWrapper.h"
#include <fstream>
#include "DbConfig.h"

void TestSingleClob()
{
	test_db_config::DbConfig config;
	bool bRet = config.Init();
	assert( bRet == true );
	occiwrapper::ConnectionInfo info( config.GetStrIp(), 1521, config.GetUserName(), config.GetPassword(), config.GetSid() );
	occiwrapper::SessionFactory sf( "ZHS16GBK", "ZHS16GBK" );	//set charset, as same as the db
	occiwrapper::Session s = sf.Create( info );
	string strErrMsg;

	s << "truncate table test_clob", now, bRet, strErrMsg;
	assert( bRet );
	s << "insert into test_clob( objs ) values( empty_clob() )", now, bRet, strErrMsg;
	assert( bRet );

	occiwrapper::Clob singleClob;
	s.SetAutoCommit( false );
	s << "select objs from test_clob where rownum <= 1 for update", into( singleClob ), now, bRet, strErrMsg;
	assert( bRet );
	//Test Binary InputStream
	ifstream fin( "InputTxt.txt", ios::in );
	occiwrapper::LobBaseOutputStream bos( singleClob );
	occiwrapper::BinaryWriter bw( bos );
	while( !fin.eof() )
	{
		char buf[ 1024 ];
		memset( buf, 0, 1024 );
		fin.read( buf, 1024 );
		bw.writeRaw( buf, fin.gcount() );
	}
	fin.close();
	singleClob.UpdateToOracle();
	s.Commit();

	occiwrapper::Clob singleClobRead;
	s << "select objs from test_clob", into( singleClobRead ), now, bRet, strErrMsg;
	occiwrapper::LobBaseInputStream bin( singleClobRead );
	ofstream fout( "OutputTxt.txt", ios::out );
	while( !bin.eof() )
	{
		char buf[ 1024 ];
		memset( buf, 0, 1024 );
		bin.read( buf, 1024 );
		fout.write( buf, bin.gcount() );
	}
	fout.close();
}

void TestVectorClob()
{
	test_db_config::DbConfig config;
	bool bRet = config.Init();
	assert( bRet == true );
	occiwrapper::ConnectionInfo info( config.GetStrIp(), 1521, config.GetUserName(), config.GetPassword(), config.GetSid() );
	occiwrapper::SessionFactory sf;
	occiwrapper::Session s = sf.Create( info );
	string strErrMsg;

	s << "truncate table test_clob", now, bRet, strErrMsg;
	assert( bRet );
	s << "insert into test_clob( objs ) values( to_clob( 'Helle World G' ) )", now, bRet, strErrMsg;
	assert( bRet );
	s << "insert into test_clob( objs ) values( to_clob( 'Helle World H' ) )", now, bRet, strErrMsg;
	assert( bRet );

	vector< occiwrapper::Clob > vClob;
	s.SetAutoCommit( false );
	s << "select objs from test_clob for update", into( vClob ), now, bRet, strErrMsg;
	assert( bRet );
	for( size_t i = 0; i < vClob.size(); ++ i )
	{
		string str = "----update added!";
		vClob[ i ].AppendRaw( str.c_str(), str.size() );
		vClob[ i ].UpdateToOracle();
	}
	s.Commit();

	vClob.clear();
	s << "select objs from test_clob", into( vClob ), now, bRet, strErrMsg;
	s.Commit();
	assert( vClob.size() == 2 );
	string str = "";
	for( size_t i = 0; i < vClob[ 0 ].content().size(); ++ i )
	{
		str.push_back( vClob[ 0 ].content().at( i ) );
	}
	assert( str == "Helle World G----update added!");
	vClob.clear();


	vector< tuple< occiwrapper::Clob > > vTuple;
	s << "select objs from test_clob", into( vTuple ), now, bRet, strErrMsg;
	assert( vTuple.size() == 2 );
	string str1 = "";
	string str2 = "";
	occiwrapper::Clob c1 = get< 0 >( vTuple[ 0 ] );
	for( size_t i = 0; i < c1.content().size(); ++ i )
	{
		str1.push_back( c1.content().at( i ) );
	}
	occiwrapper::Clob c2 = get< 0 >( vTuple[ 1 ] );
	for( size_t i = 0; i < c2.content().size(); ++ i )
	{
		str2.push_back( c2.content().at( i ) );
	}
	assert( str1 == "Helle World G----update added!" );
	assert( str2 == "Helle World H----update added!" );
}

void TestClobBinding()
{
	test_db_config::DbConfig config;
	bool bRet = config.Init();
	assert( bRet == true );
	occiwrapper::ConnectionInfo info( config.GetStrIp(), 1521, config.GetUserName(), config.GetPassword(), config.GetSid() );
	occiwrapper::SessionFactory sf;
	occiwrapper::Session s = sf.Create( info );
	string strErrMsg;

	s << "truncate table test_clob", now, bRet, strErrMsg;
	assert( bRet );
	occiwrapper::Clob clob;
	s << "insert into test_clob( objs ) values( :1 )", use( clob ), now, bRet, strErrMsg;
	assert( bRet == true );

	occiwrapper::Clob singleClob;
	s.SetAutoCommit( false );
	s << "select objs from test_clob where rownum <= 1 for update", into( singleClob ), now, bRet, strErrMsg;
	assert( bRet );
	//Test Binary InputStream
	ifstream fin( "InputTxt.txt", ios::in );
	occiwrapper::LobBaseOutputStream bos( singleClob );
	occiwrapper::BinaryWriter bw( bos );
	while( !fin.eof() )
	{
		char buf[ 1024 ];
		memset( buf, 0, 1024 );
		fin.read( buf, 1024 );
		bw.writeRaw( buf, fin.gcount() );
	}
	fin.close();
	singleClob.UpdateToOracle();
	s.Commit();

	occiwrapper::Clob singleClobRead;
	s << "select objs from test_clob", into( singleClobRead ), now, bRet, strErrMsg;
	occiwrapper::LobBaseInputStream bin( singleClobRead );
	ofstream fout( "OutputTxt.txt", ios::out | ios::binary );
	while( !bin.eof() )
	{
		char buf[ 1024 ];
		memset( buf, 0, 1024 );
		bin.read( buf, 1024 );
		fout.write( buf, bin.gcount() );
	}
	fout.close();
}


void TestVecClobBinding()
{
	test_db_config::DbConfig config;
	bool bRet = config.Init();
	assert( bRet == true );
	occiwrapper::ConnectionInfo info( config.GetStrIp(), 1521, config.GetUserName(), config.GetPassword(), config.GetSid() );
	occiwrapper::SessionFactory sf;
	occiwrapper::Session s = sf.Create( info );
	string strErrMsg;

	s << "truncate table test_clob_with_id", now, bRet, strErrMsg;
	assert( bRet );
	int id[] = { 1, 2 };
	vector< int > vId( id, id + 2 );
	s << "insert into test_clob_with_id( id, objs ) values( :1, empty_clob() )", batched_use( vId ), now, bRet, strErrMsg;
	assert( bRet == true );

	vector< occiwrapper::Clob > vClob;
	vId.clear();
	s.SetAutoCommit( false );
	s << "select id, objs from test_clob_with_id for update", into( vId ), into( vClob ), now, bRet, strErrMsg;
	assert( bRet );
	for( size_t i = 0; i < vClob.size(); ++ i )
	{
		string str = "----update added!";
		vClob[ i ].AppendRaw( str.c_str(), str.size() );
		vClob[ i ].UpdateToOracle();
	}
	s.Commit();

	vClob.clear();
	vId.clear();
	s.SetAutoCommit( true );
	s << "select id, objs from test_clob_with_id", into( vId ), into( vClob ), now, bRet, strErrMsg;
	assert( vId.size() == 2 );
	assert( vClob.size() == 2 );
	string str = "";
	for( size_t i = 0; i < vClob[ 0 ].content().size(); ++ i )
	{
		str.push_back(  vClob[ 0 ].content().at( i ) );
	}
	assert( str == "----update added!" );
	vClob.clear();
}


void TestListClob()
{
	test_db_config::DbConfig config;
	bool bRet = config.Init();
	assert( bRet == true );
	occiwrapper::ConnectionInfo info( config.GetStrIp(), 1521, config.GetUserName(), config.GetPassword(), config.GetSid() );
	occiwrapper::SessionFactory sf;
	occiwrapper::Session s = sf.Create( info );
	string strErrMsg;

	s << "truncate table test_clob_with_id", now, bRet, strErrMsg;
	assert( bRet );
	int id[] = { 1, 2 };
	list< int > vId( id, id + 2 );
	s << "insert into test_clob_with_id( id, objs ) values( :1, empty_clob() )", batched_use( vId ), now, bRet, strErrMsg;
	assert( bRet == true );

	list< occiwrapper::Clob > lClob;
	vId.clear();
	s.SetAutoCommit( false );
	s << "select id, objs from test_clob_with_id for update", into( vId ), into( lClob ), now, bRet, strErrMsg;
	assert( bRet );
	for( list< occiwrapper::Clob >::iterator it = lClob.begin(); it != lClob.end(); it ++ )
	{
		string str = "----update added!";
		it->AppendRaw( str.c_str(), str.size() );
		it->UpdateToOracle();
	}
	s.Commit();

	lClob.clear();
	vId.clear();
	s.SetAutoCommit( true );
	s << "select id, objs from test_clob_with_id", into( vId ), into( lClob ), now, bRet, strErrMsg;
	assert( vId.size() == 2 );
	assert( lClob.size() == 2 );
	string str = "";
	for( size_t i = 0; i < lClob.begin()->content().size(); ++ i )
	{
		str.push_back( lClob.begin()->content().at( i ) );
	}
	assert( str == "----update added!" );
	lClob.clear();

	list< tuple< int, occiwrapper::Clob > > vTuple;
	s << "select id, objs from test_clob_with_id", into( vTuple ), now, bRet, strErrMsg;
	assert( vId.size() == 2 );
	assert( vTuple.size() == 2 );
	for( list< tuple< int, occiwrapper::Clob > >::iterator it = vTuple.begin(); it != vTuple.end(); it ++ )
	{
		str = "";
		int id = get< 0 >( *it );
		for( size_t i = 0; i < get< 1 >( *it ).size(); ++ i )
		{
			str.push_back( get< 1 >( *it ).content().at( i ) );
		}
		assert( str == "----update added!" );
	}
}

// test procedure calling
void TestProcedureClob()
{
	test_db_config::DbConfig config;
	bool bRet = config.Init();
	assert( bRet == true );
	occiwrapper::ConnectionInfo info( config.GetStrIp(), 1521, config.GetUserName(), config.GetPassword(), config.GetSid() );
	occiwrapper::SessionFactory sf;
	occiwrapper::Session s = sf.Create( info );
	string strErrMsg;

	occiwrapper::Clob clob;
	s << "begin P_TEST_CLOB_PROCEDURE( :1 ); end;", use( clob, occiwrapper::PAR_OUT ), now, bRet, strErrMsg;
	assert( bRet );

	string str = "";
	for( size_t i = 0; i < clob.content().size(); ++ i )
	{
		str.push_back( clob.content().at( i ) );
	}
	assert( str == "Helle World G" );
}