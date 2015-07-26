#pragma once

#include "OcciWrapper/Common.h"
#include "OcciWrapper/AbstractExtractor.h"
#include "OcciWrapper/StatementImpl.h"

namespace occiwrapper
{
	/***
	*	@brief: Extracts and converts data values from the result row returned by oracle.
	*			If NULL is received, the incoming val value is not changed and false is returned
	*	@add by CUCmehp.
	*/
	class Extractor 
		: public AbstractExtractor
	{
	public:
		/***
		*	@brief: Creates the Extractor.
		*/
		Extractor( oracle::occi::Environment* pOcciEnv, oracle::occi::Connection* pOcciConn );
		
		/***
		*	@brief: Destroys the Extractor.
		*/
		virtual ~Extractor();

		/***
		*	@brief: set occi result set
		*/
		virtual void SetOcciResultSet( oracle::occi::ResultSet* pOcciResultSet );

		/***
		*	@brief: extract data from buffer
		*	@add by CUCmehp
		*	@parameters:
		*		nPos: oracle parameter index.
		*		pBuf: data buffer.
		*		nBufLength: each buffer length.
		*		pLength: all data length for retrieving.
		*		pInd: buffer to decalare the retrieving data is NULL or not.
		*		type: oracle data type
		*/
		virtual void Extract(std::size_t nPos, void* pBuf, const size_t nBufLength, UInt16* pLength, Int16* pInd, enum oracle::occi::Type type );

		/***
		*	@brief: get extract data buffer
		*	@add by CUCmehp
		*	@parameters:
		*		nPos: index of data buffer
		*/
		virtual shared_ptr< OcciDataBuffer > GetExatractDataBuffer( size_t nPos );

		/***
		*	@brief: get all extract data buffer
		*	@add by CUCmehp
		*/
		std::vector< shared_ptr< OcciDataBuffer > >& GetExatractDataBuffers();

	private:
		// Prevent VC8 warning "operator= could not be generated"
		Extractor& operator = ( const Extractor& );

	private:
		// oracle result set
		oracle::occi::ResultSet* m_pOcciResultSet;

		// oracle environment
		oracle::occi::Environment* m_pOcciEnv;

		// oracle connection
		oracle::occi::Connection* m_pOcciConn;

		// data buffer for extraction
		std::vector< shared_ptr< OcciDataBuffer > > m_vExtractVecDataBuf;

	};
} 