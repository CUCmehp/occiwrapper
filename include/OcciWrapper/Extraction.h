#pragma once

#include "OcciWrapper/Common.h"

namespace occiwrapper {

	/***
	*	@modified by CUCmehp, since 2012-6-30
	*	@brief: nothing implement class
	*/
	template< class T >
	class Extraction: public AbstractExtraction
	{
	public:
		Extraction( T& result ): m_objResult( result )
			/// Creates an Extraction object, uses an empty object T as default value
		{
		}

		~Extraction()
			/// Destroys the Extraction object.
		{
		}

		std::size_t NumOfColumnsHandled() const
		{
			return occiwrapper::TypeHandler<T>::size();
		}

		void Extract( std::size_t nPos )
		{
			AbstractExtractor* pExtractor = GetExtractor();
			assert( pExtractor != NULL );
			//TypeHandler< T >::extract( nPos, m_objResult, pExtractor );
			TypeHandler< T >::extract( nPos, pExtractor );
		}

		/***
		*	@brief: fetch data from buffer, starting at the given column position
		*	@add by CUCmehp.
		*/
		virtual void Fetch( std::size_t nPos, std::size_t nFetchNum )
		{
			//assert( nFetchNum == 1 );
			AbstractExtractor* pExtractor = GetExtractor();
			assert( pExtractor != NULL );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf;
			for( size_t i = 0; i < TypeHandler< T >::size(); ++ i )
			{
				shared_ptr< OcciDataBuffer > pDataBuf = pExtractor->GetExatractDataBuffer( nPos + i );
				vDataBuf.push_back( pDataBuf );
			}
			TypeHandler< T >::fetch( nPos, m_objResult, pExtractor, vDataBuf, nFetchNum );
		}

	private:
		T&   m_objResult;
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
			TypeHandler< std::vector<T> >::extract( nPos, pExtractor );
		}

		/***
		*	@brief: fetch data from buffer, starting at the given column position
		*	@add by CUCmehp.
		*/
		virtual void Fetch( std::size_t nPos, std::size_t nFetchedNum )
		{
			AbstractExtractor* pExtractor = GetExtractor();
			assert( pExtractor != NULL );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf;
			for( size_t i = 0; i < TypeHandler< std::vector< T > >::size(); ++ i )
			{
				vDataBuf.push_back( pExtractor->GetExatractDataBuffer( nPos + i ) );
			}
			TypeHandler< std::vector< T > >::fetch( nPos, m_vResult, pExtractor, vDataBuf, nFetchedNum );
		}

	private:
		std::vector< T >&		m_vResult;
	};


	/***
	*	@brief:
	*		Convenience function to allow for a more compact creation of a default extraction object
	*	@add by CUCmehp
	*/
	template< typename T > 
	Extraction< T >* into( T& t )
	{
		Extraction< T >* pReturn =  new Extraction< T >( t );
		pReturn->SetLimit( 1 );
		return pReturn;
	}

	/***
	*	@brief:
	*		Convenience function to allow for a more compact creation of a default extraction object
	*	@add by CUCmehp
	*/
	template< typename T > 
	Extraction< vector< T > >* into( vector< T >& t )
	{
		Extraction< vector< T > >* pReturn = new Extraction< vector< T > >( t );
		pReturn->SetLimit( Limit::LIMIT_UNLIMITED );
		return pReturn;
	}

	/***
	*	@brief:
	*		Convenience function to allow for a more compact creation of a default extraction object
	*	@add by CUCmehp
	*/
	template< typename T > 
	Extraction< list< T > >* into( list< T >& t )
	{
		Extraction< list< T > >* pReturn = new Extraction< list< T > >( t );
		pReturn->SetLimit( Limit::LIMIT_UNLIMITED );
		return pReturn;
	}

} 
