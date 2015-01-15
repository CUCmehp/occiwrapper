#pragma once

#include "Common.h"
#include <vector>
#include "AbstractExtractor.h"
#include "Limit.h"

namespace occiwrapper
{
	/***
	*	@brief:
	*		AbstractExtraction is the interface class that connects output positions to concrete values
	*		retrieved via an AbstractExtractor.
	*	@add by CUCmehp
	*/
	class __OCCI_WRAPPER_API AbstractExtraction
	{
	public:
		/***
		*	@brief: construction
		*/
		AbstractExtraction();

		/***
		*	@brief:
		*		Destroys the AbstractExtraction.
		*/
		virtual ~AbstractExtraction();

		/***
		*	@brief: set extractor
		*/
		void SetExtractor( AbstractExtractor* pExtractor );

		/***
		*	@brief: get extractor
		*/
		AbstractExtractor* GetExtractor() const;


		/***
		*	@brief:
		*		Returns the number of columns that the extraction handles.
		*		The trivial case will be one single column but when
		*		complex types are used this value can be larger than one.
		*	@add by CUCmehp
		*/
		virtual std::size_t NumOfColumnsHandled() const = 0;

		/***
		*	@brief:
		*		Extracts a value from the param, starting at the given column position.
		*	@parameters:
		*		nPos: column position
		*	@add by CUCmehp
		*/
		virtual void Extract( std::size_t nPos ) = 0;

		/***
		*	@brief: fetch data from buffer, starting at the given column position
		*	@add by CUCmehp
		*	@parameters:
		*		nPos: column position
		*		nFetchedNum: fetched number
		*/
		virtual void Fetch( std::size_t nPos, std::size_t nFetchedNum ) = 0;

		/***
		*	@brief: sets the limit.
		*	@parameters:
		*		nLimit: set limit
		*	@add by CUCmehp
		*/
		void SetLimit( UInt32 nLimit );

		/***
		*	@brief: gets the limit.
		*	@return:
		*		return limit
		*/
		UInt32 GetLimit() const;

	private:
		AbstractExtractor*	m_pExtractor;
		UInt32				m_nLimit;

	};

	inline void occiwrapper::AbstractExtraction::SetExtractor( occiwrapper::AbstractExtractor* pExtractor )
	{
		m_pExtractor = pExtractor;
	}


	inline occiwrapper::AbstractExtractor* occiwrapper::AbstractExtraction::GetExtractor() const
	{
		return m_pExtractor;
	}

}