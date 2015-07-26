#include "TestObj.h"
#include "DbConfig.h"
#include "OcciWrapper/OcciWrapper.h"


string strCreateTable = "create table tbl_person( id varchar2(255), name varchar2(255), age int, birth_date date )";


class CPerson
{
public:

	CPerson()
	{
		this->strId = "";
		this->strName = "";
		this->nAge = 0;
		this->tmBirthDate.tm_year = 0;
		this->tmBirthDate.tm_mon = 0;
		this->tmBirthDate.tm_mday = 0;
		this->tmBirthDate.tm_hour = 0;
		this->tmBirthDate.tm_min = 0;
		this->tmBirthDate.tm_sec = 0;
	}

	CPerson( struct tm tmBirthDate, string strId = "", string strName = "", int nAge = 0 )
	{
		this->strId = strId;
		this->strName = strName;
		this->nAge = nAge;
		this->tmBirthDate.tm_year = tmBirthDate.tm_year;
		this->tmBirthDate.tm_mon = tmBirthDate.tm_mon;
		this->tmBirthDate.tm_mday = tmBirthDate.tm_mday;
		this->tmBirthDate.tm_hour = tmBirthDate.tm_hour;
		this->tmBirthDate.tm_min = tmBirthDate.tm_min;
		this->tmBirthDate.tm_sec = tmBirthDate.tm_sec;
	}

	string strId;
	string strName;
	int	   nAge;
	struct tm tmBirthDate;
};

namespace occiwrapper
{
	/***
	*	@add by CUCmehp
	*/
	template <>
	class TypeHandler< CPerson >
	{
	public:
		static void bind(std::size_t pos, const CPerson& obj, AbstractBinder* pBinder)
		{
			assert( pBinder != 0 );
			pBinder->Bind( pos ++, obj.strId );
			pBinder->Bind( pos ++, obj.strName );
			pBinder->Bind( pos ++, obj.nAge );
			pBinder->Bind( pos ++, obj.tmBirthDate );
		}

		static void retrieve( std::size_t pos, CPerson& obj, AbstractBinder* pBinder )
		{
			assert( pBinder != 0 );
			pBinder->Retrieve( pos ++, obj.strId );
			pBinder->Retrieve( pos ++, obj.strName );
			pBinder->Retrieve( pos ++, obj.nAge );
			pBinder->Retrieve( pos ++, obj.tmBirthDate );
		}

		static std::size_t size()
		{
			return 4;
		}

		static void extract( std::size_t pos, AbstractExtractor* pExt )
		{
			TypeHandler< string >::extract( pos ++, pExt );
			TypeHandler< string >::extract( pos ++, pExt );
			TypeHandler< int >::extract( pos ++, pExt );
			TypeHandler< struct tm >::extract( pos ++, pExt );
		}

		static void fetch( std::size_t pos, CPerson& objResult, AbstractExtractor* pExtractor, vector< shared_ptr< OcciDataBuffer > >&  vecDataBuf, size_t nFetchedNum )
		{
			vector< vector< shared_ptr < OcciDataBuffer > > > vBufs;
			for( size_t i = 0; i < vecDataBuf.size(); ++ i )
			{
				vector< shared_ptr< OcciDataBuffer > > vBuf;
				vBuf.push_back( vecDataBuf[ i ] );
				vBufs.push_back( vBuf );
			}
			TypeHandler< string >::fetch( pos ++, objResult.strId, pExtractor, vBufs[ 0 ], nFetchedNum );
			TypeHandler< string >::fetch( pos ++, objResult.strName, pExtractor, vBufs[ 1 ], nFetchedNum );
			TypeHandler< int >::fetch( pos ++, objResult.nAge, pExtractor, vBufs[ 2 ], nFetchedNum );
			TypeHandler< struct tm >::fetch( pos ++, objResult.tmBirthDate, pExtractor, vBufs[ 3 ], nFetchedNum );
		}

	private:
		TypeHandler();
		~TypeHandler();
		TypeHandler(const TypeHandler&);
		TypeHandler& operator = (const TypeHandler&);
	};

	// specialize list for batched bind
	template <>
	class TypeHandler< vector< CPerson > >
	{
	public:
		static void bind(std::size_t pos, const vector< CPerson >& obj, AbstractBinder* pBinder)
		{
			assert( pBinder != 0 );
			vector< string > copy_obj1;
			vector< string > copy_obj2;
			vector< int > copy_obj3;
			vector< struct tm > copy_obj4;
			for( vector< CPerson >::const_iterator it = obj.begin(); it != obj.end(); ++ it )
			{
				copy_obj1.push_back( it->strId );
				copy_obj2.push_back( it->strName );
				copy_obj3.push_back( it->nAge );
				copy_obj4.push_back( it->tmBirthDate );
			}
			TypeHandler< vector< string > >::bind( pos ++, copy_obj1, pBinder );
			TypeHandler< vector< string > >::bind( pos ++, copy_obj2, pBinder );
			TypeHandler< vector< int > >::bind( pos ++, copy_obj3, pBinder );
			TypeHandler< vector< struct tm > >::bind( pos ++, copy_obj4, pBinder );
		}

		static void extract( std::size_t pos, AbstractExtractor* pExtractor )
		{
			assert( pExtractor != 0 );
			TypeHandler< vector< string > >::extract( pos ++, pExtractor );
			TypeHandler< vector< string > >::extract( pos ++, pExtractor );
			TypeHandler< vector< int > >::extract( pos ++, pExtractor );
			TypeHandler< vector< struct tm > >::extract( pos ++, pExtractor );
		}

		static void fetch( std::size_t nPos, vector< CPerson >& vResult, AbstractExtractor* pExtractor, vector< shared_ptr< OcciDataBuffer > >& vDataBuf, size_t nFetchedNum )
		{
			assert( pExtractor != 0 );
			assert( vDataBuf.size() == 4 );
			for( size_t i = 0; i < nFetchedNum; ++ i )
			{
				int nIndex = 0;
				string obj1 = TypeConvertor< string >::retrieve( ( ( void* )( ( char* )vDataBuf[ nIndex ]->m_pBuffer + vDataBuf[ nIndex ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ nIndex ]->m_pDataLength + i ), *( vDataBuf[ nIndex ]->m_pInd + i ) );
				nIndex ++;
				string obj2 = TypeConvertor< string >::retrieve( ( ( void* )( ( char* )vDataBuf[ nIndex ]->m_pBuffer + vDataBuf[ nIndex ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ nIndex ]->m_pDataLength + i ), *( vDataBuf[ nIndex ]->m_pInd + i ) );
				nIndex ++;
				int obj3 = TypeConvertor< int >::retrieve( ( ( void* )( ( char* )vDataBuf[ nIndex ]->m_pBuffer + vDataBuf[ nIndex ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ nIndex ]->m_pDataLength + i ), *( vDataBuf[ nIndex ]->m_pInd + i ) );
				nIndex ++;
				struct tm obj4 = TypeConvertor< struct tm >::retrieve( ( ( void* )( ( char* )vDataBuf[ nIndex ]->m_pBuffer + vDataBuf[ nIndex ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ nIndex ]->m_pDataLength + i ), *( vDataBuf[ nIndex ]->m_pInd + i ) );
				nIndex ++;
				CPerson objTmp;
				objTmp.strId = obj1;
				objTmp.strName = obj2;
				objTmp.nAge = obj3;
				objTmp.tmBirthDate = obj4;
				vResult.push_back( objTmp );
			}
		}

		static std::size_t size()
		{
			return TypeHandler< CPerson >::size();
		}

	private:
		TypeHandler();
		~TypeHandler();
		TypeHandler(const TypeHandler&);
		TypeHandler& operator = (const TypeHandler&);
	};

	// specialize list for batched bind
	template <>
	class TypeHandler< list< CPerson > >
	{
	public:
		static void bind(std::size_t pos, const list< CPerson >& obj, AbstractBinder* pBinder)
		{
			assert( pBinder != 0 );
			list< string > copy_obj1;
			list< string > copy_obj2;
			list< int > copy_obj3;
			list< struct tm > copy_obj4;
			for( list< CPerson >::const_iterator it = obj.begin(); it != obj.end(); ++ it )
			{
				copy_obj1.push_back( it->strId );
				copy_obj2.push_back( it->strName );
				copy_obj3.push_back( it->nAge );
				copy_obj4.push_back( it->tmBirthDate );
			}
			TypeHandler< list< string > >::bind( pos ++, copy_obj1, pBinder );
			TypeHandler< list< string > >::bind( pos ++, copy_obj2, pBinder );
			TypeHandler< list< int > >::bind( pos ++, copy_obj3, pBinder );
			TypeHandler< list< struct tm > >::bind( pos ++, copy_obj4, pBinder );
		}

		static void extract( std::size_t pos, AbstractExtractor* pExtractor )
		{
			assert( pExtractor != 0 );
			TypeHandler< list< string > >::extract( pos ++, pExtractor );
			TypeHandler< list< string > >::extract( pos ++, pExtractor );
			TypeHandler< list< int > >::extract( pos ++, pExtractor );
			TypeHandler< list< struct tm > >::extract( pos ++, pExtractor );
		}

		static void fetch( std::size_t nPos, list< CPerson >& vResult, AbstractExtractor* pExtractor, vector< shared_ptr< OcciDataBuffer > >& vDataBuf, size_t nFetchedNum )
		{
			assert( pExtractor != 0 );
			assert( vDataBuf.size() == 4 );
			for( size_t i = 0; i < nFetchedNum; ++ i )
			{
				int nIndex = 0;
				string obj1 = TypeConvertor< string >::retrieve( ( ( void* )( ( char* )vDataBuf[ nIndex ]->m_pBuffer + vDataBuf[ nIndex ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ nIndex ]->m_pDataLength + i ), *( vDataBuf[ nIndex ]->m_pInd + i ) );
				nIndex ++;
				string obj2 = TypeConvertor< string >::retrieve( ( ( void* )( ( char* )vDataBuf[ nIndex ]->m_pBuffer + vDataBuf[ nIndex ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ nIndex ]->m_pDataLength + i ), *( vDataBuf[ nIndex ]->m_pInd + i ) );
				nIndex ++;
				int obj3 = TypeConvertor< int >::retrieve( ( ( void* )( ( char* )vDataBuf[ nIndex ]->m_pBuffer + vDataBuf[ nIndex ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ nIndex ]->m_pDataLength + i ), *( vDataBuf[ nIndex ]->m_pInd + i ) );
				nIndex ++;
				struct tm obj4 = TypeConvertor< struct tm >::retrieve( ( ( void* )( ( char* )vDataBuf[ nIndex ]->m_pBuffer + vDataBuf[ nIndex ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ nIndex ]->m_pDataLength + i ), *( vDataBuf[ nIndex ]->m_pInd + i ) );
				nIndex ++;
				CPerson objTmp;
				objTmp.strId = obj1;
				objTmp.strName = obj2;
				objTmp.nAge = obj3;
				objTmp.tmBirthDate = obj4;
				vResult.push_back( objTmp );
			}
		}

		static std::size_t size()
		{
			return TypeHandler< CPerson >::size();
		}

	private:
		TypeHandler();
		~TypeHandler();
		TypeHandler(const TypeHandler&);
		TypeHandler& operator = (const TypeHandler&);
	};
}




void TestSingleObj()
{
	test_db_config::DbConfig config;
	bool bRet = config.Init();
	assert( bRet == true );
	occiwrapper::ConnectionInfo info( config.GetStrIp(), 1521, config.GetUserName(), config.GetPassword(), config.GetSid() );
	occiwrapper::SessionFactory sf;
	occiwrapper::Session s = sf.Create( info );
	string strErrMsg;
	struct tm objTm;
	objTm.tm_year = 1984 - 1900;
	objTm.tm_mon = 10;
	objTm.tm_mday = 6;
	objTm.tm_hour = objTm.tm_min = objTm.tm_sec = 0;
	s << strCreateTable, now, bRet, strErrMsg;
	s << "truncate table tbl_person", now, bRet, strErrMsg;
	assert( bRet );

	s << "insert into tbl_person( id, name, age, birth_date ) values( :1, :2, :3, :4 )", use( "422300198011030001" ), use( "Tom" ), use( 35 ), use( objTm ), now, bRet, strErrMsg;
	assert( bRet );

	objTm.tm_year = 2014 - 1900;
	objTm.tm_mon = 11;
	objTm.tm_mday = 30;
	CPerson objPersion1( objTm, "422300201412300002", "Jim", 1 );
	s << "insert into tbl_person( id, name, age, birth_date ) values( :1, :2, :3, :4 )", use( objPersion1 ) , now, bRet, strErrMsg;
	assert( bRet );


	int nSelectAge = 35;
	string strId = "";
	string strName = "";
	int nAge = 0;
	struct tm tmBirthDay;
	s << "select id, name, age, birth_date from tbl_person where age = :1", use( nSelectAge ), into( strId ), into( strName ), into( nAge ), into( tmBirthDay ), now, bRet, strErrMsg;
	assert( bRet );
	assert( nAge == nSelectAge );
	assert( strName == "Tom" );
	assert( strId == "422300198011030001" );
	assert( tmBirthDay.tm_year == 1984 - 1900 );
	assert( tmBirthDay.tm_mon == 10 );
	assert( tmBirthDay.tm_mday == 6 );

	nSelectAge = 1;
	CPerson objPersion2;
	s << "select id, name, age, birth_date from tbl_person where age = :1", use( nSelectAge ), into( objPersion2 ), now, bRet, strErrMsg;
	assert( bRet );
	assert( objPersion2.nAge == nSelectAge );
	assert( objPersion2.strName == "Jim" );
	assert( objPersion2.strId == "422300201412300002" );
	assert( objPersion2.tmBirthDate.tm_year == 2014 - 1900 );
	assert( objPersion2.tmBirthDate.tm_mon == 11 );
	assert( objPersion2.tmBirthDate.tm_mday == 30 );

	s << "drop table tbl_person", now;
}


void TestObjectVector()
{
	test_db_config::DbConfig config;
	bool bRet = config.Init();
	assert( bRet == true );
	occiwrapper::ConnectionInfo info( config.GetStrIp(), 1521, config.GetUserName(), config.GetPassword(), config.GetSid() );
	occiwrapper::SessionFactory sf;
	occiwrapper::Session s = sf.Create( info );
	string strErrMsg;
	struct tm objTm;
	objTm.tm_year = 2010 - 1900;
	objTm.tm_mon = 10;
	objTm.tm_mday = 6;
	objTm.tm_hour = objTm.tm_min = objTm.tm_sec = 0;
	s << strCreateTable, now, bRet, strErrMsg;
	s << "truncate table tbl_person", now, bRet, strErrMsg;
	assert( bRet );

	CPerson objPersion1( objTm, "422300201010060001", "Tim", 4 );
	objTm.tm_year = 2014 - 1900;
	objTm.tm_mon = 11;
	objTm.tm_mday = 30;
	CPerson objPersion2( objTm, "422300201412300002", "Jim", 1 );
	vector< CPerson > vInsert;
	vInsert.push_back( objPersion1 );
	vInsert.push_back( objPersion2 );

	s << "insert into tbl_person( id, name, age, birth_date ) values( :1, :2, :3, :4 )", batched_use( vInsert ), now, bRet, strErrMsg;
	assert( bRet );

	vector< CPerson > vPerson;
	s << "select id, name, age, birth_date from tbl_person order by id asc", into( vPerson ), now, bRet, strErrMsg;
	assert( bRet );
	assert( vPerson.size() == 2 );
	assert( vPerson[ 0 ].strId == "422300201010060001" );
	assert( vPerson[ 0 ].strName == "Tim" );
	assert( vPerson[ 0 ].nAge == 4 );
	assert( vPerson[ 1 ].strId == "422300201412300002" );
	assert( vPerson[ 1 ].strName == "Jim" );
	assert( vPerson[ 1 ].nAge == 1 );
	s << "drop table tbl_person", now;
}

/***
*	@brief: test insert an object vector
*/
void TestObjectList()
{
	test_db_config::DbConfig config;
	bool bRet = config.Init();
	assert( bRet == true );
	occiwrapper::ConnectionInfo info( config.GetStrIp(), 1521, config.GetUserName(), config.GetPassword(), config.GetSid() );
	occiwrapper::SessionFactory sf;
	occiwrapper::Session s = sf.Create( info );
	string strErrMsg;
	struct tm objTm;
	objTm.tm_year = 2010 - 1900;
	objTm.tm_mon = 10;
	objTm.tm_mday = 6;
	objTm.tm_hour = objTm.tm_min = objTm.tm_sec = 0;
	s << strCreateTable, now, bRet, strErrMsg;
	s << "truncate table tbl_person", now, bRet, strErrMsg;
	assert( bRet );

	CPerson objPersion1( objTm, "422300201010060001", "Tim", 4 );
	objTm.tm_year = 2014 - 1900;
	objTm.tm_mon = 11;
	objTm.tm_mday = 30;
	CPerson objPersion2( objTm, "422300201412300002", "Jim", 1 );
	list< CPerson > vInsert;
	vInsert.push_back( objPersion1 );
	vInsert.push_back( objPersion2 );

	s << "insert into tbl_person( id, name, age, birth_date ) values( :1, :2, :3, :4 )", batched_use( vInsert ), now, bRet, strErrMsg;
	assert( bRet );

	list< CPerson > vPerson;
	s << "select id, name, age, birth_date from tbl_person order by id asc", into( vPerson ), now, bRet, strErrMsg;
	assert( bRet );
	assert( vPerson.size() == 2 );
	s << "drop table tbl_person", now;
}

