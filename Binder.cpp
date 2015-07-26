#include "OcciWrapper/Binder.h"
#include <memory.h>

occiwrapper::Binder::Binder( oracle::occi::Statement* pOcciStat, oracle::occi::Environment* pEnv, oracle::occi::Connection* pOcciConn )
: m_pOcciStat( pOcciStat )
, m_pEnv( pEnv )
, m_pOcciConn( pOcciConn )
{
	this->m_bBindStart = false;
	this->m_vBindArray.clear();
	this->m_nDataCount = 0;
	this->m_eDataDirection = occiwrapper::PAR_IN;
}

occiwrapper::Binder::Binder()
{
	this->m_bBindStart = false;
	this->m_vBindArray.clear();
	this->m_nDataCount = 0;
	m_pOcciStat = NULL;
	m_pEnv = NULL;
}

occiwrapper::Binder::~Binder()
{
	this->m_vBindArray.clear();
}

void occiwrapper::Binder::SetStatement( oracle::occi::Statement* pOcciStat )
{
	this->m_pOcciStat = pOcciStat;
}

void occiwrapper::Binder::SetEnv( oracle::occi::Environment* p_env )
{
	this->m_pEnv = p_env;
}

oracle::occi::Environment* occiwrapper::Binder::GetEnv()
{
	return this->m_pEnv;
}

void occiwrapper::Binder::Bind( std::size_t pos, const Int8& val )
{
	try
	{
		if( this->IsIn() )
		{
			m_pOcciStat->setInt( pos, val );
		}
		if( this->IsOut() )
		{
			m_pOcciStat->registerOutParam( pos, oracle::occi::OCCIINT );
		}
	}
	catch( oracle::occi::SQLException& exc )
	{
		throw BindException( exc.what() );
	}
	catch( ... )
	{
		throw UnknownException( "unknown exception occurs, when bind Int8" );
	}
}

void occiwrapper::Binder::Retrieve( std::size_t nPos, Int8& val )
{
	if( !this->IsOut() )
	{
		throw BindException( "variable direction in can not retrieve value!" );
	}
	try
	{
		val = m_pOcciStat->getInt( nPos );
	}
	catch( oracle::occi::SQLException& exc )
	{
		throw BindException( exc.what() );
	}
	catch( ... )
	{
		throw UnknownException( "unknown exception occurs, when retrieve Int8" );
	}
}

void occiwrapper::Binder::Bind( std::size_t nPos, const UInt8& val )
{
	try
	{
		if( this->IsIn() )
		{
			m_pOcciStat->setUInt( nPos, val );
		}
		if( this->IsOut() )
		{
			m_pOcciStat->registerOutParam( nPos, oracle::occi::OCCIINT );
		}
	}
	catch( oracle::occi::SQLException& exc )
	{
		throw BindException( exc.what() );
	}
	catch( ... )
	{
		throw UnknownException( "unknown exception occurs, when bind UInt8" );
	}
}

void occiwrapper::Binder::Retrieve( std::size_t nPos, UInt8& val )
{
	if( !this->IsOut() )
	{
		throw BindException( "variable direction in can not retrieve value!" );
	}
	try
	{
		val = m_pOcciStat->getInt( nPos );
	}
	catch( oracle::occi::SQLException& exc )
	{
		throw BindException( exc.what() );
	}
	catch( ... )
	{
		throw UnknownException( "unknown exception occurs, when retrieve UInt8" );
	}
}

void occiwrapper::Binder::Bind( std::size_t nPos, const Int16& val )
{
	try
	{
		if( this->IsIn() )
		{
			this->m_pOcciStat->setInt( nPos, val );
		}
		if( this->IsOut() )
		{
			m_pOcciStat->registerOutParam( nPos, oracle::occi::OCCIINT );
		}
	}
	catch( oracle::occi::SQLException& exc )
	{
		throw BindException( exc.what() );
	}
	catch( ... )
	{
		throw UnknownException( "unknown exception occurs, when bind Int16" );
	}
}

void occiwrapper::Binder::Retrieve( std::size_t nPos, Int16& val )
{
	if( !this->IsOut() )
	{
		throw BindException( "variable direction in can not retrieve value!" );
	}
	try
	{
		val = m_pOcciStat->getInt( nPos );
	}
	catch( oracle::occi::SQLException& exc )
	{
		throw BindException( exc.what() );
	}
	catch( ... )
	{
		throw UnknownException( "unknown exception occurs, when retrieve Int16" );
	}
}

void occiwrapper::Binder::Bind( std::size_t nPos, const UInt16& val )
{
	try
	{
		if( this->IsIn() )
		{
			m_pOcciStat->setUInt( nPos, val );
		}
		if( this->IsOut() )
		{
			m_pOcciStat->registerOutParam( nPos, oracle::occi::OCCIINT );
		}
	}
	catch( oracle::occi::SQLException& exc )
	{
		throw BindException( exc.what() );
	}
	catch( ... )
	{
		throw UnknownException( "unknown exception occurs, when bind UInt16" );
	}
}

void occiwrapper::Binder::Retrieve( std::size_t nPos, UInt16& val )
{
	if( !this->IsOut() )
	{
		throw BindException( "variable direction in can not retrieve value!" );
	}
	try
	{
		val = m_pOcciStat->getInt( nPos );
	}
	catch( oracle::occi::SQLException& exc )
	{
		throw BindException( exc.what() );
	}
	catch( ... )
	{
		throw UnknownException( "unknown exception occurs, when retrieve UInt16" );
	}
}

void occiwrapper::Binder::Bind( std::size_t nPos, const Int32& val )
{
	try
	{
		if( this->IsIn() )
		{
			m_pOcciStat->setInt( nPos, val );
		}
		if( this->IsOut() )
		{
			m_pOcciStat->registerOutParam( nPos, oracle::occi::OCCIINT );
		}
	}
	catch( oracle::occi::SQLException& exc )
	{
		throw BindException( exc.what() );
	}
	catch( ... )
	{
		throw UnknownException( "unknown exception occurs, when bind Int32" );
	}
}

void occiwrapper::Binder::Retrieve( std::size_t nPos, Int32& val )
{
	if( !this->IsOut() )
	{
		throw BindException( "variable direction in can not retrieve value!" );
	}
	try
	{
		val = m_pOcciStat->getInt( nPos );
	}
	catch( oracle::occi::SQLException& exc )
	{
		throw BindException( exc.what() );
	}
	catch( ... )
	{
		throw UnknownException( "unknown exception occurs, when bind Int32" );
	}
}

void occiwrapper::Binder::Bind( std::size_t nPos, const UInt32& val )
{
	try
	{
		if( this->IsIn() )
		{
			m_pOcciStat->setUInt( nPos, val );
		}
		if( this->IsOut() )
		{
			m_pOcciStat->registerOutParam( nPos, oracle::occi::OCCIINT );
		}
	}
	catch( oracle::occi::SQLException& exc )
	{
		throw BindException( exc.what() );
	}
	catch( ... )
	{
		throw UnknownException( "unknown exception occurs, when bind UInt32" );
	}
}

void occiwrapper::Binder::Retrieve( std::size_t nPos, UInt32& val )
{
	if( !this->IsOut() )
	{
		throw BindException( "variable direction in can not retrieve value!" );
	}
	try
	{
		val = m_pOcciStat->getInt( nPos );
	}
	catch( oracle::occi::SQLException& exc )
	{
		throw BindException( exc.what() );
	}
	catch( ... )
	{
		throw UnknownException( "unknown exception occurs, when bind UInt32" );
	}
}

void occiwrapper::Binder::Bind( std::size_t nPos, const Int64& val )
{
	try
	{
		if( this->IsIn() )
		{
			m_pOcciStat->setNumber( nPos, oracle::occi::Number( ( long )val ) );
		} 
		if( this->IsOut() )
		{
			m_pOcciStat->registerOutParam( nPos, oracle::occi::OCCINUMBER );
		}
	}
	catch( oracle::occi::SQLException& exc )
	{
		throw BindException( exc.what() );
	}
	catch( ... )
	{
		throw UnknownException( "unknown exception occurs, when bind Int64" );
	}
}

void occiwrapper::Binder::Retrieve( std::size_t nPos, Int64& val )
{
	if( !this->IsOut() )
	{
		throw BindException( "variable direction in can not retrieve value!" );
	}
	try
	{
		val = ( Int64 )( long )m_pOcciStat->getNumber( nPos );
	}
	catch( oracle::occi::SQLException& exc )
	{
		throw BindException( exc.what() );
	}
	catch( ... )
	{
		throw UnknownException( "unknown exception occurs, when bind Int64" );
	}
}

void occiwrapper::Binder::Bind( std::size_t nPos, const UInt64& val )
{
	try
	{
		if( this->IsIn() )
		{
			m_pOcciStat->setNumber( nPos, oracle::occi::Number( ( unsigned long )val ) );
		} 
		if( this->IsOut() )
		{
			m_pOcciStat->registerOutParam( nPos, oracle::occi::OCCINUMBER );
		}
	}
	catch( oracle::occi::SQLException& exc )
	{
		throw BindException( exc.what() );
	}
	catch( ... )
	{
		throw UnknownException( "unknown exception occurs, when bind UInt64" );
	}
}

void occiwrapper::Binder::Retrieve( std::size_t nPos, UInt64& val )
{
	if( !this->IsOut() )
	{
		throw BindException( "variable direction in can not retrieve value!" );
	}
	try
	{
		val = ( UInt64 )( unsigned long )m_pOcciStat->getNumber( nPos );
	}
	catch( oracle::occi::SQLException& exc )
	{
		throw BindException( exc.what() );
	}
	catch( ... )
	{
		throw UnknownException( "unknown exception occurs, when bind UInt64" );
	}
}

void occiwrapper::Binder::Bind( std::size_t nPos, const bool& val )
{
	try
	{
		if( this->IsIn() )
		{
			m_pOcciStat->setInt( nPos, ( int )val );
		} 
		if( this->IsOut() )
		{
			m_pOcciStat->registerOutParam( nPos, oracle::occi::OCCIINT );
		}
	}
	catch( oracle::occi::SQLException& exc )
	{
		throw BindException( exc.what() );
	}
	catch( ... )
	{
		throw UnknownException( "unknown exception occurs, when bind UInt64" );
	}
}

void occiwrapper::Binder::Retrieve( std::size_t pos, bool& val )
{
	if( !this->IsOut() )
	{
		throw BindException( "variable direction in can not retrieve value!" );
	}
	try
	{
		val = m_pOcciStat->getInt( pos ) != 0;
	}
	catch( oracle::occi::SQLException& exc )
	{
		throw BindException( exc.what() );
	}
	catch( ... )
	{
		throw UnknownException( "unknown exception occurs, when bind bool" );
	}
}

void occiwrapper::Binder::Bind( std::size_t nPos, const float& val )
{
	try
	{
		if( this->IsIn() )
		{
			m_pOcciStat->setFloat( nPos, val );
		} 
		if( this->IsOut() )
		{
			m_pOcciStat->registerOutParam( nPos, oracle::occi::OCCIFLOAT );
		}
	}
	catch( oracle::occi::SQLException& exc )
	{
		throw BindException( exc.what() );
	}
	catch( ... )
	{
		throw UnknownException( "unknown exception occurs, when bind float" );
	}
}

void occiwrapper::Binder::Retrieve( std::size_t nPos, float& val )
{
	if( !this->IsOut() )
	{
		throw BindException( "variable direction in can not retrieve value!" );
	}
	try
	{
		val = m_pOcciStat->getFloat( nPos );
	}
	catch( oracle::occi::SQLException& exc )
	{
		throw BindException( exc.what() );
	}
	catch( ... )
	{
		throw UnknownException( "unknown exception occurs, when bind float" );
	}
}

void occiwrapper::Binder::Bind( std::size_t nPos, const double& val )
{
	try
	{
		if( this->IsIn() )
		{
			m_pOcciStat->setDouble( nPos, val );
		} 
		if( this->IsOut() )
		{
			m_pOcciStat->registerOutParam( nPos, oracle::occi::OCCINUMBER );
		}
	}
	catch( oracle::occi::SQLException& exc )
	{
		throw BindException( exc.what() );
	}
	catch( ... )
	{
		throw UnknownException( "unknown exception occurs, when bind double" );
	}
}

void occiwrapper::Binder::Retrieve( std::size_t nPos, double& val )
{
	if( !this->IsOut() )
	{
		throw BindException( "variable direction in can not retrieve value!" );
	}
	try
	{
		val = ( double )m_pOcciStat->getNumber( nPos );
	}
	catch( oracle::occi::SQLException& exc )
	{
		throw BindException( exc.what() );
	}
	catch( ... )
	{
		throw UnknownException( "unknown exception occurs, when bind double" );
	}
}

void occiwrapper::Binder::Bind( std::size_t nPos, const oracle::occi::Number& val )
{
	try
	{
		if( this->IsIn() )
		{
			m_pOcciStat->setNumber( nPos, val );
		} 
		if( this->IsOut() )
		{
			m_pOcciStat->registerOutParam( nPos, oracle::occi::OCCINUMBER );
		}
	}
	catch( oracle::occi::SQLException& exc )
	{
		throw BindException( exc.what() );
	}
	catch( ... )
	{
		throw UnknownException( "unknown exception occurs, when bind double" );
	}
}

void occiwrapper::Binder::Retrieve( std::size_t nPos, oracle::occi::Number& val )
{
	if( !this->IsOut() )
	{
		throw BindException( "variable direction in can not retrieve value!" );
	}
	try
	{
		val = m_pOcciStat->getNumber( nPos );
	}
	catch( oracle::occi::SQLException& exc )
	{
		throw BindException( exc.what() );
	}
	catch( ... )
	{
		throw UnknownException( "unknown exception occurs, when bind Number" );
	}
}

void occiwrapper::Binder::Bind( std::size_t nPos, const std::string& val )
{
	try
	{
		if( this->IsIn() )
		{
			m_pOcciStat->setString( nPos, val );
		} 
		if( this->IsOut() )
		{
			m_pOcciStat->registerOutParam( nPos, oracle::occi::OCCISTRING, 4000 );
		}
	}
	catch( oracle::occi::SQLException& exc )
	{
		throw BindException( exc.what() );
	}
	catch( ... )
	{
		throw UnknownException( "unknown exception occurs, when bind string" );
	}
}

void occiwrapper::Binder::Retrieve( std::size_t nPos, string& val )
{
	if( !this->IsOut() )
	{
		throw BindException( "variable direction in can not retrieve value!" );
	}
	try
	{
		val = m_pOcciStat->getString( nPos );
	}
	catch( oracle::occi::SQLException& exc )
	{
		throw BindException( exc.what() );
	}
	catch( ... )
	{
		throw UnknownException( "unknown exception occurs, when retrieve string" );
	}
}

void occiwrapper::Binder::Bind( std::size_t nPos, const struct tm& val )
{
	try
	{
		if( this->IsIn() )
		{
			m_pOcciStat->setDate( nPos, occiwrapper::ToDate( val, this->m_pEnv ) );
		} 
		if( this->IsOut() )
		{
			m_pOcciStat->registerOutParam( nPos, oracle::occi::OCCIDATE );
		}
	}
	catch( oracle::occi::SQLException& exc )
	{
		throw BindException( exc.what() );
	}
	catch( ... )
	{
		throw UnknownException( "unknown exception occurs, when bind tm" );
	}
}

void occiwrapper::Binder::Retrieve( std::size_t nPos, struct tm& val )
{
	if( !this->IsOut() )
	{
		throw BindException( "variable direction in can not retrieve value!" );
	}
	try
	{
		oracle::occi::Date tmp = m_pOcciStat->getDate( nPos );
		const_cast< struct tm& >( val ) = occiwrapper::GetTm( tmp );
	}
	catch( oracle::occi::SQLException& exc )
	{
		throw BindException( exc.what() );
	}
	catch( ... )
	{
		throw UnknownException( "unknown exception occurs, when retrieve tm" );
	}
}

void occiwrapper::Binder::Bind( std::size_t nPos, const Blob& blob )
{
	try
	{
		if( this->IsIn() )
		{
			if( blob.size() != 0 )
			{
				throw BindException( "binding blob to statement, but blob is not null!" );
			}
			oracle::occi::Blob _blob;
			_blob.setEmpty( m_pOcciConn );
			m_pOcciStat->setBlob( nPos, _blob );
		} 
		if( this->IsOut() )
		{
			m_pOcciStat->registerOutParam( nPos, oracle::occi::OCCIBLOB );
		}
	}
	catch( BindException& exc )
	{
		throw exc;
	}
	catch( oracle::occi::SQLException& exc )
	{
		throw BindException( exc.what() );
	}
	catch( ... )
	{
		throw UnknownException( "unknown exception occurs, when bind blob" );
	}
}

void occiwrapper::Binder::Retrieve( std::size_t nPos, Blob& val )
{
	if( !this->IsOut() )
	{
		throw BindException( "variable direction in can not retrieve value!" );
	}
	try
	{
		oracle::occi::Blob tmp = m_pOcciStat->getBlob( nPos );
		unsigned char strBuf[ 10240 ];
		memset( strBuf, 0, 10240 );

		unsigned int nOffset = 1;
		unsigned int nRet = 0;
		while( ( nRet = tmp.read( 10240, strBuf, 10240, nOffset ) ) > 0  )
		{
			nOffset += nRet;
			val.AppendRaw( ( char* )strBuf, nRet );
		}
	}
	catch( oracle::occi::SQLException& exc )
	{
		throw BindException( exc.what() );
	}
	catch( ... )
	{
		throw UnknownException( "unknown exception occurs, when retrieve blob" );
	}
}

void occiwrapper::Binder::Bind(std::size_t nPos, const Clob& clob )
{
	try
	{
		if( this->IsIn() )
		{
			if( clob.size() != 0 )
			{
				throw BindException( "binding clob to statement, but clob is not null!" );
			}
			oracle::occi::Clob _clob;
			_clob.setEmpty( m_pOcciConn );
			m_pOcciStat->setClob( nPos, _clob );
		} 
		if( this->IsOut() )
		{
			m_pOcciStat->registerOutParam( nPos, oracle::occi::OCCICLOB );
		}
	}
	catch( BindException& exc )
	{
		throw exc;
	}
	catch( oracle::occi::SQLException& exc )
	{
		throw BindException( exc.what() );
	}
	catch( ... )
	{
		throw UnknownException( "unknown exception occurs, when bind clob" );
	}
}

void occiwrapper::Binder::Retrieve(std::size_t nPos, Clob& val)
{
	if( !this->IsOut() )
	{
		throw BindException( "variable direction in can not retrieve value!" );
	}
	try
	{
		oracle::occi::Clob tmp = m_pOcciStat->getClob( nPos );
		unsigned char strBuf[ 10240 ];
		memset( strBuf, 0, 10240 );

		unsigned int nOffset = 1;
		unsigned int nRet = 0;
		while( ( nRet = tmp.read( 10240, strBuf, 10240, nOffset ) ) > 0  )
		{
			nOffset += nRet;
			val.AppendRaw( ( char* )strBuf, nRet );
		}
	}
	catch( oracle::occi::SQLException& exc )
	{
		throw BindException( exc.what() );
	}
	catch( ... )
	{
		throw UnknownException( "unknown exception occurs, when retrieve clob" );
	}
}

void occiwrapper::Binder::Bind( std::size_t nPos, const char* const& str )
{
	if( str == NULL )
	{
		throw BindException( "str is NULL" );
	}
	string tmp( str );
	Bind( nPos, tmp );
}

void occiwrapper::Binder::Retrieve( std::size_t nPos, const char* const& val )
{
	if( !this->IsOut() )
	{
		throw BindException( "variable direction in can not retrieve value!" );
	}
	throw BindException( "can not retrieve to a const char array!");
}



void occiwrapper::Binder::BatchedBind( std::size_t pos, void* p_buf, const size_t each_buf_length, UInt16* p_length, Int16* p_Ind, enum oracle::occi::Type type )
{
	this->m_vBindArray.push_back( shared_ptr< OcciDataBuffer >( new OcciDataBuffer( p_buf, p_length, p_Ind, each_buf_length, type ) ) );
	const std::size_t _index = m_vBindArray.size() - 1;
	try
	{
		m_pOcciStat->setDataBuffer( pos, m_vBindArray[ _index ]->m_pBuffer, type, each_buf_length, m_vBindArray[ _index ]->m_pDataLength, p_Ind );
	}
	catch( oracle::occi::SQLException& exc )
	{
		throw BindException( exc.what() );
	}
	catch( ... )
	{
		throw UnknownException( "unknown exception occurs, when bind string" );
	}
}

oracle::occi::Connection* occiwrapper::Binder::GetOcciConn()
{
	return m_pOcciConn;
}
