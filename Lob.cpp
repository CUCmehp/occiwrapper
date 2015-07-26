#include "OcciWrapper/Lob.h"
#include <memory.h>

occiwrapper::Blob::Blob()
	: LobBase()
{

}

occiwrapper::Blob::Blob(const std::vector<char>& content)
	: LobBase( content )
{

}

occiwrapper::Blob::Blob(const char* const pContent, std::size_t size)
	: LobBase( pContent, size )
{

}

occiwrapper::Blob::Blob(const std::string& content)
	: LobBase( content )
{

}

occiwrapper::Blob::Blob(const Blob& other)
{
	this->_pContent = other._pContent;
	this->m_occiBlob = other.m_occiBlob;
}

occiwrapper::Blob::~Blob()
{
	
}

occiwrapper::Blob& occiwrapper::Blob::operator = ( const occiwrapper::Blob& other)
{
	occiwrapper::Blob tmp( other );
	Swap( tmp );
	return *this;
}

void occiwrapper::Blob::Swap( occiwrapper::Blob& other)
{
	using std::swap;
	swap( _pContent, other._pContent );
	swap( m_occiBlob, other.m_occiBlob );
}

bool occiwrapper::Blob::operator == ( const occiwrapper::Blob& other ) const
{
	return *_pContent == *other._pContent;
}

bool occiwrapper::Blob::operator!=(const Blob& other) const
{
	return *_pContent != *other._pContent;
}

void occiwrapper::Blob::SetOcciBlob( oracle::occi::Blob& occiBlob)
{
	this->m_occiBlob = occiBlob;
}

void occiwrapper::Blob::UpdateToOracle()
{
	unsigned char buf[ 1024 ];
	size_t i = 0;
	size_t nCount = 1;
	for( i = 0; i < _pContent->size(); ++ i )
	{
		if( ( i != 0 && i % 1024 == 0 )  )
		{
			nCount += m_occiBlob.write( 1024, buf, 1024, nCount );
			memset( buf, 0, 1024 );
		}
		buf[ i % 1024 ] = ( unsigned char )_pContent->at( i );
	}
	if( i % 1024 != 0 )
	{
		m_occiBlob.write( i % 1024, buf, 1024, nCount );
	}
}


//////////////////////////////////////////////////////////////////////////////////
occiwrapper::Clob::Clob()
	: LobBase()
{

}

occiwrapper::Clob::Clob(const std::vector<char>& content)
	: LobBase( content )
{

}

occiwrapper::Clob::Clob(const char* const pContent, std::size_t size)
	: LobBase( pContent, size )
{

}

occiwrapper::Clob::Clob(const std::string& content)
	: LobBase( content )
{

}

occiwrapper::Clob::Clob( const occiwrapper::Clob& other)
{
	this->_pContent = other._pContent;
	this->m_occiClob = other.m_occiClob;
}

occiwrapper::Clob::~Clob()
{

}

occiwrapper::Clob& occiwrapper::Clob::operator = ( const occiwrapper::Clob& other)
{
	occiwrapper::Clob tmp( other );
	Swap( tmp );
	return *this;
}

void occiwrapper::Clob::Swap( occiwrapper::Clob& other)
{
	using std::swap;
	swap( _pContent, other._pContent );
	swap( m_occiClob, other.m_occiClob );
}

bool occiwrapper::Clob::operator == ( const occiwrapper::Clob& other ) const
{
	return *_pContent == *other._pContent;
}

bool occiwrapper::Clob::operator!=(const Clob& other) const
{
	return *_pContent != *other._pContent;
}

void occiwrapper::Clob::UpdateToOracle()
{
	unsigned char buf[ 1024 ];
	size_t i = 0;
	size_t nCount = 1;
	for( i = 0; i < _pContent->size(); ++ i )
	{
		if( ( i != 0 && i % 1024 == 0 )  )
		{
			nCount += m_occiClob.write( 1024, buf, 1024, nCount );
			memset( buf, 0, 1024 );
		}
		buf[ i % 1024 ] = ( unsigned char )_pContent->at( i );
	}
	if( i % 1024 != 0 )
	{
		m_occiClob.write( i % 1024, buf, 1024, nCount );
	}
}

void occiwrapper::Clob::SetOcciClob(oracle::occi::Clob& occiClob )
{
	this->m_occiClob = occiClob;
}


