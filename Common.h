#pragma once
#include "Type.h"
#include "occi.h"
#include "occiCommon.h"
#include <string>
#include <vector>
using namespace std;

#if defined(WIN32)
#include <memory>
#include <tuple>
using std::tr1::tuple;
using std::tr1::shared_ptr;
using std::tr1::get;
using std::tr1::make_tuple;
#elif defined(WIN64)
#include <memory>
#include <tuple>
#else
#include <tr1/memory>
#include <tr1/tuple>
#endif

#if defined(WIN32)
#ifdef OCCI_WRAPPER_DLL_EXPORTS
#define __OCCI_WRAPPER_API __declspec(dllexport)
#else
#define __OCCI_WRAPPER_API __declspec(dllimport)
#ifdef _DEBUG
#pragma comment( lib, "OcciWrapperd.lib")
#else
#pragma comment( lib, "OcciWrapper.lib")
#endif
#endif
#else
#define __OCCI_WRAPPER_API
#endif

namespace occiwrapper
{
	const int nBatchedRetrieveOnceCount = 4;

	enum __OCCI_WRAPPER_API Validity { INVALID = 0, VALID = 1 };

	enum __OCCI_WRAPPER_API DataDirection_E
	{
		PAR_IN = 0,
		PAR_OUT = 1,
		PAR_IN_OUT = 2
	};

	// Occi data buffer
	class __OCCI_WRAPPER_API OcciDataBuffer
	{
	public:

		/***
		*	@brief: OcciDataBuffer construction
		*/
		OcciDataBuffer( void* pBuffer, UInt16* pDataLength, Int16* pInd, Int32 nDataBufMaxPerLength );


		/***
		*	@brief: destroyed function
		*/
		~OcciDataBuffer();

	public:
		// the buffer to store data
		void* m_pBuffer;

		// data lenth
		UInt16* m_pDataLength;

		// indicator information, to determine the data is null or not
		Int16* m_pInd;

		// max per length
		Int32 m_nDataBufMaxPerLength;

	private:
		/***
		*	@brief: disable default construction
		*/
		OcciDataBuffer();

	};

	/***
	*	@brief: get vector string max length
	*	@add by: CUCmehp
	*	@since: 2012-05-06
	*/
	__OCCI_WRAPPER_API size_t  GetVectorStringMaxLength( const vector< string >& vec );

	/***
	*	@brief: convert struct tm_value to oracle type Date
	*	@add by: CUCmehp
	*	@add since 2012-05-07
	*/
	__OCCI_WRAPPER_API oracle::occi::Date  ToDate( const struct tm& tmValue, oracle::occi::Environment* pEnv );

	/***
	*	@brief: convert oracle type Date to struct tm_value
	*	@add by: CUCmehp
	*	@add since 2012-05-07
	*/
	__OCCI_WRAPPER_API struct tm  GetTm( const oracle::occi::Date& date );
}


