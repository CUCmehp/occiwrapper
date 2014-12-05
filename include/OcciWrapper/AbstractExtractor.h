#pragma once
#include "OcciWrapper/Common.h"
#include <string>
#include "occiCommon.h"

namespace occiwrapper{
	
	/***
	*	@brief: extract data from occi data buffer
	*/
	class AbstractExtractor
	{
	public:
		/// Creates the AbstractExtractor.
		AbstractExtractor(){}
		
		/// Destroys the AbstractExtractor.
		virtual ~AbstractExtractor(){}

		/// Extracts
		virtual void Extract( std::size_t nPos, void* pBuf, const size_t nEachBufLength, UInt16* pLength, Int16* pInd, enum oracle::occi::Type type ) = 0;

		/// Get Data Buf from extractor
		virtual shared_ptr< OcciDataBuffer > GetExatractDataBuffer( size_t nPos ) = 0;
	};
}
