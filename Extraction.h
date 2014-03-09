#pragma once

#include "Common.h"

namespace occiwrapper {

	/***
	*	@modified by CUCmehp, since 2012-6-30
	*	@brief: nothing implement class
	*/
	template< class T >
	class Extraction: public AbstractExtraction
	{

	};

	/***
	*	@brief: Vector Data Type specialization for extraction of values from a query result set.
	*	@add by CUCmehp
	*/
	template< class T >
	class Extraction< std::vector<T> >: public AbstractExtraction
	{
	public:
		Extraction(std::vector<T>& vResult ) 
			: m_vResult( vResult )
			, m_objDefault()
		{
		}

		Extraction(std::vector<T>& vResult, const T& def): m_vResult( vResult ), m_objDefault( def )
		{
		}

		virtual ~Extraction()
		{
		}

		std::size_t NumOfColumnsHandled() const
		{
			return occiwrapper::TypeHandler<T>::size();
		}

		void Extract(std::size_t nPos)
		{
			AbstractExtractor* pExtractor = GetExtractor();
			assert( pExtractor != NULL );
			TypeHandler< std::vector<T> >::extract( nPos, m_vResult, pExtractor );
		}

		/***
		*	@brief: fetch data from buffer, starting at the given column position
		*	@add by CUCmehp.
		*/
		virtual void Fetch( std::size_t nPos, std::size_t nFetchedNum )
		{
			AbstractExtractor* pExtractor = GetExtractor();
			assert( pExtractor != NULL );
			shared_ptr< OcciDataBuffer > pDataBuf = pExtractor->GetExatractDataBuffer( nPos );
			TypeHandler< std::vector< T > >::fetch( nPos, m_vResult, pExtractor, pDataBuf, nFetchedNum );
		}

	private:
		std::vector< T >&		m_vResult;
		T						m_objDefault; // copy the default
	};


	/***
	*	@brief:
	*		Convenience function to allow for a more compact creation of a default extraction object
	*	@add by CUCmehp
	*/
	template< typename T > 
	Extraction< T >* into( T& t )
	{
		return new Extraction< T >( t );
	}


	/***
	*	@brief:
	*		Convenience function to allow for a more compact creation of an extraction object with the given default
	*	@add by CUCmehp
	*/
	template< typename T > 
	Extraction< T >* into( T& t, const T& def )
	{
		return new Extraction< T >( t, def );
	}

} 
