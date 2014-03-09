#pragma once
#include "Common.h"
#include <assert.h>
#include "AbstractBinding.h"
#include "AbstractBinder.h"
#include <tuple>
#include <string>
#include <vector>
#include <iostream>
#include <limits>
#include "Exception.h"
#include "AbstractExtractor.h"
#include <string.h>

using namespace std;

#pragma warning( disable : 4996 )

namespace occiwrapper
{
	template< class T >
	class TypeConvertor;

	template<>
	class TypeConvertor< Int8 >
	{
	public:
		static enum oracle::occi::Type Convert()
		{
			return oracle::occi::OCCIINT;
		};

		static Int8 retrieve( void* pBuf, const int& length, const int& ind )
		{
			if( ind == -1 )
			{
				return 0;
			}
			else
			{
				return *(Int8*)pBuf;
			}
		}
	};

	template<>
	class TypeConvertor< UInt8 >
	{
	public:
		static enum oracle::occi::Type Convert()
		{
			return oracle::occi::OCCIINT;
		};

		static UInt8 retrieve( void* pBuf, const int& length, const int& ind )
		{
			if( ind == -1 )
			{
				return 0;
			}
			else
			{
				return *( UInt8* )pBuf;
			}
		}
	};

	template<>
	class TypeConvertor< Int16 >
	{
	public:
		static enum oracle::occi::Type Convert()
		{
			return oracle::occi::OCCIINT;
		};

		static Int16 retrieve( void* pBuf, const int& length, const int& ind )
		{
			if( ind == -1 )
			{
				return 0;
			}
			else
			{
				return *( Int16* )pBuf;
			}
		}
	};

	template<>
	class TypeConvertor< UInt16 >
	{
	public:
		static enum oracle::occi::Type Convert()
		{
			return oracle::occi::OCCIINT;
		};

		static UInt16 retrieve( void* pBuf, const int& length, const int& ind )
		{
			if( ind == -1 )
			{
				return 0;
			}
			else
			{
				return *( UInt16* )pBuf;
			}
		}
	};


	template<>
	class TypeConvertor< Int32 >
	{
	public:
		static enum oracle::occi::Type Convert()
		{
			return oracle::occi::OCCIINT;
		};

		static Int32 retrieve( void* pBuf, const int& length, const int& ind )
		{
			if( ind == -1 )
			{
				return 0;
			}
			else
			{
				return *( Int32* )pBuf;
			}
		}
	};

	template<>
	class TypeConvertor< UInt32 >
	{
	public:
		static enum oracle::occi::Type Convert()
		{
			return oracle::occi::OCCIINT;
		};

		static UInt32 retrieve( void* pBuf, const int& length, const int& ind )
		{
			if( ind == -1 )
			{
				return 0;
			}
			else
			{
				return *( UInt32* )pBuf;
			}
		}
	};

	template<>
	class TypeConvertor< Int64 >
	{
	public:
		static enum oracle::occi::Type Convert()
		{
			return oracle::occi::OCCIINT;
		};

		static Int64 retrieve( void* pBuf, const int& length, const int& ind )
		{
			if( ind == -1 )
			{
				return 0;
			}
			else
			{
				return *( Int64* )pBuf;
			}
		}
	};

	template<>
	class TypeConvertor< UInt64 >
	{
	public:
		static enum oracle::occi::Type Convert()
		{
			return oracle::occi::OCCIINT;
		};

		static UInt64 retrieve( void* pBuf, const int& length, const int& ind )
		{
			if( ind == -1 )
			{
				return 0;
			}
			else
			{
				return *( UInt64* )pBuf;
			}
		}
	};

	template<>
	class TypeConvertor< float >
	{
	public:
		static enum oracle::occi::Type Convert()
		{
			return oracle::occi::OCCIFLOAT;
		};

		static float retrieve( void* pBuf, const int& length, const int& ind )
		{
			if( ind == -1 )
			{
				return 0;
			}
			else
			{
				return *( float* )pBuf;
			}
		}
	};

	template<>
	class TypeConvertor< double >
	{
	public:
		static enum oracle::occi::Type Convert()
		{
			return oracle::occi::OCCIFLOAT;
		};

		static double retrieve( void* pBuf, const int& length, const int& ind )
		{
			if( ind == -1 )
			{
				return 0;
			}
			else
			{
				return *( double* )pBuf;
			}
		}
	};

	template<>
	class TypeConvertor< string >
	{
	public:
		static enum oracle::occi::Type Convert()
		{
			return oracle::occi::OCCI_SQLT_STR;
		};

		static string retrieve( void* pBuf, const int& length, const int& ind  )
		{
			if( ind == -1 )
			{
				return "";
			}
			else
			{
				return string( ( char* )pBuf, length );
			}
		}
	};

	template<>
	class TypeConvertor< struct tm >
	{
	public:
		static enum oracle::occi::Type Convert()
		{
			return oracle::occi::OCCI_SQLT_ODT;
		};

		static struct tm retrieve( void* pBuf, const int& length, const int& ind )
		{
			struct tm tmRet;
			if( ind == -1 )
			{
				tmRet.tm_year = 0;
				tmRet.tm_mon = 0;
				tmRet.tm_mday =  1;
				tmRet.tm_hour =  0;
				tmRet.tm_min =  0;
				tmRet.tm_sec =  0;
			}
			else
			{
				tmRet.tm_year = *( unsigned short* )pBuf - 1900;
				tmRet.tm_mon = *( ( unsigned char* )pBuf + 2 ) - 1;
				tmRet.tm_mday =  *( ( unsigned char* )pBuf + 3 );
				tmRet.tm_hour =  *( ( unsigned char* )pBuf + 4 ) - 1;
				tmRet.tm_min =  *( ( unsigned char* )pBuf + 5 );
				tmRet.tm_sec =  *( ( unsigned char* )pBuf + 6 );
			}
			return tmRet;
		}
	};

	/***
	*	@add by CUCmehp
	*/
	template <class T>
	class TypeHandler
	{
	public:
		static void bind(std::size_t pos, const T& obj, AbstractBinder* pBinder)
		{
			assert( pBinder != 0 );
			pBinder->Bind( pos, obj );
		}

		static void batched_bind( std::size_t pos, const vector<T>& vec_obj, AbstractBinder* pBinder );

		static std::size_t size()
		{
			return 1;
		}

		static void extract( std::size_t pos, T& obj, const T& defVal, AbstractExtractor* pExt )
		{
			assert( pExt != 0 );
			if ( !pExt->Extract( pos, obj ) )
				obj = defVal;
		}

	private:
		TypeHandler();
		~TypeHandler();
		TypeHandler(const TypeHandler&);
		TypeHandler& operator = (const TypeHandler&);
	};

	template <typename TupleType, typename Type, int N>
	void tupleBind(std::size_t& pos, TupleType tuple, AbstractBinder* pBinder)
	{
		TypeHandler<Type>::bind(pos, get<N>(tuple), pBinder);
		pos += TypeHandler<Type>::size();
	}

	// specialize tuple, tuple size = 1
	template < class T1 >
	class TypeHandler< tuple< T1 > >
	{
	public:
		static void bind(std::size_t pos, const tuple< T1 >& obj, AbstractBinder* pBinder)
		{
			assert( pBinder != 0 );
			tupleBind< tuple< T1 >, T1, 0 >( pos, obj, pBinder );
		}

		static std::size_t size()
		{
			return TypeHandler< T1 >::size();
		}

	private:
		TypeHandler();
		~TypeHandler();
		TypeHandler(const TypeHandler&);
		TypeHandler& operator = (const TypeHandler&);
	};

	// specialize tuple, tuple size = 2
	template < class T1, class T2 >
	class TypeHandler< tuple< T1 , T2 > >
	{
	public:
		static void bind(std::size_t pos, const tuple< T1 ,T2 >& obj, AbstractBinder* pBinder)
		{
			assert( pBinder != 0 );
			tupleBind< tuple< T1, T2 >, T1, 0 >( pos, obj, pBinder );
			tupleBind< tuple< T1, T2 >, T2, 1 >( pos, obj, pBinder );
		}

		static std::size_t size()
		{
			return TypeHandler< T1 >::size() + TypeHandler< T2 >::size();
		}

	private:
		TypeHandler();
		~TypeHandler();
		TypeHandler(const TypeHandler&);
		TypeHandler& operator = (const TypeHandler&);
	};

	// specialize tuple, tuple size = 3
	template < class T1, class T2, class T3 >
	class TypeHandler< tuple< T1, T2, T3 > >
	{
	public:
		static void bind(std::size_t pos, const tuple< T1 ,T2, T3 >& obj, AbstractBinder* pBinder)
		{
			assert( pBinder != 0 );
			tupleBind< tuple< T1, T2, T3 >, T1, 0 >( pos, obj, pBinder );
			tupleBind< tuple< T1, T2, T3 >, T2, 1 >( pos, obj, pBinder );
			tupleBind< tuple< T1, T2, T3 >, T3, 2 >( pos, obj, pBinder );
		}

		static std::size_t size()
		{
			return TypeHandler< T1 >::size() + TypeHandler< T2 >::size() +  TypeHandler< T3 >::size();
		}

	private:
		TypeHandler();
		~TypeHandler();
		TypeHandler(const TypeHandler&);
		TypeHandler& operator = (const TypeHandler&);
	};

	// specialize tuple, tuple size = 4
	template < class T1, class T2, class T3, class T4 >
	class TypeHandler< tuple< T1, T2, T3, T4 > >
	{
	public:
		static void bind(std::size_t pos, const tuple< T1 ,T2, T3, T4 >& obj, AbstractBinder* pBinder)
		{
			assert( pBinder != 0 );
			tupleBind< tuple< T1 ,T2, T3, T4 >, T1, 0 >( pos, obj, pBinder );
			tupleBind< tuple< T1 ,T2, T3, T4 >, T2, 1 >( pos, obj, pBinder );
			tupleBind< tuple< T1 ,T2, T3, T4 >, T3, 2 >( pos, obj, pBinder );
			tupleBind< tuple< T1 ,T2, T3, T4 >, T4, 3 >( pos, obj, pBinder );
		}

		static std::size_t size()
		{
			return TypeHandler< T1 >::size() + TypeHandler< T2 >::size() +  TypeHandler< T3 >::size() + TypeHandler< T4 >::size();
		}

	private:
		TypeHandler();
		~TypeHandler();
		TypeHandler(const TypeHandler&);
		TypeHandler& operator = (const TypeHandler&);
	};

	// specialize tuple, tuple size = 5
	template < class T1, class T2, class T3, class T4, class T5 >
	class TypeHandler< tuple< T1, T2, T3, T4, T5 > >
	{
	public:
		static void bind(std::size_t pos, const tuple< T1 ,T2, T3, T4, T5 >& obj, AbstractBinder* pBinder)
		{
			assert( pBinder != 0 );
			tupleBind< tuple< T1 ,T2, T3, T4, T5 >, T1, 0 >( pos, obj, pBinder );
			tupleBind< tuple< T1 ,T2, T3, T4, T5 >, T2, 1 >( pos, obj, pBinder );
			tupleBind< tuple< T1 ,T2, T3, T4, T5 >, T3, 2 >( pos, obj, pBinder );
			tupleBind< tuple< T1 ,T2, T3, T4, T5 >, T4, 3 >( pos, obj, pBinder );
			tupleBind< tuple< T1 ,T2, T3, T4, T5 >, T5, 4 >( pos, obj, pBinder );
		}

		static std::size_t size()
		{
			return TypeHandler< T1 >::size() + TypeHandler< T2 >::size() +  TypeHandler< T3 >::size() + TypeHandler< T4 >::size() + TypeHandler< T5 >::size();
		}

	private:
		TypeHandler();
		~TypeHandler();
		TypeHandler(const TypeHandler&);
		TypeHandler& operator = (const TypeHandler&);
	};

	// specialize vector for batched bind
	template < class T >
	class TypeHandler< vector< T > >
	{
	public:
		static void bind(std::size_t pos, const vector< T >& obj, AbstractBinder* pBinder)
		{
			assert( pBinder != 0 );
			const size_t max_size = (numeric_limits< size_t >::max)() / sizeof( int );
			if( obj.size() > max_size )
				throw BindException( "bind vector<int> exceeding max row number" );
			size_t buf_length = sizeof(T) * ( obj.size() );
			// set buffer
			T* p = ( T* )malloc( buf_length );
			for( size_t i = 0; i < obj.size(); ++ i )
				*( p + i ) = obj[ i ];
			// set length array
			UInt16* p_length = ( UInt16* )malloc( sizeof( UInt16 ) *  obj.size() );
			for( size_t i = 0; i < obj.size(); i ++ )
				*(p_length + i ) = sizeof( T );
			// set indicator
			Int16* p_Ind = ( Int16* ) malloc( sizeof( Int16 ) * obj.size() );
			for( size_t i = 0; i < obj.size(); i ++ )
				*( p_Ind + i ) = 0;
			pBinder->BatchedBind( pos, p, sizeof(T), p_length, p_Ind, TypeConvertor< T >::Convert() );
		}

		static std::size_t size()
		{
			return TypeHandler< T >::size();
		}

		static void extract(std::size_t pos, const vector< T >& obj, AbstractExtractor* pExt)
		{
			assert( pExt != 0 );
			size_t nAllBufLength = sizeof(T) * ( nBatchedRetrieveOnceCount );
			// set buffer
			T* p = ( T* )malloc( nAllBufLength );
			// set length array
			UInt16* p_length = ( UInt16* )malloc( sizeof( UInt16 ) * nBatchedRetrieveOnceCount );
			// set indicator
			Int16* p_Ind = ( Int16* ) malloc( sizeof( Int16 ) * nBatchedRetrieveOnceCount );

			pExt->Extract( pos, p, sizeof(T), p_length, p_Ind, TypeConvertor< T >::Convert() );
		}

		static void fetch( std::size_t pos, vector< T >& vecResult, AbstractExtractor* pExtractor, shared_ptr< OcciDataBuffer >& pDataBuf, size_t nFetchedNum )
		{
			for( size_t i = 0; i < nFetchedNum; ++ i )
			{
				T obj = TypeConvertor< T >::retrieve( ( ( void* )( ( char* )pDataBuf->m_pBuffer + pDataBuf->m_nDataBufMaxPerLength * i ) ) , *( pDataBuf->m_pDataLength + i ), *( pDataBuf->m_pInd + i ) );
				vecResult.push_back( obj );
			}
		}

	private:
		TypeHandler();
		~TypeHandler();
		TypeHandler(const TypeHandler&);
		TypeHandler& operator = (const TypeHandler&);
	};

	// specialize vector for batched bind
	template <>
	class TypeHandler< vector< string > >
	{
	public:
		static void bind(std::size_t pos, const vector< string >& obj, AbstractBinder* pBinder)
		{
			assert( pBinder != 0 );
			size_t char_buf_max = occiwrapper::GetVectorStringMaxLength( obj ) + 1;
			const size_t max_size = ( numeric_limits< size_t >::max )() / sizeof( char_buf_max );
			if( obj.size() > max_size )
				throw BindException( "bind vector<string> exceeding max row number" );
			size_t buf_length =  char_buf_max * ( obj.size() );
			// set buffer
			char* p = ( char* )malloc( buf_length );
			for( size_t i = 0; i < obj.size(); ++ i )
			{
				strcpy( p + i * char_buf_max, obj[i].c_str() );
			}
			// set length array
			UInt16* p_length = ( UInt16* )malloc( sizeof( UInt16 ) *  obj.size() );
			// set indicator
			Int16* p_Ind = ( Int16* )malloc( sizeof( Int16 ) * obj.size() );
			for( size_t i = 0; i < obj.size(); ++ i )
			{
				if( obj.empty() )
				{
					*( p_Ind + i ) = -1;
				}
				else
				{
					*( p_Ind + i ) = 0;
				}

				*(p_length + i ) = obj[ i ].size() + 1;
			}

			pBinder->BatchedBind( pos, p, char_buf_max, p_length, p_Ind, TypeConvertor< string >::Convert() );
		}

		static std::size_t size()
		{
			return TypeHandler< string >::size();
		}

		static void extract(std::size_t pos, const vector< string >& obj, AbstractExtractor* pExt)
		{
			size_t nCharBufMax = 4000;
			assert( pExt != 0 );
			size_t nAllBufLength = nCharBufMax * ( nBatchedRetrieveOnceCount );
			// set buffer
			char* p = ( char* )malloc( nAllBufLength );
			// set length array
			UInt16* p_length = ( UInt16* )malloc( sizeof( UInt16 ) * nBatchedRetrieveOnceCount );
			// set indicator
			Int16* p_Ind = ( Int16* )malloc( sizeof( Int16 ) * nBatchedRetrieveOnceCount );

			pExt->Extract( pos, p, nCharBufMax, p_length, p_Ind, TypeConvertor< string >::Convert() );
		}

		static void fetch( std::size_t pos, vector< string >& vecResult, AbstractExtractor* pExtractor, shared_ptr< OcciDataBuffer >& pDataBuf, size_t nFetchedNum )
		{
			for( size_t i = 0; i < nFetchedNum; ++ i )
			{
				string obj = TypeConvertor< string >::retrieve( ( ( void* )( ( char* )pDataBuf->m_pBuffer + pDataBuf->m_nDataBufMaxPerLength * i ) ) , *( pDataBuf->m_pDataLength + i ), *( pDataBuf->m_pInd + i ) );
				vecResult.push_back( obj );
			}
		}

	private:
		TypeHandler();
		~TypeHandler();
		TypeHandler(const TypeHandler&);
		TypeHandler& operator = (const TypeHandler&);
	};

	// specialize vector for batched bind
	template <>
	class TypeHandler< vector< struct tm > >
	{
	public:
		static void bind(std::size_t pos, const vector< struct tm >& obj, AbstractBinder* pBinder)
		{
			assert( pBinder != 0 );
			size_t char_buf_max = sizeof( oracle::occi::Date );
			const size_t max_size = (numeric_limits< size_t >::max)() / char_buf_max;
			if( obj.size() > max_size )
				throw BindException( "bind vector<struct tm> exceeding max row number" );
			size_t buf_length =  char_buf_max * ( obj.size() );
			// set buffer
			oracle::occi::Date* p = ( oracle::occi::Date* )malloc( buf_length );
			for( size_t i = 0; i < obj.size(); ++ i )
			{
				* ( p + i ) = occiwrapper::ToDate( obj[ i ], pBinder->GetEnv() );
			}
			// set length array
			UInt16* p_length = ( UInt16* )malloc( sizeof( UInt16 ) *  obj.size() );
			// set indicator
			Int16* p_Ind = ( Int16* )malloc( sizeof( Int16 ) * obj.size() );
			for( size_t i = 0; i < obj.size(); i ++ )
			{
				*(p_length + i ) = char_buf_max;
				*( p_Ind + i ) = 0;
			}
			pBinder->BatchedBind( pos, p, char_buf_max, p_length, p_Ind, TypeConvertor< struct tm >::Convert() );
		}

		static std::size_t size()
		{
			return TypeHandler< struct tm >::size();
		}

		static void extract(std::size_t pos, const vector< struct tm >& obj, AbstractExtractor* pExt)
		{
			size_t nCharBufMax = 8;
			assert( pExt != 0 );
			size_t nAllBufLength = nCharBufMax * ( nBatchedRetrieveOnceCount );
			// set buffer
			char* p = ( char* )malloc( nAllBufLength );
			// set length array
			UInt16* p_length = ( UInt16* )malloc( sizeof( UInt16 ) * nBatchedRetrieveOnceCount );
			// set indicator
			Int16* p_Ind = ( Int16* )malloc( sizeof( Int16 ) * nBatchedRetrieveOnceCount );
			pExt->Extract( pos, p, nCharBufMax, p_length, p_Ind, TypeConvertor< struct tm >::Convert() );
		}

		static void fetch( std::size_t pos, vector< struct tm >& vecResult, AbstractExtractor* pExtractor, shared_ptr< OcciDataBuffer >& pDataBuf, size_t nFetchedNum )
		{
			for( size_t i = 0; i < nFetchedNum; ++ i )
			{
				struct tm obj = TypeConvertor< struct tm >::retrieve( ( ( void* )( ( char* )pDataBuf->m_pBuffer + pDataBuf->m_nDataBufMaxPerLength * i ) ) , *( pDataBuf->m_pDataLength + i ), *( pDataBuf->m_pInd + i ) );
				vecResult.push_back( obj );
			}
		}

	private:
		TypeHandler();
		~TypeHandler();
		TypeHandler(const TypeHandler&);
		TypeHandler& operator = (const TypeHandler&);
	};

	// specialize vector for batched bind
	template < class T1 >
	class TypeHandler< vector< tuple< T1 > > >
	{
	public:
		static void bind(std::size_t pos, const vector< tuple< T1 > >& obj, AbstractBinder* pBinder)
		{
			assert( pBinder != 0 );
			vector< T1 > copy_obj;
			for( size_t i = 0; i < obj.size(); ++ i )
				copy_obj.push_back( get< 0 >( obj[ i ] ) );
			TypeHandler< vector< T1 > >::bind( pos, copy_obj, pBinder );
		}

		static std::size_t size()
		{
			return TypeHandler< tuple< T1 > >::size();
		}

	private:
		TypeHandler();
		~TypeHandler();
		TypeHandler(const TypeHandler&);
		TypeHandler& operator = (const TypeHandler&);
	};

	// specialize vector for batched bind
	template < class T1, class T2 >
	class TypeHandler< vector< tuple< T1, T2 > > >
	{
	public:
		static void bind(std::size_t pos, const vector< tuple< T1, T2 > >& obj, AbstractBinder* pBinder)
		{
			assert( pBinder != 0 );
			vector< T1 > copy_obj1;
			vector< T2 > copy_obj2;
			for( size_t i = 0; i < obj.size(); ++ i )
			{
				copy_obj1.push_back( get< 0 >( obj[ i ] ) );
				copy_obj2.push_back( get< 1 >( obj[ i ] ) );
			}
			TypeHandler< vector< T1 > >::bind( pos, copy_obj1, pBinder );
			TypeHandler< vector< T2 > >::bind( pos + 1, copy_obj2, pBinder );
		}

		static std::size_t size()
		{
			return TypeHandler< tuple< T1 > >::size()
				+  TypeHandler< tuple< T2 > >::size();
		}

	private:
		TypeHandler();
		~TypeHandler();
		TypeHandler(const TypeHandler&);
		TypeHandler& operator = (const TypeHandler&);
	};

	// specialize vector for batched bind
	template < class T1, class T2, class T3 >
	class TypeHandler< vector< tuple< T1, T2, T3 > > >
	{
	public:
		static void bind(std::size_t pos, const vector< tuple< T1, T2, T3 > >& obj, AbstractBinder* pBinder)
		{
			assert( pBinder != 0 );
			vector< T1 > copy_obj1;
			vector< T2 > copy_obj2;
			vector< T3 > copy_obj3;
			for( size_t i = 0; i < obj.size(); ++ i )
			{
				copy_obj1.push_back( get< 0 >( obj[ i ] ) );
				copy_obj2.push_back( get< 1 >( obj[ i ] ) );
				copy_obj3.push_back( get< 2 >( obj[ i ] ) );
			}
			TypeHandler< vector< T1 > >::bind( pos, copy_obj1, pBinder );
			TypeHandler< vector< T2 > >::bind( pos + 1, copy_obj2, pBinder );
			TypeHandler< vector< T3 > >::bind( pos + 2, copy_obj3, pBinder );
		}

		static std::size_t size()
		{
			return TypeHandler< tuple< T1 > >::size()
				+  TypeHandler< tuple< T2 > >::size()
				+  TypeHandler< tuple< T3 > >::size();
		}

	private:
		TypeHandler();
		~TypeHandler();
		TypeHandler(const TypeHandler&);
		TypeHandler& operator = (const TypeHandler&);
	};

	// specialize vector for batched bind
	template < class T1, class T2, class T3, class T4 >
	class TypeHandler< vector< tuple< T1, T2, T3, T4 > > >
	{
	public:
		static void bind(std::size_t pos, const vector< tuple< T1, T2, T3, T4 > >& obj, AbstractBinder* pBinder)
		{
			assert( pBinder != 0 );
			vector< T1 > copy_obj1;
			vector< T2 > copy_obj2;
			vector< T3 > copy_obj3;
			vector< T4 > copy_obj4;
			for( size_t i = 0; i < obj.size(); ++ i )
			{
				copy_obj1.push_back( get< 0 >( obj[ i ] ) );
				copy_obj2.push_back( get< 1 >( obj[ i ] ) );
				copy_obj3.push_back( get< 2 >( obj[ i ] ) );
				copy_obj4.push_back( get< 3 >( obj[ i ] ) );
			}
			TypeHandler< vector< T1 > >::bind( pos, copy_obj1, pBinder );
			TypeHandler< vector< T2 > >::bind( pos + 1, copy_obj2, pBinder );
			TypeHandler< vector< T3 > >::bind( pos + 2, copy_obj3, pBinder );
			TypeHandler< vector< T4 > >::bind( pos + 3, copy_obj4, pBinder );
		}

		static std::size_t size()
		{
			return TypeHandler< tuple< T1 > >::size()
				+  TypeHandler< tuple< T2 > >::size()
				+  TypeHandler< tuple< T3 > >::size()
				+  TypeHandler< tuple< T4 > >::size();
		}

	private:
		TypeHandler();
		~TypeHandler();
		TypeHandler(const TypeHandler&);
		TypeHandler& operator = (const TypeHandler&);
	};

	// specialize vector for batched bind
	template < class T1, class T2, class T3, class T4, class T5 >
	class TypeHandler< vector< tuple< T1, T2, T3, T4, T5 > > >
	{
	public:
		static void bind(std::size_t pos, const vector< tuple< T1, T2, T3, T4, T5 > >& obj, AbstractBinder* pBinder)
		{
			assert( pBinder != 0 );
			vector< T1 > copy_obj1;
			vector< T2 > copy_obj2;
			vector< T3 > copy_obj3;
			vector< T4 > copy_obj4;
			vector< T5 > copy_obj5;
			for( size_t i = 0; i < obj.size(); ++ i )
			{
				copy_obj1.push_back( get< 0 >( obj[ i ] ) );
				copy_obj2.push_back( get< 1 >( obj[ i ] ) );
				copy_obj3.push_back( get< 2 >( obj[ i ] ) );
				copy_obj4.push_back( get< 3 >( obj[ i ] ) );
				copy_obj5.push_back( get< 4 >( obj[ i ] ) );
			}
			TypeHandler< vector< T1 > >::bind( pos, copy_obj1, pBinder );
			TypeHandler< vector< T2 > >::bind( pos + 1, copy_obj2, pBinder );
			TypeHandler< vector< T3 > >::bind( pos + 2, copy_obj3, pBinder );
			TypeHandler< vector< T4 > >::bind( pos + 3, copy_obj4, pBinder );
			TypeHandler< vector< T5 > >::bind( pos + 4, copy_obj5, pBinder );
		}

		static std::size_t size()
		{
			return TypeHandler< tuple< T1 > >::size()
				+  TypeHandler< tuple< T2 > >::size()
				+  TypeHandler< tuple< T3 > >::size()
				+  TypeHandler< tuple< T4 > >::size()
				+  TypeHandler< tuple< T5 > >::size();
		}

	private:
		TypeHandler();
		~TypeHandler();
		TypeHandler(const TypeHandler&);
		TypeHandler& operator = (const TypeHandler&);
	};

	// specialize vector for batched bind
	template < class T1, class T2, class T3, class T4, class T5, class T6 >
	class TypeHandler< vector< tuple< T1, T2, T3, T4, T5, T6 > > >
	{
	public:
		static void bind(std::size_t pos, const vector< tuple< T1, T2, T3, T4, T5, T6 > >& obj, AbstractBinder* pBinder)
		{
			assert( pBinder != 0 );
			vector< T1 > copy_obj1;
			vector< T2 > copy_obj2;
			vector< T3 > copy_obj3;
			vector< T4 > copy_obj4;
			vector< T5 > copy_obj5;
			vector< T6 > copy_obj6;
			for( size_t i = 0; i < obj.size(); ++ i )
			{
				copy_obj1.push_back( get< 0 >( obj[ i ] ) );
				copy_obj2.push_back( get< 1 >( obj[ i ] ) );
				copy_obj3.push_back( get< 2 >( obj[ i ] ) );
				copy_obj4.push_back( get< 3 >( obj[ i ] ) );
				copy_obj5.push_back( get< 4 >( obj[ i ] ) );
				copy_obj6.push_back( get< 5 >( obj[ i ] ) );
			}
			TypeHandler< vector< T1 > >::bind( pos, copy_obj1, pBinder );
			TypeHandler< vector< T2 > >::bind( pos + 1, copy_obj2, pBinder );
			TypeHandler< vector< T3 > >::bind( pos + 2, copy_obj3, pBinder );
			TypeHandler< vector< T4 > >::bind( pos + 3, copy_obj4, pBinder );
			TypeHandler< vector< T5 > >::bind( pos + 4, copy_obj5, pBinder );
			TypeHandler< vector< T6 > >::bind( pos + 5, copy_obj6, pBinder );
		}

		static std::size_t size()
		{
			return TypeHandler< tuple< T1 > >::size()
				+  TypeHandler< tuple< T2 > >::size()
				+  TypeHandler< tuple< T3 > >::size()
				+  TypeHandler< tuple< T4 > >::size()
				+  TypeHandler< tuple< T5 > >::size()
				+  TypeHandler< tuple< T6 > >::size();
		}

	private:
		TypeHandler();
		~TypeHandler();
		TypeHandler(const TypeHandler&);
		TypeHandler& operator = (const TypeHandler&);
	};

	// specialize vector for batched bind
	template < class T1, class T2, class T3, class T4, class T5, class T6, class T7 >
	class TypeHandler< vector< tuple< T1, T2, T3, T4, T5, T6, T7 > > >
	{
	public:
		static void bind(std::size_t pos, const vector< tuple< T1, T2, T3, T4, T5, T6, T7 > >& obj, AbstractBinder* pBinder)
		{
			assert( pBinder != 0 );
			vector< T1 > copy_obj1;
			vector< T2 > copy_obj2;
			vector< T3 > copy_obj3;
			vector< T4 > copy_obj4;
			vector< T5 > copy_obj5;
			vector< T6 > copy_obj6;
			vector< T7 > copy_obj7;
			for( size_t i = 0; i < obj.size(); ++ i )
			{
				copy_obj1.push_back( get< 0 >( obj[ i ] ) );
				copy_obj2.push_back( get< 1 >( obj[ i ] ) );
				copy_obj3.push_back( get< 2 >( obj[ i ] ) );
				copy_obj4.push_back( get< 3 >( obj[ i ] ) );
				copy_obj5.push_back( get< 4 >( obj[ i ] ) );
				copy_obj6.push_back( get< 5 >( obj[ i ] ) );
				copy_obj7.push_back( get< 6 >( obj[ i ] ) );
			}
			TypeHandler< vector< T1 > >::bind( pos, copy_obj1, pBinder );
			TypeHandler< vector< T2 > >::bind( pos + 1, copy_obj2, pBinder );
			TypeHandler< vector< T3 > >::bind( pos + 2, copy_obj3, pBinder );
			TypeHandler< vector< T4 > >::bind( pos + 3, copy_obj4, pBinder );
			TypeHandler< vector< T5 > >::bind( pos + 4, copy_obj5, pBinder );
			TypeHandler< vector< T6 > >::bind( pos + 5, copy_obj6, pBinder );
			TypeHandler< vector< T7 > >::bind( pos + 6, copy_obj7, pBinder );
		}

		static std::size_t size()
		{
			return TypeHandler< tuple< T1 > >::size()
				+  TypeHandler< tuple< T2 > >::size()
				+  TypeHandler< tuple< T3 > >::size()
				+  TypeHandler< tuple< T4 > >::size()
				+  TypeHandler< tuple< T5 > >::size()
				+  TypeHandler< tuple< T6 > >::size()
				+  TypeHandler< tuple< T7 > >::size();
		}

	private:
		TypeHandler();
		~TypeHandler();
		TypeHandler(const TypeHandler&);
		TypeHandler& operator = (const TypeHandler&);
	};

	// specialize vector for batched bind
	template < class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8 >
	class TypeHandler< vector< tuple< T1, T2, T3, T4, T5, T6, T7, T8 > > >
	{
	public:
		static void bind(std::size_t pos, const vector< tuple< T1, T2, T3, T4, T5, T6, T7, T8 > >& obj, AbstractBinder* pBinder)
		{
			assert( pBinder != 0 );
			vector< T1 > copy_obj1;
			vector< T2 > copy_obj2;
			vector< T3 > copy_obj3;
			vector< T4 > copy_obj4;
			vector< T5 > copy_obj5;
			vector< T6 > copy_obj6;
			vector< T7 > copy_obj7;
			vector< T8 > copy_obj8;
			for( size_t i = 0; i < obj.size(); ++ i )
			{
				copy_obj1.push_back( get< 0 >( obj[ i ] ) );
				copy_obj2.push_back( get< 1 >( obj[ i ] ) );
				copy_obj3.push_back( get< 2 >( obj[ i ] ) );
				copy_obj4.push_back( get< 3 >( obj[ i ] ) );
				copy_obj5.push_back( get< 4 >( obj[ i ] ) );
				copy_obj6.push_back( get< 5 >( obj[ i ] ) );
				copy_obj7.push_back( get< 6 >( obj[ i ] ) );
				copy_obj8.push_back( get< 7 >( obj[ i ] ) );
			}
			TypeHandler< vector< T1 > >::bind( pos, copy_obj1, pBinder );
			TypeHandler< vector< T2 > >::bind( pos + 1, copy_obj2, pBinder );
			TypeHandler< vector< T3 > >::bind( pos + 2, copy_obj3, pBinder );
			TypeHandler< vector< T4 > >::bind( pos + 3, copy_obj4, pBinder );
			TypeHandler< vector< T5 > >::bind( pos + 4, copy_obj5, pBinder );
			TypeHandler< vector< T6 > >::bind( pos + 5, copy_obj6, pBinder );
			TypeHandler< vector< T7 > >::bind( pos + 6, copy_obj7, pBinder );
			TypeHandler< vector< T8 > >::bind( pos + 7, copy_obj8, pBinder );
		}

		static std::size_t size()
		{
			return TypeHandler< tuple< T1 > >::size()
				+  TypeHandler< tuple< T2 > >::size()
				+  TypeHandler< tuple< T3 > >::size()
				+  TypeHandler< tuple< T4 > >::size()
				+  TypeHandler< tuple< T5 > >::size()
				+  TypeHandler< tuple< T6 > >::size()
				+  TypeHandler< tuple< T7 > >::size()
				+  TypeHandler< tuple< T8 > >::size();
		}

	private:
		TypeHandler();
		~TypeHandler();
		TypeHandler(const TypeHandler&);
		TypeHandler& operator = (const TypeHandler&);
	};

	// specialize vector for batched bind
	template < class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9 >
	class TypeHandler< vector< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9 > > >
	{
	public:
		static void bind(std::size_t pos, const vector< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9 > >& obj, AbstractBinder* pBinder)
		{
			assert( pBinder != 0 );
			vector< T1 > copy_obj1;
			vector< T2 > copy_obj2;
			vector< T3 > copy_obj3;
			vector< T4 > copy_obj4;
			vector< T5 > copy_obj5;
			vector< T6 > copy_obj6;
			vector< T7 > copy_obj7;
			vector< T8 > copy_obj8;
			vector< T9 > copy_obj9;
			for( size_t i = 0; i < obj.size(); ++ i )
			{
				copy_obj1.push_back( get< 0 >( obj[ i ] ) );
				copy_obj2.push_back( get< 1 >( obj[ i ] ) );
				copy_obj3.push_back( get< 2 >( obj[ i ] ) );
				copy_obj4.push_back( get< 3 >( obj[ i ] ) );
				copy_obj5.push_back( get< 4 >( obj[ i ] ) );
				copy_obj6.push_back( get< 5 >( obj[ i ] ) );
				copy_obj7.push_back( get< 6 >( obj[ i ] ) );
				copy_obj8.push_back( get< 7 >( obj[ i ] ) );
				copy_obj9.push_back( get< 8 >( obj[ i ] ) );
			}
			TypeHandler< vector< T1 > >::bind( pos, copy_obj1, pBinder );
			TypeHandler< vector< T2 > >::bind( pos + 1, copy_obj2, pBinder );
			TypeHandler< vector< T3 > >::bind( pos + 2, copy_obj3, pBinder );
			TypeHandler< vector< T4 > >::bind( pos + 3, copy_obj4, pBinder );
			TypeHandler< vector< T5 > >::bind( pos + 4, copy_obj5, pBinder );
			TypeHandler< vector< T6 > >::bind( pos + 5, copy_obj6, pBinder );
			TypeHandler< vector< T7 > >::bind( pos + 6, copy_obj7, pBinder );
			TypeHandler< vector< T8 > >::bind( pos + 7, copy_obj8, pBinder );
			TypeHandler< vector< T9 > >::bind( pos + 8, copy_obj9, pBinder );
		}

		static std::size_t size()
		{
			return TypeHandler< tuple< T1 > >::size()
				+  TypeHandler< tuple< T2 > >::size()
				+  TypeHandler< tuple< T3 > >::size()
				+  TypeHandler< tuple< T4 > >::size()
				+  TypeHandler< tuple< T5 > >::size()
				+  TypeHandler< tuple< T6 > >::size()
				+  TypeHandler< tuple< T7 > >::size()
				+  TypeHandler< tuple< T8 > >::size()
				+  TypeHandler< tuple< T9 > >::size();
		}

	private:
		TypeHandler();
		~TypeHandler();
		TypeHandler(const TypeHandler&);
		TypeHandler& operator = (const TypeHandler&);
	};

	// specialize vector for batched bind
	template < class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10 >
	class TypeHandler< vector< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9, T10 > > >
	{
	public:
		static void bind(std::size_t pos, const vector< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9, T10 > >& obj, AbstractBinder* pBinder)
		{
			assert( pBinder != 0 );
			vector< T1 > copy_obj1;
			vector< T2 > copy_obj2;
			vector< T3 > copy_obj3;
			vector< T4 > copy_obj4;
			vector< T5 > copy_obj5;
			vector< T6 > copy_obj6;
			vector< T7 > copy_obj7;
			vector< T8 > copy_obj8;
			vector< T9 > copy_obj9;
			vector< T10 > copy_obj10;
			for( size_t i = 0; i < obj.size(); ++ i )
			{
				copy_obj1.push_back( get< 0 >( obj[ i ] ) );
				copy_obj2.push_back( get< 1 >( obj[ i ] ) );
				copy_obj3.push_back( get< 2 >( obj[ i ] ) );
				copy_obj4.push_back( get< 3 >( obj[ i ] ) );
				copy_obj5.push_back( get< 4 >( obj[ i ] ) );
				copy_obj6.push_back( get< 5 >( obj[ i ] ) );
				copy_obj7.push_back( get< 6 >( obj[ i ] ) );
				copy_obj8.push_back( get< 7 >( obj[ i ] ) );
				copy_obj9.push_back( get< 8 >( obj[ i ] ) );
				copy_obj10.push_back( get< 9 >( obj[ i ] ) );
			}
			TypeHandler< vector< T1 > >::bind( pos, copy_obj1, pBinder );
			TypeHandler< vector< T2 > >::bind( pos + 1, copy_obj2, pBinder );
			TypeHandler< vector< T3 > >::bind( pos + 2, copy_obj3, pBinder );
			TypeHandler< vector< T4 > >::bind( pos + 3, copy_obj4, pBinder );
			TypeHandler< vector< T5 > >::bind( pos + 4, copy_obj5, pBinder );
			TypeHandler< vector< T6 > >::bind( pos + 5, copy_obj6, pBinder );
			TypeHandler< vector< T7 > >::bind( pos + 6, copy_obj7, pBinder );
			TypeHandler< vector< T8 > >::bind( pos + 7, copy_obj8, pBinder );
			TypeHandler< vector< T9 > >::bind( pos + 8, copy_obj9, pBinder );
			TypeHandler< vector< T10 > >::bind( pos + 9, copy_obj10, pBinder );
		}

		static std::size_t size()
		{
			return TypeHandler< tuple< T1 > >::size()
				+  TypeHandler< tuple< T2 > >::size()
				+  TypeHandler< tuple< T3 > >::size()
				+  TypeHandler< tuple< T4 > >::size()
				+  TypeHandler< tuple< T5 > >::size()
				+  TypeHandler< tuple< T6 > >::size()
				+  TypeHandler< tuple< T7 > >::size()
				+  TypeHandler< tuple< T8 > >::size()
				+  TypeHandler< tuple< T9 > >::size()
				+  TypeHandler< tuple< T10 > >::size();
		}

	private:
		TypeHandler();
		~TypeHandler();
		TypeHandler(const TypeHandler&);
		TypeHandler& operator = (const TypeHandler&);
	};
}