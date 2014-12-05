#pragma once
#include "OcciWrapper/Common.h"
#include "OcciWrapper/AbstractBinding.h"

using namespace std;

namespace occiwrapper
{

	/***
	*	@brief: A Binding maps a value to a column.
	*/
	template <class T>
	class Binding: public AbstractBinding
	{
	public:
		/***
		*	@brief: Creates the Binding.
		*/
		explicit Binding( const T& val, bool bBatched, occiwrapper::DataDirection_E eDataDirection = occiwrapper::PAR_IN )
			: m_objConstVal( val )
			, m_bBound( false )
			, m_bBatched( bBatched )
			, m_nBatchedNum( 0 )
			, m_eDataDirection( eDataDirection )
			, m_objVal( const_cast< T& >( val ) )
		{
		}

		/***
		*	@brief: Destroys the Binding.
		*/
		~Binding()
		{
		}

		std::size_t NumOfColumnsHandled() const
		{
			return TypeHandler<T>::size();
		}

		std::size_t NumOfRowsHandled() const
		{
			return 1;
		}

		bool CanBind() const
		{
			return !m_bBound;
		}

		void Bind(std::size_t pos)
		{
			AbstractBinder* p_binder = GetBinder();
			assert( p_binder != 0 );
			p_binder->SetDirection( this->m_eDataDirection );
			TypeHandler<T>::bind( pos, m_objConstVal, p_binder );
			m_bBound = true;
		}

		void ReverseBind( std::size_t pos )
		{
			AbstractBinder* p_binder = GetBinder();
			assert( p_binder != 0 );
			p_binder->SetDirection( this->m_eDataDirection );
			if( this->IsOut() )
			{
				p_binder->Retrieve( pos, m_objVal );
			}
		}

		void Reset ()
		{
			m_bBound = false;
		}

		virtual bool IsBatchedBind()
		{
			return m_bBatched;
		}

		virtual void SetBatchedNum( size_t _batched_num )
		{
			this->m_nBatchedNum = _batched_num;
		}

		virtual int GetBatchedNum()
		{
			return m_nBatchedNum;
		}

		virtual bool IsOut()
		{
			return m_eDataDirection == occiwrapper::PAR_OUT || m_eDataDirection == occiwrapper::PAR_IN_OUT;
		}

		virtual bool IsIn()
		{
			return m_eDataDirection == occiwrapper::PAR_IN || m_eDataDirection == occiwrapper::PAR_IN_OUT;
		}

	private:
		const T&			m_objConstVal;
		T&					m_objVal;
		bool				m_bBound;
		bool				m_bBatched;
		size_t				m_nBatchedNum;
		DataDirection_E		m_eDataDirection;	//is registered as out variable or in variable
	};

	//
	template <class T>
	class Binding< std::vector<T> >
		: public AbstractBinding
	{
	public:
		/***
		*	@brief: Creates the Binding.
		*/
		explicit Binding(const std::vector<T>& val, bool bBatched, occiwrapper::DataDirection_E eDataDirection = occiwrapper::PAR_IN )
			: m_objConstVal( val )
			, m_bBound( false )
			, m_bBatched( bBatched )
			, m_nBatchedNum( 0 )
			, m_eDataDirection( m_eDataDirection )
			, m_objVal( const_cast< std::vector< T > & >( val ) )
		{
			
		}

		~Binding()
			/// Destroys the Binding.
		{
		}

		std::size_t NumOfColumnsHandled() const
		{
			return TypeHandler< std::vector<T> >::size();
		}

		std::size_t NumOfRowsHandled() const
		{
			return m_objConstVal.size();
		}

		bool CanBind() const
		{
			return !m_bBound;
		}

		void Bind( std::size_t pos )
		{
			AbstractBinder* p_binder = GetBinder();
			assert( p_binder != 0 );
			if( this->IsOut() )
				throw BindException( "vector can not registered as out variables" );
			TypeHandler< std::vector<T> >::bind( pos, m_objConstVal, p_binder );
			m_bBound = true;
		}

		void ReverseBind( std::size_t pos )
		{
			// nothing to do here
		}

		void Reset ()
		{
			m_bBound = false;
		}

		virtual bool IsBatchedBind()
		{
			return m_bBatched;
		}

		virtual void SetBatchedNum( size_t m_nBatchedNum )
		{
			this->m_nBatchedNum = m_nBatchedNum;
		}

		virtual int GetBatchedNum()
		{
			return m_nBatchedNum;
		}

		// is registered as in variable
		virtual bool IsIn()
		{
			return m_eDataDirection == occiwrapper::PAR_IN || m_eDataDirection == occiwrapper::PAR_IN_OUT;
		}

		virtual bool IsOut()
		{
			return m_eDataDirection == occiwrapper::PAR_IN_OUT || m_eDataDirection == occiwrapper::PAR_OUT;
		}

	private:
		const std::vector< T >&				m_objConstVal;
		std::vector< T >&					m_objVal;
		bool								m_bBound;
		bool								m_bBatched;
		size_t								m_nBatchedNum;
		occiwrapper::DataDirection_E		m_eDataDirection;					//is registered as out variable or in variable
	};

	/// Convenience function for a more compact Binding creation.
	template< typename T > 
	Binding< T >* use( const T& t, occiwrapper::DataDirection_E dir = occiwrapper::PAR_IN )
	{
		return new Binding< T >( t, false, dir );
	}

	// do not implement, add compile error later
	template< typename T > 
	Binding< vector< T > >* use( const vector< T >& t, occiwrapper::DataDirection_E dir = occiwrapper::PAR_IN );

	// do not implement, add compile error later
	template< typename T >
	Binding< T >* batched_use( const T& t );

	template< typename T >
	Binding< vector< T > >* batched_use( const vector< T >& t )
	{
		Binding< vector< T > >* p = new Binding< vector< T > >( t , true );
		p->SetBatchedNum( t.size() );
		return p;
	}
}