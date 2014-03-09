#include "Extractor.h"

occiwrapper::Extractor::Extractor( oracle::occi::Environment* pOcciEnv )
	: m_pOcciResultSet( NULL )
	, m_pOcciEnv( pOcciEnv )
{

}

occiwrapper::Extractor::~Extractor()
{

}

void occiwrapper::Extractor::SetOcciResultSet( oracle::occi::ResultSet* pOcciResultSet )
{
	this->m_pOcciResultSet = pOcciResultSet;
}

void occiwrapper::Extractor::Extract( std::size_t nPos, void* pBuf, const size_t nBufLength, UInt16* pLength, Int16* pInd, enum oracle::occi::Type type )
{
	if( m_pOcciResultSet == NULL )
	{
		throw InvalidResultSetException( "the ResultSet is NULL,when extract" );
	}

	this->m_vExtractVecDataBuf.push_back( shared_ptr< OcciDataBuffer >( new OcciDataBuffer( pBuf, pLength, pInd, nBufLength ) ) );
	const std::size_t _index = m_vExtractVecDataBuf.size() - 1;
	assert( _index >= 0 );
	try
	{
		m_pOcciResultSet->setDataBuffer( nPos, m_vExtractVecDataBuf[ _index ]->m_pBuffer, type, nBufLength, m_vExtractVecDataBuf[ _index ]->m_pDataLength, pInd );
	}
	catch( oracle::occi::SQLException& exc )
	{
		throw BindException( exc.what() );
	}
	catch( ... )
	{
		throw UnknownException( "unknown exception occurs, when bind string" );
	}
};

shared_ptr< occiwrapper::OcciDataBuffer > occiwrapper::Extractor::GetExatractDataBuffer( size_t nPos )
{
	assert( m_vExtractVecDataBuf.size() > nPos - 1 );
	return m_vExtractVecDataBuf[ nPos - 1 ];
}

std::vector< shared_ptr< occiwrapper::OcciDataBuffer > >& occiwrapper::Extractor::GetExatractDataBuffers()
{
	return m_vExtractVecDataBuf;
}