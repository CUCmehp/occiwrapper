#include <vector>
#include <assert.h>
#include "OcciWrapper/OcciWrapper.h"
#include <fstream>
#include "DbConfig.h"
#include <string.h>
#include <stdio.h>

#pragma warning( disable : 4244 )

using namespace std;


void TestLobBase()
{
	std::string strDigit = "1234567890";
	std::string strAlpha = "abcdefghijklmnopqrstuvwxyz";
	std::vector<char> vecAlpha( strAlpha.begin(), strAlpha.end() );
	std::vector<char> vecDigit( strDigit.begin(), strDigit.end() );

	occiwrapper::LobBase blobNumStr( strDigit.c_str(), strDigit.size() );
	assert( blobNumStr.size() == strDigit.size() );
	assert( 0 == strncmp( strDigit.c_str(), blobNumStr.RawContent(), strDigit.size() ) );
	assert( *blobNumStr.begin() == '1' );
	assert( *( blobNumStr.end()-1 ) == '0' );
	occiwrapper::LobBase blobNumVec( vecDigit );
	assert( blobNumVec.size() == vecDigit.size() );
	assert( blobNumVec == blobNumStr );
	blobNumVec.Swap( blobNumStr );
	assert( blobNumVec.size() == blobNumStr.size() );
	assert( blobNumVec == blobNumStr );

	occiwrapper::LobBase blobChrStr( strAlpha.c_str(), strAlpha.size() );
	occiwrapper::LobBase blobChrVec( vecAlpha );
	assert( blobChrStr.size() == strAlpha.size() );
	assert( 0 == strncmp( strAlpha.c_str(), blobChrStr.RawContent(), strAlpha.size() ) );
	assert( *blobChrStr.begin() == 'a' );
	assert( *(blobChrStr.end()-1) == 'z' );
	assert( blobChrStr == blobChrVec );

	blobNumStr.Swap( blobChrStr );
	assert( blobNumStr != blobChrStr );
	assert( &blobNumStr != &blobChrStr );
	assert( blobNumStr.content() != blobChrStr.content() );
	assert( &blobNumStr.content() != &blobChrStr.content() );
	assert( blobNumStr == blobChrVec );
}

void TestBlob()
{
	std::string strDigit = "1234567890";
	std::string strAlpha = "abcdefghijklmnopqrstuvwxyz";
	std::vector<char> vecAlpha( strAlpha.begin(), strAlpha.end() );
	std::vector<char> vecDigit( strDigit.begin(), strDigit.end() );

	occiwrapper::Blob blobNumStr( strDigit.c_str(), strDigit.size() );
	assert( blobNumStr.size() == strDigit.size() );
	assert( 0 == strncmp( strDigit.c_str(), blobNumStr.RawContent(), strDigit.size() ) );
	assert( *blobNumStr.begin() == '1' );
	assert( *( blobNumStr.end()-1 ) == '0' );
	occiwrapper::Blob blobNumVec( vecDigit );
	assert( blobNumVec.size() == vecDigit.size() );
	assert( blobNumVec == blobNumStr );
	blobNumVec.Swap( blobNumStr );
	assert( blobNumVec.size() == blobNumStr.size() );
	assert( blobNumVec == blobNumStr );

	occiwrapper::Blob blobChrStr( strAlpha.c_str(), strAlpha.size() );
	occiwrapper::Blob blobChrVec( vecAlpha );
	assert( blobChrStr.size() == strAlpha.size() );
	assert( 0 == strncmp( strAlpha.c_str(), blobChrStr.RawContent(), strAlpha.size() ) );
	assert( *blobChrStr.begin() == 'a' );
	assert( *(blobChrStr.end()-1) == 'z' );
	assert( blobChrStr == blobChrVec );
	
	blobNumStr.Swap( blobChrStr );
	assert( blobNumStr != blobChrStr );
	assert( &blobNumStr != &blobChrStr );
	assert( blobNumStr.content() != blobChrStr.content() );
	assert( &blobNumStr.content() != &blobChrStr.content() );
	assert( blobNumStr == blobChrVec );
}

void WriteToLobBase( occiwrapper::BinaryWriter& writer )
{
	writer << true;
	writer << false;
	writer << 'a';

	writer << ( short ) -100;
	writer << ( unsigned short ) 50000;
	writer << -123456;
	writer << ( unsigned ) 123456;

	writer << ( occiwrapper::Int64 ) -1234567890;
	writer << ( occiwrapper::UInt64 ) 1234567890;

	writer << ( float ) 1.5;
	writer << ( double ) -1.5;

	writer << "foo";
	writer << "";

	writer << std::string( "bar" );
	writer << std::string();

	writer.write7BitEncoded( ( occiwrapper::UInt32 )100 );
	writer.write7BitEncoded( ( occiwrapper::UInt32 )1000 );
	writer.write7BitEncoded( ( occiwrapper::UInt32 )10000 );
	writer.write7BitEncoded( ( occiwrapper::UInt32 )100000 );
	writer.write7BitEncoded( ( occiwrapper::UInt32 )1000000 );

	writer.write7BitEncoded( ( occiwrapper::UInt64 )100 );
	writer.write7BitEncoded( ( occiwrapper::UInt64 )1000 );
	writer.write7BitEncoded( ( occiwrapper::UInt64 )10000 );
	writer.write7BitEncoded( ( occiwrapper::UInt64 )100000 );
	writer.write7BitEncoded( ( occiwrapper::UInt64 )1000000 );

	writer.writeRaw( "RAW" );
}

void ReadFromLobBase( occiwrapper::BinaryReader& reader )
{
	bool b = false;
	reader >> b;
	assert (b);
	reader >> b;
	assert (!b);

	char c = ' ';
	reader >> c;
	assert (c == 'a');

	short shortv = 0;
	reader >> shortv;
	assert (shortv == -100);

	unsigned short ushortv = 0;
	reader >> ushortv;
	assert (ushortv == 50000);

	int intv = 0;
	reader >> intv;
	assert (intv == -123456);

	unsigned uintv = 0;
	reader >> uintv;
	assert (uintv == 123456);

	occiwrapper::Int64 int64v = 0;
	reader >> int64v;
	assert (int64v == -1234567890);

	occiwrapper::UInt64 uint64v = 0;
	reader >> uint64v;
	assert (uint64v == 1234567890);

	float floatv = 0.0;
	reader >> floatv;
	assert (floatv == 1.5);

	double doublev = 0.0;
	reader >> doublev;
	assert (doublev == -1.5);

	std::string str;
	reader >> str;
	assert (str == "foo");
	reader >> str;
	assert (str == "");

	reader >> str;
	assert (str == "bar");
	reader >> str;
	assert (str == "");

	occiwrapper::UInt32 uint32v;
	reader.read7BitEncoded(uint32v);
	assert (uint32v == 100);
	reader.read7BitEncoded(uint32v);
	assert (uint32v == 1000);
	reader.read7BitEncoded(uint32v);
	assert (uint32v == 10000);
	reader.read7BitEncoded(uint32v);
	assert (uint32v == 100000);
	reader.read7BitEncoded(uint32v);
	assert (uint32v == 1000000);

	reader.read7BitEncoded(uint64v);
	assert (uint64v == 100);
	reader.read7BitEncoded(uint64v);
	assert (uint64v == 1000);
	reader.read7BitEncoded(uint64v);
	assert (uint64v == 10000);
	reader.read7BitEncoded(uint64v);
	assert (uint64v == 100000);
	reader.read7BitEncoded(uint64v);
	assert (uint64v == 1000000);

	reader.readRaw(3, str);
	assert (str == "RAW");
}

void TestBlobStreams()
{
	occiwrapper::Blob blob;
	assert( 0 == blob.size() );

	
	occiwrapper::LobBaseOutputStream bos( blob );
	occiwrapper::BinaryWriter bw( bos );

	assert( 0 == blob.size() );
	WriteToLobBase( bw );
	assert( blob.size() > 0 );

	occiwrapper::LobBaseInputStream bis( blob );
	occiwrapper::BinaryReader br( bis );
	ReadFromLobBase( br );

	occiwrapper::Blob binaryBlob;
	assert( binaryBlob.size() == 0 );
	occiwrapper::LobBaseOutputStream binaryBos( binaryBlob );
	occiwrapper::BinaryWriter binaryBosWriter( binaryBos );
	
	//Test Binary InputStream
	ifstream fin( "InputPic.jpg", ios::in | ios::binary );
	while( !fin.eof() )
	{
		char buf[ 1024 ];
		memset( buf, 0, 1024 );
		fin.read( buf, 1024 );
		binaryBosWriter.writeRaw( buf, fin.gcount() );
	}
	fin.close();

	occiwrapper::LobBaseInputStream binaryBis( binaryBlob );
	occiwrapper::BinaryReader binaryBosReader( binaryBis );
	//Test Binary OutputStream
	ofstream fout( "OutputPic.jpg", ios::out | ios::binary );
	while( !binaryBosReader.stream().eof() )
	{
		char buf[ 1024 ];
		memset( buf, 0, 1024 );
		binaryBosReader.readRaw( buf, 1024 );
		fout.write( buf, binaryBosReader.stream().gcount() );
	}
	fout.close();
}

void TestSingleBlob()
{
	test_db_config::DbConfig config;
	bool bRet = config.Init();
	assert( bRet == true );
	occiwrapper::ConnectionInfo info( config.GetStrIp(), 1521, config.GetUserName(), config.GetPassword(), config.GetSid() );
	occiwrapper::SessionFactory sf;
	occiwrapper::Session s = sf.Create( info );
	string strErrMsg;

	s << "truncate table test_blob", now, bRet, strErrMsg;
	assert( bRet );
	s << "insert into test_blob( objs ) values( empty_blob() )", now, bRet, strErrMsg;
	assert( bRet );

	occiwrapper::Blob singleBlob;
	s.SetAutoCommit( false );
	s << "select objs from test_blob where rownum <= 1 for update", into( singleBlob ), now, bRet, strErrMsg;
	assert( bRet );
	//Test Binary InputStream
	ifstream fin( "InputPic.jpg", ios::in | ios::binary );
	occiwrapper::LobBaseOutputStream bos( singleBlob );
	occiwrapper::BinaryWriter bw( bos );
	while( !fin.eof() )
	{
		char buf[ 1024 ];
		memset( buf, 0, 1024 );
		fin.read( buf, 1024 );
		bw.writeRaw( buf, fin.gcount() );
	}
	fin.close();
	singleBlob.UpdateToOracle();
	s.Commit();

	occiwrapper::Blob singleBlobRead;
	s << "select objs from test_blob", into( singleBlobRead ), now, bRet, strErrMsg;
	occiwrapper::LobBaseInputStream bin( singleBlobRead );
	ofstream fout( "OutputPic.jpg", ios::out | ios::binary );
	while( !bin.eof() )
	{
		char buf[ 1024 ];
		memset( buf, 0, 1024 );
		bin.read( buf, 1024 );
		fout.write( buf, bin.gcount() );
	}
	fout.close();
}

void TestVectorBlob()
{
	test_db_config::DbConfig config;
	bool bRet = config.Init();
	assert( bRet == true );
	occiwrapper::ConnectionInfo info( config.GetStrIp(), 1521, config.GetUserName(), config.GetPassword(), config.GetSid() );
	occiwrapper::SessionFactory sf;
	occiwrapper::Session s = sf.Create( info );
	string strErrMsg;

	s << "truncate table test_blob", now, bRet, strErrMsg;
	assert( bRet );
	s << "insert into test_blob( objs ) values( to_blob( '48656C6C6520576F726C642047' ) )", now, bRet, strErrMsg;
	assert( bRet );
	s << "insert into test_blob( objs ) values( to_blob( '48656C6C6520576F726C642048' ) )", now, bRet, strErrMsg;
	assert( bRet );

	vector< occiwrapper::Blob > vBlob;
	s.SetAutoCommit( false );
	s << "select objs from test_blob for update", into( vBlob ), now, bRet, strErrMsg;
	assert( bRet );
	for( size_t i = 0; i < vBlob.size(); ++ i )
	{
		string str = "----update added!";
		vBlob[ i ].AppendRaw( str.c_str(), str.size() );
		vBlob[ i ].UpdateToOracle();
	}
	s.Commit();

	vBlob.clear();
	s << "select objs from test_blob", into( vBlob ), now, bRet, strErrMsg;
	s.Commit();
	assert( vBlob.size() == 2 );
	string str = "";
	for( size_t i = 0; i < vBlob[ 0 ].content().size(); ++ i )
	{
		str.push_back( vBlob[ 0 ].content().at( i ) );
	}
	assert( str == "Helle World G----update added!");
	vBlob.clear();


	vector< tuple< occiwrapper::Blob > > vTuple;
	s << "select objs from test_blob", into( vTuple ), now, bRet, strErrMsg;
	assert( vTuple.size() == 2 );
	string str1 = "";
	string str2 = "";
	occiwrapper::Blob b1 = get< 0 >( vTuple[ 0 ] );
	for( size_t i = 0; i < b1.content().size(); ++ i )
	{
		str1.push_back( b1.content().at( i ) );
	}
	occiwrapper::Blob b2 = get< 0 >( vTuple[ 1 ] );
	for( size_t i = 0; i < b2.content().size(); ++ i )
	{
		str2.push_back( b2.content().at( i ) );
	}
	assert( str1 == "Helle World G----update added!" );
	assert( str2 == "Helle World H----update added!" );
}

void TestBlobBinding()
{
	test_db_config::DbConfig config;
	bool bRet = config.Init();
	assert( bRet == true );
	occiwrapper::ConnectionInfo info( config.GetStrIp(), 1521, config.GetUserName(), config.GetPassword(), config.GetSid() );
	occiwrapper::SessionFactory sf;
	occiwrapper::Session s = sf.Create( info );
	string strErrMsg;

	s << "truncate table test_blob", now, bRet, strErrMsg;
	assert( bRet );
	occiwrapper::Blob blob;
	s << "insert into test_blob( objs ) values( :1 )", use( blob ), now, bRet, strErrMsg;
	assert( bRet == true );

	occiwrapper::Blob singleBlob;
	s.SetAutoCommit( false );
	s << "select objs from test_blob where rownum <= 1 for update", into( singleBlob ), now, bRet, strErrMsg;
	assert( bRet );
	//Test Binary InputStream
	ifstream fin( "InputPic.jpg", ios::in | ios::binary );
	occiwrapper::LobBaseOutputStream bos( singleBlob );
	occiwrapper::BinaryWriter bw( bos );
	while( !fin.eof() )
	{
		char buf[ 1024 ];
		memset( buf, 0, 1024 );
		fin.read( buf, 1024 );
		bw.writeRaw( buf, fin.gcount() );
	}
	fin.close();
	singleBlob.UpdateToOracle();
	s.Commit();

	occiwrapper::Blob singleBlobRead;
	s << "select objs from test_blob", into( singleBlobRead ), now, bRet, strErrMsg;
	occiwrapper::LobBaseInputStream bin( singleBlobRead );
	ofstream fout( "OutputPic.jpg", ios::out | ios::binary );
	while( !bin.eof() )
	{
		char buf[ 1024 ];
		memset( buf, 0, 1024 );
		bin.read( buf, 1024 );
		fout.write( buf, bin.gcount() );
	}
	fout.close();
}

void TestVecBlobBinding()
{
	test_db_config::DbConfig config;
	bool bRet = config.Init();
	assert( bRet == true );
	occiwrapper::ConnectionInfo info( config.GetStrIp(), 1521, config.GetUserName(), config.GetPassword(), config.GetSid() );
	occiwrapper::SessionFactory sf;
	occiwrapper::Session s = sf.Create( info );
	string strErrMsg;

	s << "truncate table test_blob_with_id", now, bRet, strErrMsg;
	assert( bRet );
	int id[] = { 1, 2 };
	vector< int > vId( id, id + 2 );
	s << "insert into test_blob_with_id( id, objs ) values( :1, empty_blob() )", batched_use( vId ), now, bRet, strErrMsg;
	assert( bRet == true );

	vector< occiwrapper::Blob > vBlob;
	vId.clear();
	s.SetAutoCommit( false );
	s << "select id, objs from test_blob_with_id for update", into( vId ), into( vBlob ), now, bRet, strErrMsg;
	assert( bRet );
	for( size_t i = 0; i < vBlob.size(); ++ i )
	{
		string str = "----update added!";
		vBlob[ i ].AppendRaw( str.c_str(), str.size() );
		vBlob[ i ].UpdateToOracle();
	}
	s.Commit();

	vBlob.clear();
	vId.clear();
	s.SetAutoCommit( true );
	s << "select id, objs from test_blob_with_id", into( vId ), into( vBlob ), now, bRet, strErrMsg;
	assert( vId.size() == 2 );
	assert( vBlob.size() == 2 );
	string str = "";
	for( size_t i = 0; i < vBlob[ 0 ].content().size(); ++ i )
	{
		str.push_back(  vBlob[ 0 ].content().at( i ) );
	}
	assert( str == "----update added!" );
	vBlob.clear();
}


void TestListBlob()
{
	test_db_config::DbConfig config;
	bool bRet = config.Init();
	assert( bRet == true );
	occiwrapper::ConnectionInfo info( config.GetStrIp(), 1521, config.GetUserName(), config.GetPassword(), config.GetSid() );
	occiwrapper::SessionFactory sf;
	occiwrapper::Session s = sf.Create( info );
	string strErrMsg;

	s << "truncate table test_blob_with_id", now, bRet, strErrMsg;
	assert( bRet );
	int id[] = { 1, 2 };
	list< int > vId( id, id + 2 );
	s << "insert into test_blob_with_id( id, objs ) values( :1, empty_blob() )", batched_use( vId ), now, bRet, strErrMsg;
	assert( bRet == true );

	list< occiwrapper::Blob > lBlob;
	vId.clear();
	s.SetAutoCommit( false );
	s << "select id, objs from test_blob_with_id for update", into( vId ), into( lBlob ), now, bRet, strErrMsg;
	assert( bRet );
	for( list< occiwrapper::Blob >::iterator it = lBlob.begin(); it != lBlob.end(); it ++ )
	{
		string str = "----update added!";
		it->AppendRaw( str.c_str(), str.size() );
		it->UpdateToOracle();
	}
	s.Commit();

	lBlob.clear();
	vId.clear();
	s.SetAutoCommit( true );
	s << "select id, objs from test_blob_with_id", into( vId ), into( lBlob ), now, bRet, strErrMsg;
	assert( vId.size() == 2 );
	assert( lBlob.size() == 2 );
	string str = "";
	for( size_t i = 0; i < lBlob.begin()->content().size(); ++ i )
	{
		str.push_back( lBlob.begin()->content().at( i ) );
	}
	assert( str == "----update added!" );
	lBlob.clear();

	list< tuple< int, occiwrapper::Blob > > vTuple;
	s << "select id, objs from test_blob_with_id", into( vTuple ), now, bRet, strErrMsg;
	assert( vId.size() == 2 );
	assert( vTuple.size() == 2 );
	for( list< tuple< int, occiwrapper::Blob > >::iterator it = vTuple.begin(); it != vTuple.end(); it ++ )
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
void TestProcedureBlob()
{
	test_db_config::DbConfig config;
	bool bRet = config.Init();
	assert( bRet == true );
	occiwrapper::ConnectionInfo info( config.GetStrIp(), 1521, config.GetUserName(), config.GetPassword(), config.GetSid() );
	occiwrapper::SessionFactory sf;
	occiwrapper::Session s = sf.Create( info );
	string strErrMsg;

	occiwrapper::Blob blob;
	s << "begin P_TEST_BLOB_PROCEDURE( :1 ); end;", use( blob, occiwrapper::PAR_OUT ), now, bRet, strErrMsg;
	assert( bRet );

	string str = "";
	for( size_t i = 0; i < blob.content().size(); ++ i )
	{
		str.push_back( blob.content().at( i ) );
	}
	assert( str == "Helle World G" );
}