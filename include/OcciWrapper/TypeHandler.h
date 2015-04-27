#pragma once
#include "OcciWrapper/Common.h"
#include <assert.h>
#include "OcciWrapper/AbstractBinding.h"
#include "OcciWrapper/AbstractBinder.h"
#include <tuple>
#include <functional> 
#include <string>
#include <vector>
#include <iostream>
#include <limits>
#include "OcciWrapper/Exception.h"
#include "OcciWrapper/AbstractExtractor.h"
#include <string.h>
#include <malloc.h>

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
				tmRet.tm_hour =  *( ( unsigned char* )pBuf + 4 );
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

		static void retrieve( std::size_t pos, T& obj, AbstractBinder* p_binder )
		{
			assert( p_binder != 0 );
			p_binder->Retrieve( pos, obj );
		}

		//static void batched_bind( std::size_t pos, const vector<T>& vec_obj, AbstractBinder* pBinder );

		static std::size_t size()
		{
			return 1;
		}

		//static void extract( std::size_t pos, T& obj, AbstractExtractor* pExt )
		static void extract( std::size_t pos, AbstractExtractor* pExt )
		{
			assert( pExt != 0 );
			// only one data to retrieve
			size_t nRowRetrieve = 1;
			
			size_t nAllBufLength = sizeof( T ) * nRowRetrieve;
			// set buffer
			T* p = ( T* )malloc( nAllBufLength );
			// set length array
			UInt16* p_length = ( UInt16* )malloc( sizeof( UInt16 ) * nRowRetrieve );
			// set indicator
			Int16* p_Ind = ( Int16* )malloc( sizeof( Int16 ) * nRowRetrieve );

			pExt->Extract( pos, p, sizeof(T), p_length, p_Ind, TypeConvertor< T >::Convert() );
		}

		static void fetch( std::size_t pos, T& objResult, AbstractExtractor* pExtractor, vector< shared_ptr< OcciDataBuffer > >&  vecDataBuf, size_t nFetchedNum )
		{
			assert( vecDataBuf.size() == 1 );
			shared_ptr< OcciDataBuffer > pDataBuf = vecDataBuf[ 0 ];
			objResult = TypeConvertor< T >::retrieve( ( ( void* )( ( char* )pDataBuf->m_pBuffer + pDataBuf->m_nDataBufMaxPerLength * 0 ) ) , *( pDataBuf->m_pDataLength + 0 ), *( pDataBuf->m_pInd + 0 ) );
		}

	private:
		TypeHandler();
		~TypeHandler();
		TypeHandler(const TypeHandler&);
		TypeHandler& operator = (const TypeHandler&);
	};

	/***
	*	@add by CUCmehp
	*/
	template <>
	class TypeHandler< string >
	{
	public:
		static void bind(std::size_t pos, const string& obj, AbstractBinder* pBinder)
		{
			assert( pBinder != 0 );
			pBinder->Bind( pos, obj );
		}

		static void retrieve( std::size_t pos, string& obj, AbstractBinder* p_binder )
		{
			assert( p_binder != 0 );
			p_binder->Retrieve( pos, obj );
		}

		static std::size_t size()
		{
			return 1;
		}

		//static void extract( std::size_t pos, string& obj, AbstractExtractor* pExt )
		static void extract( std::size_t pos, AbstractExtractor* pExt )
		{
			size_t nCharBufMax = 4000;
			assert( pExt != 0 );
			// only one data to retrieve
			size_t nRowRetrieve = 1;
			size_t nAllBufLength = nCharBufMax * nRowRetrieve;
			// set buffer
			char* p = ( char* )malloc( nAllBufLength );
			// set length array
			UInt16* p_length = ( UInt16* )malloc( sizeof( UInt16 ) * nRowRetrieve );
			// set indicator
			Int16* p_Ind = ( Int16* )malloc( sizeof( Int16 ) * nRowRetrieve );

			pExt->Extract( pos, p, nCharBufMax, p_length, p_Ind, TypeConvertor< string >::Convert() );
		}

		static void fetch( std::size_t pos, string& objResult, AbstractExtractor* pExtractor, vector< shared_ptr< OcciDataBuffer > >& vDataBuf, size_t nFetchedNum )
		{
			assert( nFetchedNum == 1 );
			assert( vDataBuf.size() == 1 );
			shared_ptr< OcciDataBuffer > pDataBuf = vDataBuf[ 0 ];
			objResult = TypeConvertor< string >::retrieve( ( ( void* )( ( char* )pDataBuf->m_pBuffer + pDataBuf->m_nDataBufMaxPerLength * 0 ) ) , *( pDataBuf->m_pDataLength + 0 ), *( pDataBuf->m_pInd + 0 ) );
		}

	private:
		TypeHandler();
		~TypeHandler();
		TypeHandler(const TypeHandler&);
		TypeHandler& operator = (const TypeHandler&);
	};

	/***
	*	@add by CUCmehp
	*/
	template <>
	class TypeHandler< struct tm >
	{
	public:
		static void bind(std::size_t pos, const struct tm& obj, AbstractBinder* pBinder)
		{
			assert( pBinder != 0 );
			pBinder->Bind( pos, obj );
		}

		static void retrieve( std::size_t pos, struct tm& obj, AbstractBinder* p_binder )
		{
			assert( p_binder != 0 );
			p_binder->Retrieve( pos, obj );
		}

		static std::size_t size()
		{
			return 1;
		}

		//static void extract( std::size_t pos, struct tm& obj, AbstractExtractor* pExt )
		static void extract( std::size_t pos, AbstractExtractor* pExt )
		{
			size_t nCharBufMax = 8;
			assert( pExt != 0 );
			// only one data to retrieve
			size_t nRowRetrieve = 1;
			size_t nAllBufLength = nCharBufMax * nRowRetrieve;
			// set buffer
			char* p = ( char* )malloc( nAllBufLength );
			// set length array
			UInt16* p_length = ( UInt16* )malloc( sizeof( UInt16 ) * nRowRetrieve );
			// set indicator
			Int16* p_Ind = ( Int16* )malloc( sizeof( Int16 ) * nRowRetrieve );
			pExt->Extract( pos, p, nCharBufMax, p_length, p_Ind, TypeConvertor< struct tm >::Convert() );
		}

		static void fetch( std::size_t pos, struct tm& objResult, AbstractExtractor* pExtractor, vector< shared_ptr< OcciDataBuffer > >& vDataBuf, size_t nFetchedNum )
		{
			assert( nFetchedNum == 1 );
			assert( vDataBuf.size() == 1 );
			shared_ptr< OcciDataBuffer > pDataBuf = vDataBuf[ 0 ];
			objResult = TypeConvertor< struct tm >::retrieve( ( ( void* )( ( char* )pDataBuf->m_pBuffer + pDataBuf->m_nDataBufMaxPerLength * 0 ) ) , *( pDataBuf->m_pDataLength + 0 ), *( pDataBuf->m_pInd + 0 ) );
		}

	private:
		TypeHandler();
		~TypeHandler();
		TypeHandler(const TypeHandler&);
		TypeHandler& operator = (const TypeHandler&);
	};

	template < typename TupleType, typename Type, int N >
	void tupleBind( std::size_t& pos, TupleType tuple, AbstractBinder* pBinder )
	{
		TypeHandler<Type>::bind(pos, get<N>(tuple), pBinder);
		pos += TypeHandler<Type>::size();
	}

	template < typename TupleType, typename Type, int N >
	void tupleRetrieve( std::size_t& pos, TupleType tuple, AbstractBinder* pBinder )
	{
		TypeHandler<Type>::retrieve( pos, get<N>(tuple), pBinder );
		pos += TypeHandler<Type>::size();
	}

	template < typename Type, int N >
	void tupleExtract( std::size_t& pos, AbstractExtractor* pExtractor )
	{
		TypeHandler<Type>::extract( pos, pExtractor );
		pos += TypeHandler<Type>::size();
	}

	template < typename TupleType, typename Type, int N >
	void tupleFetch( std::size_t& pos, TupleType& tuple, AbstractExtractor* pExtractor, vector< shared_ptr< OcciDataBuffer > >& vDataBuf, size_t nFetchedNum )
	{
		assert( vDataBuf.size() == 1 );
		TypeHandler< Type >::fetch( pos, get<N>(tuple), pExtractor, vDataBuf, nFetchedNum );
		pos += TypeHandler<Type>::size();
	}

	// specialize tuple, tuple size = 1
	template < class T1 >
	class TypeHandler< tuple< T1 > >
	{
	public:
		static void bind( std::size_t pos, const tuple< T1 >& obj, AbstractBinder* pBinder )
		{
			assert( pBinder != 0 );
			tupleBind< tuple< T1 >, T1, 0 >( pos, obj, pBinder );
		}

		static void retrieve( std::size_t pos, tuple< T1 >& obj, AbstractBinder* pBinder )
		{
			assert( pBinder != 0 );
			tupleRetrieve< tuple< T1 >, T1, 0 >( pos, obj, pBinder );
		}

		static void extract( std::size_t pos, AbstractExtractor* pExtractor )
		{
			assert( pExtractor != 0 );
			tupleExtract< T1, 0 >( pos, pExtractor );
		}

		static void fetch( std::size_t pos, tuple< T1 >& obj, AbstractExtractor* pExtractor, vector< shared_ptr< OcciDataBuffer > >& vDataBuf, size_t nFetchedNum )
		{
			assert( pExtractor != 0 );
			assert( vDataBuf.size() == 1 );
			tupleFetch< tuple< T1 >, T1, 0 >( pos, obj, pExtractor, vDataBuf, nFetchedNum );
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

		static void retrieve( std::size_t pos, tuple< T1 ,T2 >& obj, AbstractBinder* pBinder )
		{
			assert( pBinder != 0 );
			tupleRetrieve< tuple< T1, T2 >, T1, 0 >( pos, obj, pBinder );
			tupleRetrieve< tuple< T1, T2 >, T2, 1 >( pos, obj, pBinder );
		}

		//static void extract( std::size_t pos, tuple< T1, T2 >& obj, AbstractExtractor* pExtractor )
		static void extract( std::size_t pos, AbstractExtractor* pExtractor )
		{
			assert( pExtractor != 0 );
			tupleExtract< T1, 0 >( pos, pExtractor );
			tupleExtract< T2, 1 >( pos, pExtractor );
		}

		static void fetch( std::size_t pos, tuple< T1, T2 >& obj, AbstractExtractor* pExtractor, vector< shared_ptr< OcciDataBuffer > >& vDataBuf, size_t nFetchedNum )
		{
			assert( pExtractor != 0 );
			assert( vDataBuf.size() == 2 );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf1;
			vDataBuf1.push_back( vDataBuf[ 0 ] );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf2;
			vDataBuf2.push_back( vDataBuf[ 1 ] );
			tupleFetch< tuple< T1, T2 >, T1, 0 >( pos, obj, pExtractor, vDataBuf1, nFetchedNum );
			tupleFetch< tuple< T1, T2 >, T2, 1 >( pos, obj, pExtractor, vDataBuf2, nFetchedNum );
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

		static void retrieve( std::size_t pos, tuple< T1 ,T2, T3 >& obj, AbstractBinder* pBinder )
		{
			assert( pBinder != 0 );
			tupleRetrieve< tuple< T1, T2, T3 >, T1, 0 >( pos, obj, pBinder );
			tupleRetrieve< tuple< T1, T2, T3 >, T2, 1 >( pos, obj, pBinder );
			tupleRetrieve< tuple< T1, T2, T3 >, T3, 2 >( pos, obj, pBinder );
		}

		static void extract( std::size_t pos, AbstractExtractor* pExtractor )
		{
			assert( pExtractor != 0 );
			tupleExtract< T1, 0 >( pos, pExtractor );
			tupleExtract< T2, 1 >( pos, pExtractor );
			tupleExtract< T3, 2 >( pos, pExtractor );
		}

		static void fetch( std::size_t pos, tuple< T1, T2, T3 >& obj, AbstractExtractor* pExtractor, vector< shared_ptr< OcciDataBuffer > >& vDataBuf, size_t nFetchedNum )
		{
			assert( pExtractor != 0 );
			assert( vDataBuf.size() == 3 );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf1;
			vDataBuf1.push_back( vDataBuf[ 0 ] );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf2;
			vDataBuf2.push_back( vDataBuf[ 1 ] );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf3;
			vDataBuf3.push_back( vDataBuf[ 2 ] );
			tupleFetch< tuple< T1, T2, T3 >, T1, 0 >( pos, obj, pExtractor, vDataBuf1, nFetchedNum );
			tupleFetch< tuple< T1, T2, T3 >, T2, 1 >( pos, obj, pExtractor, vDataBuf2, nFetchedNum );
			tupleFetch< tuple< T1, T2, T3 >, T3, 2 >( pos, obj, pExtractor, vDataBuf3, nFetchedNum );
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

		static void retrieve( std::size_t pos, tuple< T1 ,T2, T3, T4 >& obj, AbstractBinder* pBinder )
		{
			assert( pBinder != 0 );
			tupleRetrieve< tuple< T1, T2, T3, T4 >, T1, 0 >( pos, obj, pBinder );
			tupleRetrieve< tuple< T1, T2, T3, T4 >, T2, 1 >( pos, obj, pBinder );
			tupleRetrieve< tuple< T1, T2, T3, T4 >, T3, 2 >( pos, obj, pBinder );
			tupleRetrieve< tuple< T1, T2, T3, T4 >, T4, 3 >( pos, obj, pBinder );
		}

		static void extract( std::size_t pos, AbstractExtractor* pExtractor )
		{
			assert( pExtractor != 0 );
			tupleExtract< T1, 0 >( pos, pExtractor );
			tupleExtract< T2, 1 >( pos, pExtractor );
			tupleExtract< T3, 2 >( pos, pExtractor );
			tupleExtract< T4, 3 >( pos, pExtractor );
		}

		static void fetch( std::size_t pos, tuple< T1, T2, T3, T4 >& obj, AbstractExtractor* pExtractor, vector< shared_ptr< OcciDataBuffer > >& vDataBuf, size_t nFetchedNum )
		{
			assert( pExtractor != 0 );
			assert( vDataBuf.size() == 4 );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf1;
			vDataBuf1.push_back( vDataBuf[ 0 ] );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf2;
			vDataBuf2.push_back( vDataBuf[ 1 ] );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf3;
			vDataBuf3.push_back( vDataBuf[ 2 ] );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf4;
			vDataBuf4.push_back( vDataBuf[ 3 ] );
			tupleFetch< tuple< T1, T2, T3, T4 >, T1, 0 >( pos, obj, pExtractor, vDataBuf1, nFetchedNum );
			tupleFetch< tuple< T1, T2, T3, T4 >, T2, 1 >( pos, obj, pExtractor, vDataBuf2, nFetchedNum );
			tupleFetch< tuple< T1, T2, T3, T4 >, T3, 2 >( pos, obj, pExtractor, vDataBuf3, nFetchedNum );
			tupleFetch< tuple< T1, T2, T3, T4 >, T4, 3 >( pos, obj, pExtractor, vDataBuf4, nFetchedNum );
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

		static void retrieve( std::size_t pos, tuple< T1 ,T2, T3, T4, T5 >& obj, AbstractBinder* pBinder )
		{
			assert( pBinder != 0 );
			tupleRetrieve< tuple< T1, T2, T3, T4, T5 >, T1, 0 >( pos, obj, pBinder );
			tupleRetrieve< tuple< T1, T2, T3, T4, T5 >, T2, 1 >( pos, obj, pBinder );
			tupleRetrieve< tuple< T1, T2, T3, T4, T5 >, T3, 2 >( pos, obj, pBinder );
			tupleRetrieve< tuple< T1, T2, T3, T4, T5 >, T4, 3 >( pos, obj, pBinder );
			tupleRetrieve< tuple< T1, T2, T3, T4, T5 >, T5, 4 >( pos, obj, pBinder );
		}

		//static void extract( std::size_t pos, tuple< T1, T2, T3, T4, T5 >& obj, AbstractExtractor* pExtractor )
		static void extract( std::size_t pos, AbstractExtractor* pExtractor )
		{
			assert( pExtractor != 0 );
			tupleExtract< T1, 0 >( pos, pExtractor );
			tupleExtract< T2, 1 >( pos, pExtractor );
			tupleExtract< T3, 2 >( pos, pExtractor );
			tupleExtract< T4, 3 >( pos, pExtractor );
			tupleExtract< T5, 4 >( pos, pExtractor );
		}

		static void fetch( std::size_t pos, tuple< T1, T2, T3, T4, T5 >& obj, AbstractExtractor* pExtractor, vector< shared_ptr< OcciDataBuffer > >& vDataBuf, size_t nFetchedNum )
		{
			assert( pExtractor != 0 );
			assert( vDataBuf.size() == 5 );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf1;
			vDataBuf1.push_back( vDataBuf[ 0 ] );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf2;
			vDataBuf2.push_back( vDataBuf[ 1 ] );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf3;
			vDataBuf3.push_back( vDataBuf[ 2 ] );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf4;
			vDataBuf4.push_back( vDataBuf[ 3 ] );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf5;
			vDataBuf5.push_back( vDataBuf[ 4 ] );
			tupleFetch< tuple< T1, T2, T3, T4, T5 >, T1, 0 >( pos, obj, pExtractor, vDataBuf1, nFetchedNum );
			tupleFetch< tuple< T1, T2, T3, T4, T5 >, T2, 1 >( pos, obj, pExtractor, vDataBuf2, nFetchedNum );
			tupleFetch< tuple< T1, T2, T3, T4, T5 >, T3, 2 >( pos, obj, pExtractor, vDataBuf3, nFetchedNum );
			tupleFetch< tuple< T1, T2, T3, T4, T5 >, T4, 3 >( pos, obj, pExtractor, vDataBuf4, nFetchedNum );
			tupleFetch< tuple< T1, T2, T3, T4, T5 >, T5, 4 >( pos, obj, pExtractor, vDataBuf5, nFetchedNum );
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

	// specialize tuple, tuple size = 6
	template < class T1, class T2, class T3, class T4, class T5, class T6 >
	class TypeHandler< tuple< T1, T2, T3, T4, T5, T6 > >
	{
	public:
		static void bind(std::size_t pos, const tuple< T1 ,T2, T3, T4, T5, T6 >& obj, AbstractBinder* pBinder)
		{
			assert( pBinder != 0 );
			tupleBind< tuple< T1 ,T2, T3, T4, T5, T6 >, T1, 0 >( pos, obj, pBinder );
			tupleBind< tuple< T1 ,T2, T3, T4, T5, T6 >, T2, 1 >( pos, obj, pBinder );
			tupleBind< tuple< T1 ,T2, T3, T4, T5, T6 >, T3, 2 >( pos, obj, pBinder );
			tupleBind< tuple< T1 ,T2, T3, T4, T5, T6 >, T4, 3 >( pos, obj, pBinder );
			tupleBind< tuple< T1 ,T2, T3, T4, T5, T6 >, T5, 4 >( pos, obj, pBinder );
			tupleBind< tuple< T1 ,T2, T3, T4, T5, T6 >, T6, 5 >( pos, obj, pBinder );
		}

		static void retrieve( std::size_t pos, tuple< T1 ,T2, T3, T4, T5, T6 >& obj, AbstractBinder* pBinder )
		{
			assert( pBinder != 0 );
			tupleRetrieve< tuple< T1, T2, T3, T4, T5, T6 >, T1, 0 >( pos, obj, pBinder );
			tupleRetrieve< tuple< T1, T2, T3, T4, T5, T6 >, T2, 1 >( pos, obj, pBinder );
			tupleRetrieve< tuple< T1, T2, T3, T4, T5, T6 >, T3, 2 >( pos, obj, pBinder );
			tupleRetrieve< tuple< T1, T2, T3, T4, T5, T6 >, T4, 3 >( pos, obj, pBinder );
			tupleRetrieve< tuple< T1, T2, T3, T4, T5, T6 >, T5, 4 >( pos, obj, pBinder );
			tupleRetrieve< tuple< T1, T2, T3, T4, T5, T6 >, T6, 5 >( pos, obj, pBinder );
		}

		static void extract( std::size_t pos, AbstractExtractor* pExtractor )
		{
			assert( pExtractor != 0 );
			tupleExtract< T1, 0 >( pos, pExtractor );
			tupleExtract< T2, 1 >( pos, pExtractor );
			tupleExtract< T3, 2 >( pos, pExtractor );
			tupleExtract< T4, 3 >( pos, pExtractor );
			tupleExtract< T5, 4 >( pos, pExtractor );
			tupleExtract< T6, 5 >( pos, pExtractor );
		}

		static void fetch( std::size_t pos, tuple< T1, T2, T3, T4, T5, T6 >& obj, AbstractExtractor* pExtractor, vector< shared_ptr< OcciDataBuffer > >& vDataBuf, size_t nFetchedNum )
		{
			assert( pExtractor != 0 );
			assert( vDataBuf.size() == 6 );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf1;
			vDataBuf1.push_back( vDataBuf[ 0 ] );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf2;
			vDataBuf2.push_back( vDataBuf[ 1 ] );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf3;
			vDataBuf3.push_back( vDataBuf[ 2 ] );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf4;
			vDataBuf4.push_back( vDataBuf[ 3 ] );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf5;
			vDataBuf5.push_back( vDataBuf[ 4 ] );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf6;
			vDataBuf6.push_back( vDataBuf[ 5 ] );
			tupleFetch< tuple< T1, T2, T3, T4, T5, T6 >, T1, 0 >( pos, obj, pExtractor, vDataBuf1, nFetchedNum );
			tupleFetch< tuple< T1, T2, T3, T4, T5, T6 >, T2, 1 >( pos, obj, pExtractor, vDataBuf2, nFetchedNum );
			tupleFetch< tuple< T1, T2, T3, T4, T5, T6 >, T3, 2 >( pos, obj, pExtractor, vDataBuf3, nFetchedNum );
			tupleFetch< tuple< T1, T2, T3, T4, T5, T6 >, T4, 3 >( pos, obj, pExtractor, vDataBuf4, nFetchedNum );
			tupleFetch< tuple< T1, T2, T3, T4, T5, T6 >, T5, 4 >( pos, obj, pExtractor, vDataBuf5, nFetchedNum );
			tupleFetch< tuple< T1, T2, T3, T4, T5, T6 >, T6, 5 >( pos, obj, pExtractor, vDataBuf6, nFetchedNum );
		}

		static std::size_t size()
		{
			return TypeHandler< T1 >::size()
				 + TypeHandler< T2 >::size() 
				 + TypeHandler< T3 >::size()
				 + TypeHandler< T4 >::size() 
				 + TypeHandler< T5 >::size() 
				 + TypeHandler< T6 >::size();
		}

	private:
		TypeHandler();
		~TypeHandler();
		TypeHandler(const TypeHandler&);
		TypeHandler& operator = (const TypeHandler&);
	};

	// specialize tuple, tuple size = 7
	template < class T1, class T2, class T3, class T4, class T5, class T6, class T7 >
	class TypeHandler< tuple< T1, T2, T3, T4, T5, T6, T7 > >
	{
	public:
		static void bind(std::size_t pos, const tuple< T1 ,T2, T3, T4, T5, T6, T7 >& obj, AbstractBinder* pBinder)
		{
			assert( pBinder != 0 );
			tupleBind< tuple< T1 ,T2, T3, T4, T5, T6, T7 >, T1, 0 >( pos, obj, pBinder );
			tupleBind< tuple< T1 ,T2, T3, T4, T5, T6, T7 >, T2, 1 >( pos, obj, pBinder );
			tupleBind< tuple< T1 ,T2, T3, T4, T5, T6, T7 >, T3, 2 >( pos, obj, pBinder );
			tupleBind< tuple< T1 ,T2, T3, T4, T5, T6, T7 >, T4, 3 >( pos, obj, pBinder );
			tupleBind< tuple< T1 ,T2, T3, T4, T5, T6, T7 >, T5, 4 >( pos, obj, pBinder );
			tupleBind< tuple< T1 ,T2, T3, T4, T5, T6, T7 >, T6, 5 >( pos, obj, pBinder );
			tupleBind< tuple< T1 ,T2, T3, T4, T5, T6, T7 >, T7, 6 >( pos, obj, pBinder );
		}

		static void retrieve( std::size_t pos, tuple< T1 ,T2, T3, T4, T5, T6, T7 >& obj, AbstractBinder* pBinder )
		{
			assert( pBinder != 0 );
			tupleRetrieve< tuple< T1, T2, T3, T4, T5, T6, T7 >, T1, 0 >( pos, obj, pBinder );
			tupleRetrieve< tuple< T1, T2, T3, T4, T5, T6, T7 >, T2, 1 >( pos, obj, pBinder );
			tupleRetrieve< tuple< T1, T2, T3, T4, T5, T6, T7 >, T3, 2 >( pos, obj, pBinder );
			tupleRetrieve< tuple< T1, T2, T3, T4, T5, T6, T7 >, T4, 3 >( pos, obj, pBinder );
			tupleRetrieve< tuple< T1, T2, T3, T4, T5, T6, T7 >, T5, 4 >( pos, obj, pBinder );
			tupleRetrieve< tuple< T1, T2, T3, T4, T5, T6, T7 >, T6, 5 >( pos, obj, pBinder );
			tupleRetrieve< tuple< T1, T2, T3, T4, T5, T6, T7 >, T7, 6 >( pos, obj, pBinder );
		}

		static void extract( std::size_t pos, AbstractExtractor* pExtractor )
		{
			assert( pExtractor != 0 );
			tupleExtract< T1, 0 >( pos, pExtractor );
			tupleExtract< T2, 1 >( pos, pExtractor );
			tupleExtract< T3, 2 >( pos, pExtractor );
			tupleExtract< T4, 3 >( pos, pExtractor );
			tupleExtract< T5, 4 >( pos, pExtractor );
			tupleExtract< T6, 5 >( pos, pExtractor );
			tupleExtract< T7, 6 >( pos, pExtractor );
		}

		static void fetch( std::size_t pos, tuple< T1, T2, T3, T4, T5, T6, T7 >& obj, AbstractExtractor* pExtractor, vector< shared_ptr< OcciDataBuffer > >& vDataBuf, size_t nFetchedNum )
		{
			assert( pExtractor != 0 );
			assert( vDataBuf.size() == 7 );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf1;
			vDataBuf1.push_back( vDataBuf[ 0 ] );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf2;
			vDataBuf2.push_back( vDataBuf[ 1 ] );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf3;
			vDataBuf3.push_back( vDataBuf[ 2 ] );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf4;
			vDataBuf4.push_back( vDataBuf[ 3 ] );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf5;
			vDataBuf5.push_back( vDataBuf[ 4 ] );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf6;
			vDataBuf6.push_back( vDataBuf[ 5 ] );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf7;
			vDataBuf7.push_back( vDataBuf[ 6 ] );
			tupleFetch< tuple< T1, T2, T3, T4, T5, T6, T7 >, T1, 0 >( pos, obj, pExtractor, vDataBuf1, nFetchedNum );
			tupleFetch< tuple< T1, T2, T3, T4, T5, T6, T7 >, T2, 1 >( pos, obj, pExtractor, vDataBuf2, nFetchedNum );
			tupleFetch< tuple< T1, T2, T3, T4, T5, T6, T7 >, T3, 2 >( pos, obj, pExtractor, vDataBuf3, nFetchedNum );
			tupleFetch< tuple< T1, T2, T3, T4, T5, T6, T7 >, T4, 3 >( pos, obj, pExtractor, vDataBuf4, nFetchedNum );
			tupleFetch< tuple< T1, T2, T3, T4, T5, T6, T7 >, T5, 4 >( pos, obj, pExtractor, vDataBuf5, nFetchedNum );
			tupleFetch< tuple< T1, T2, T3, T4, T5, T6, T7 >, T6, 5 >( pos, obj, pExtractor, vDataBuf6, nFetchedNum );
			tupleFetch< tuple< T1, T2, T3, T4, T5, T6, T7 >, T7, 6 >( pos, obj, pExtractor, vDataBuf7, nFetchedNum );
		}

		static std::size_t size()
		{
			return TypeHandler< T1 >::size()
				 + TypeHandler< T2 >::size() 
				 + TypeHandler< T3 >::size()
				 + TypeHandler< T4 >::size() 
				 + TypeHandler< T5 >::size() 
				 + TypeHandler< T6 >::size()
				 + TypeHandler< T7 >::size();
		}

	private:
		TypeHandler();
		~TypeHandler();
		TypeHandler(const TypeHandler&);
		TypeHandler& operator = (const TypeHandler&);
	};

	// specialize tuple, tuple size = 8
	template < class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8 >
	class TypeHandler< tuple< T1, T2, T3, T4, T5, T6, T7, T8 > >
	{
	public:
		static void bind(std::size_t pos, const tuple< T1 ,T2, T3, T4, T5, T6, T7, T8 >& obj, AbstractBinder* pBinder)
		{
			assert( pBinder != 0 );
			tupleBind< tuple< T1 ,T2, T3, T4, T5, T6, T7, T8 >, T1, 0 >( pos, obj, pBinder );
			tupleBind< tuple< T1 ,T2, T3, T4, T5, T6, T7, T8 >, T2, 1 >( pos, obj, pBinder );
			tupleBind< tuple< T1 ,T2, T3, T4, T5, T6, T7, T8 >, T3, 2 >( pos, obj, pBinder );
			tupleBind< tuple< T1 ,T2, T3, T4, T5, T6, T7, T8 >, T4, 3 >( pos, obj, pBinder );
			tupleBind< tuple< T1 ,T2, T3, T4, T5, T6, T7, T8 >, T5, 4 >( pos, obj, pBinder );
			tupleBind< tuple< T1 ,T2, T3, T4, T5, T6, T7, T8 >, T6, 5 >( pos, obj, pBinder );
			tupleBind< tuple< T1 ,T2, T3, T4, T5, T6, T7, T8 >, T7, 6 >( pos, obj, pBinder );
			tupleBind< tuple< T1 ,T2, T3, T4, T5, T6, T7, T8 >, T8, 7 >( pos, obj, pBinder );
		}

		static void retrieve( std::size_t pos, tuple< T1 ,T2, T3, T4, T5, T6, T7, T8 >& obj, AbstractBinder* pBinder )
		{
			assert( pBinder != 0 );
			tupleRetrieve< tuple< T1, T2, T3, T4, T5, T6, T7, T8 >, T1, 0 >( pos, obj, pBinder );
			tupleRetrieve< tuple< T1, T2, T3, T4, T5, T6, T7, T8 >, T2, 1 >( pos, obj, pBinder );
			tupleRetrieve< tuple< T1, T2, T3, T4, T5, T6, T7, T8 >, T3, 2 >( pos, obj, pBinder );
			tupleRetrieve< tuple< T1, T2, T3, T4, T5, T6, T7, T8 >, T4, 3 >( pos, obj, pBinder );
			tupleRetrieve< tuple< T1, T2, T3, T4, T5, T6, T7, T8 >, T5, 4 >( pos, obj, pBinder );
			tupleRetrieve< tuple< T1, T2, T3, T4, T5, T6, T7, T8 >, T6, 5 >( pos, obj, pBinder );
			tupleRetrieve< tuple< T1, T2, T3, T4, T5, T6, T7, T8 >, T7, 6 >( pos, obj, pBinder );
			tupleRetrieve< tuple< T1, T2, T3, T4, T5, T6, T7, T8 >, T8, 7 >( pos, obj, pBinder );
		}

		static void extract( std::size_t pos, AbstractExtractor* pExtractor )
		{
			assert( pExtractor != 0 );
			tupleExtract< T1, 0 >( pos, pExtractor );
			tupleExtract< T2, 1 >( pos, pExtractor );
			tupleExtract< T3, 2 >( pos, pExtractor );
			tupleExtract< T4, 3 >( pos, pExtractor );
			tupleExtract< T5, 4 >( pos, pExtractor );
			tupleExtract< T6, 5 >( pos, pExtractor );
			tupleExtract< T7, 6 >( pos, pExtractor );
			tupleExtract< T8, 7 >( pos, pExtractor );
		}

		static void fetch( std::size_t pos, tuple< T1, T2, T3, T4, T5, T6, T7, T8 >& obj, AbstractExtractor* pExtractor, vector< shared_ptr< OcciDataBuffer > >& vDataBuf, size_t nFetchedNum )
		{
			assert( pExtractor != 0 );
			assert( vDataBuf.size() == 8 );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf1;
			vDataBuf1.push_back( vDataBuf[ 0 ] );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf2;
			vDataBuf2.push_back( vDataBuf[ 1 ] );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf3;
			vDataBuf3.push_back( vDataBuf[ 2 ] );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf4;
			vDataBuf4.push_back( vDataBuf[ 3 ] );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf5;
			vDataBuf5.push_back( vDataBuf[ 4 ] );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf6;
			vDataBuf6.push_back( vDataBuf[ 5 ] );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf7;
			vDataBuf7.push_back( vDataBuf[ 6 ] );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf8;
			vDataBuf8.push_back( vDataBuf[ 7 ] );
			tupleFetch< tuple< T1, T2, T3, T4, T5, T6, T7, T8 >, T1, 0 >( pos, obj, pExtractor, vDataBuf1, nFetchedNum );
			tupleFetch< tuple< T1, T2, T3, T4, T5, T6, T7, T8 >, T2, 1 >( pos, obj, pExtractor, vDataBuf2, nFetchedNum );
			tupleFetch< tuple< T1, T2, T3, T4, T5, T6, T7, T8 >, T3, 2 >( pos, obj, pExtractor, vDataBuf3, nFetchedNum );
			tupleFetch< tuple< T1, T2, T3, T4, T5, T6, T7, T8 >, T4, 3 >( pos, obj, pExtractor, vDataBuf4, nFetchedNum );
			tupleFetch< tuple< T1, T2, T3, T4, T5, T6, T7, T8 >, T5, 4 >( pos, obj, pExtractor, vDataBuf5, nFetchedNum );
			tupleFetch< tuple< T1, T2, T3, T4, T5, T6, T7, T8 >, T6, 5 >( pos, obj, pExtractor, vDataBuf6, nFetchedNum );
			tupleFetch< tuple< T1, T2, T3, T4, T5, T6, T7, T8 >, T7, 6 >( pos, obj, pExtractor, vDataBuf7, nFetchedNum );
			tupleFetch< tuple< T1, T2, T3, T4, T5, T6, T7, T8 >, T8, 7 >( pos, obj, pExtractor, vDataBuf8, nFetchedNum );
		}

		static std::size_t size()
		{
			return TypeHandler< T1 >::size()
				 + TypeHandler< T2 >::size() 
				 + TypeHandler< T3 >::size()
				 + TypeHandler< T4 >::size() 
				 + TypeHandler< T5 >::size() 
				 + TypeHandler< T6 >::size()
				 + TypeHandler< T7 >::size()
				 + TypeHandler< T8 >::size();
		}

	private:
		TypeHandler();
		~TypeHandler();
		TypeHandler(const TypeHandler&);
		TypeHandler& operator = (const TypeHandler&);
	};

	// specialize tuple, tuple size = 9
	template < class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9 >
	class TypeHandler< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9 > >
	{
	public:
		static void bind(std::size_t pos, const tuple< T1 ,T2, T3, T4, T5, T6, T7, T8, T9 >& obj, AbstractBinder* pBinder)
		{
			assert( pBinder != 0 );
			tupleBind< tuple< T1 ,T2, T3, T4, T5, T6, T7, T8, T9 >, T1, 0 >( pos, obj, pBinder );
			tupleBind< tuple< T1 ,T2, T3, T4, T5, T6, T7, T8, T9 >, T2, 1 >( pos, obj, pBinder );
			tupleBind< tuple< T1 ,T2, T3, T4, T5, T6, T7, T8, T9 >, T3, 2 >( pos, obj, pBinder );
			tupleBind< tuple< T1 ,T2, T3, T4, T5, T6, T7, T8, T9 >, T4, 3 >( pos, obj, pBinder );
			tupleBind< tuple< T1 ,T2, T3, T4, T5, T6, T7, T8, T9 >, T5, 4 >( pos, obj, pBinder );
			tupleBind< tuple< T1 ,T2, T3, T4, T5, T6, T7, T8, T9 >, T6, 5 >( pos, obj, pBinder );
			tupleBind< tuple< T1 ,T2, T3, T4, T5, T6, T7, T8, T9 >, T7, 6 >( pos, obj, pBinder );
			tupleBind< tuple< T1 ,T2, T3, T4, T5, T6, T7, T8, T9 >, T8, 7 >( pos, obj, pBinder );
			tupleBind< tuple< T1 ,T2, T3, T4, T5, T6, T7, T8, T9 >, T9, 8 >( pos, obj, pBinder );
		}

		static void retrieve( std::size_t pos, tuple< T1 ,T2, T3, T4, T5, T6, T7, T8, T9 >& obj, AbstractBinder* pBinder )
		{
			assert( pBinder != 0 );
			tupleRetrieve< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9>, T1, 0 >( pos, obj, pBinder );
			tupleRetrieve< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9>, T2, 1 >( pos, obj, pBinder );
			tupleRetrieve< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9>, T3, 2 >( pos, obj, pBinder );
			tupleRetrieve< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9>, T4, 3 >( pos, obj, pBinder );
			tupleRetrieve< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9>, T5, 4 >( pos, obj, pBinder );
			tupleRetrieve< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9>, T6, 5 >( pos, obj, pBinder );
			tupleRetrieve< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9>, T7, 6 >( pos, obj, pBinder );
			tupleRetrieve< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9>, T8, 7 >( pos, obj, pBinder );
			tupleRetrieve< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9>, T9, 8 >( pos, obj, pBinder );
		}

		static void extract( std::size_t pos, AbstractExtractor* pExtractor )
		{
			assert( pExtractor != 0 );
			tupleExtract< T1, 0 >( pos, pExtractor );
			tupleExtract< T2, 1 >( pos, pExtractor );
			tupleExtract< T3, 2 >( pos, pExtractor );
			tupleExtract< T4, 3 >( pos, pExtractor );
			tupleExtract< T5, 4 >( pos, pExtractor );
			tupleExtract< T6, 5 >( pos, pExtractor );
			tupleExtract< T7, 6 >( pos, pExtractor );
			tupleExtract< T8, 7 >( pos, pExtractor );
			tupleExtract< T9, 8 >( pos, pExtractor );
		}

		static void fetch( std::size_t pos, tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9 >& obj, AbstractExtractor* pExtractor, vector< shared_ptr< OcciDataBuffer > >& vDataBuf, size_t nFetchedNum )
		{
			assert( pExtractor != 0 );
			assert( vDataBuf.size() == 9 );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf1;
			vDataBuf1.push_back( vDataBuf[ 0 ] );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf2;
			vDataBuf2.push_back( vDataBuf[ 1 ] );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf3;
			vDataBuf3.push_back( vDataBuf[ 2 ] );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf4;
			vDataBuf4.push_back( vDataBuf[ 3 ] );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf5;
			vDataBuf5.push_back( vDataBuf[ 4 ] );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf6;
			vDataBuf6.push_back( vDataBuf[ 5 ] );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf7;
			vDataBuf7.push_back( vDataBuf[ 6 ] );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf8;
			vDataBuf8.push_back( vDataBuf[ 7 ] );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf9;
			vDataBuf9.push_back( vDataBuf[ 8 ] );
			tupleFetch< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9 >, T1, 0 >( pos, obj, pExtractor, vDataBuf1, nFetchedNum );
			tupleFetch< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9 >, T2, 1 >( pos, obj, pExtractor, vDataBuf2, nFetchedNum );
			tupleFetch< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9 >, T3, 2 >( pos, obj, pExtractor, vDataBuf3, nFetchedNum );
			tupleFetch< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9 >, T4, 3 >( pos, obj, pExtractor, vDataBuf4, nFetchedNum );
			tupleFetch< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9 >, T5, 4 >( pos, obj, pExtractor, vDataBuf5, nFetchedNum );
			tupleFetch< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9 >, T6, 5 >( pos, obj, pExtractor, vDataBuf6, nFetchedNum );
			tupleFetch< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9 >, T7, 6 >( pos, obj, pExtractor, vDataBuf7, nFetchedNum );
			tupleFetch< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9 >, T8, 7 >( pos, obj, pExtractor, vDataBuf8, nFetchedNum );
			tupleFetch< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9 >, T9, 8 >( pos, obj, pExtractor, vDataBuf9, nFetchedNum );
		}

		static std::size_t size()
		{
			return TypeHandler< T1 >::size()
				+ TypeHandler< T2 >::size() 
				+ TypeHandler< T3 >::size()
				+ TypeHandler< T4 >::size() 
				+ TypeHandler< T5 >::size() 
				+ TypeHandler< T6 >::size()
				+ TypeHandler< T7 >::size()
				+ TypeHandler< T8 >::size()
				+ TypeHandler< T9 >::size();
		}

	private:
		TypeHandler();
		~TypeHandler();
		TypeHandler(const TypeHandler&);
		TypeHandler& operator = (const TypeHandler&);
	};

	// specialize tuple, tuple size = 10
	template < class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10 >
	class TypeHandler< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9, T10 > >
	{
	public:
		static void bind(std::size_t pos, const tuple< T1 ,T2, T3, T4, T5, T6, T7, T8, T9, T10 >& obj, AbstractBinder* pBinder)
		{
			assert( pBinder != 0 );
			tupleBind< tuple< T1 ,T2, T3, T4, T5, T6, T7, T8, T9, T10 >, T1, 0 >( pos, obj, pBinder );
			tupleBind< tuple< T1 ,T2, T3, T4, T5, T6, T7, T8, T9, T10 >, T2, 1 >( pos, obj, pBinder );
			tupleBind< tuple< T1 ,T2, T3, T4, T5, T6, T7, T8, T9, T10 >, T3, 2 >( pos, obj, pBinder );
			tupleBind< tuple< T1 ,T2, T3, T4, T5, T6, T7, T8, T9, T10 >, T4, 3 >( pos, obj, pBinder );
			tupleBind< tuple< T1 ,T2, T3, T4, T5, T6, T7, T8, T9, T10 >, T5, 4 >( pos, obj, pBinder );
			tupleBind< tuple< T1 ,T2, T3, T4, T5, T6, T7, T8, T9, T10 >, T6, 5 >( pos, obj, pBinder );
			tupleBind< tuple< T1 ,T2, T3, T4, T5, T6, T7, T8, T9, T10 >, T7, 6 >( pos, obj, pBinder );
			tupleBind< tuple< T1 ,T2, T3, T4, T5, T6, T7, T8, T9, T10 >, T8, 7 >( pos, obj, pBinder );
			tupleBind< tuple< T1 ,T2, T3, T4, T5, T6, T7, T8, T9, T10 >, T9, 8 >( pos, obj, pBinder );
			tupleBind< tuple< T1 ,T2, T3, T4, T5, T6, T7, T8, T9, T10 >, T10, 9 >( pos, obj, pBinder );
		}

		static void retrieve( std::size_t pos, tuple< T1 ,T2, T3, T4, T5, T6, T7, T8, T9, T10 >& obj, AbstractBinder* pBinder )
		{
			assert( pBinder != 0 );
			tupleRetrieve< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9, T10 >, T1, 0 >( pos, obj, pBinder );
			tupleRetrieve< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9, T10 >, T2, 1 >( pos, obj, pBinder );
			tupleRetrieve< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9, T10 >, T3, 2 >( pos, obj, pBinder );
			tupleRetrieve< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9, T10 >, T4, 3 >( pos, obj, pBinder );
			tupleRetrieve< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9, T10 >, T5, 4 >( pos, obj, pBinder );
			tupleRetrieve< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9, T10 >, T6, 5 >( pos, obj, pBinder );
			tupleRetrieve< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9, T10 >, T7, 6 >( pos, obj, pBinder );
			tupleRetrieve< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9, T10 >, T8, 7 >( pos, obj, pBinder );
			tupleRetrieve< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9, T10 >, T9, 8 >( pos, obj, pBinder );
			tupleRetrieve< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9, T10 >, T10, 9 >( pos, obj, pBinder );
		}

		static void extract( std::size_t pos, AbstractExtractor* pExtractor )
		{
			assert( pExtractor != 0 );
			tupleExtract< T1, 0 >( pos, pExtractor );
			tupleExtract< T2, 1 >( pos, pExtractor );
			tupleExtract< T3, 2 >( pos, pExtractor );
			tupleExtract< T4, 3 >( pos, pExtractor );
			tupleExtract< T5, 4 >( pos, pExtractor );
			tupleExtract< T6, 5 >( pos, pExtractor );
			tupleExtract< T7, 6 >( pos, pExtractor );
			tupleExtract< T8, 7 >( pos, pExtractor );
			tupleExtract< T9, 8 >( pos, pExtractor );
			tupleExtract< T10, 9 >( pos, pExtractor );
		}

		static void fetch( std::size_t pos, tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9, T10 >& obj, AbstractExtractor* pExtractor, vector< shared_ptr< OcciDataBuffer > >& vDataBuf, size_t nFetchedNum )
		{
			assert( pExtractor != 0 );
			assert( vDataBuf.size() == 10 );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf1;
			vDataBuf1.push_back( vDataBuf[ 0 ] );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf2;
			vDataBuf2.push_back( vDataBuf[ 1 ] );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf3;
			vDataBuf3.push_back( vDataBuf[ 2 ] );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf4;
			vDataBuf4.push_back( vDataBuf[ 3 ] );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf5;
			vDataBuf5.push_back( vDataBuf[ 4 ] );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf6;
			vDataBuf6.push_back( vDataBuf[ 5 ] );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf7;
			vDataBuf7.push_back( vDataBuf[ 6 ] );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf8;
			vDataBuf8.push_back( vDataBuf[ 7 ] );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf9;
			vDataBuf9.push_back( vDataBuf[ 8 ] );
			vector< shared_ptr< OcciDataBuffer > > vDataBuf10;
			vDataBuf10.push_back( vDataBuf[ 9 ] );
			tupleFetch< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9, T10 >, T1, 0 >( pos, obj, pExtractor, vDataBuf1, nFetchedNum );
			tupleFetch< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9, T10 >, T2, 1 >( pos, obj, pExtractor, vDataBuf2, nFetchedNum );
			tupleFetch< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9, T10 >, T3, 2 >( pos, obj, pExtractor, vDataBuf3, nFetchedNum );
			tupleFetch< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9, T10 >, T4, 3 >( pos, obj, pExtractor, vDataBuf4, nFetchedNum );
			tupleFetch< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9, T10 >, T5, 4 >( pos, obj, pExtractor, vDataBuf5, nFetchedNum );
			tupleFetch< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9, T10 >, T6, 5 >( pos, obj, pExtractor, vDataBuf6, nFetchedNum );
			tupleFetch< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9, T10 >, T7, 6 >( pos, obj, pExtractor, vDataBuf7, nFetchedNum );
			tupleFetch< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9, T10 >, T8, 7 >( pos, obj, pExtractor, vDataBuf8, nFetchedNum );
			tupleFetch< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9, T10 >, T9, 8 >( pos, obj, pExtractor, vDataBuf9, nFetchedNum );
			tupleFetch< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9, T10 >, T10, 9 >( pos, obj, pExtractor, vDataBuf10, nFetchedNum );
		}

		static std::size_t size()
		{
			return TypeHandler< T1 >::size()
				+ TypeHandler< T2 >::size() 
				+ TypeHandler< T3 >::size()
				+ TypeHandler< T4 >::size() 
				+ TypeHandler< T5 >::size() 
				+ TypeHandler< T6 >::size()
				+ TypeHandler< T7 >::size()
				+ TypeHandler< T8 >::size()
				+ TypeHandler< T9 >::size()
				+ TypeHandler< T10 >::size();
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

		//static void extract(std::size_t pos, const vector< T >& obj, AbstractExtractor* pExt)
		static void extract(std::size_t pos, AbstractExtractor* pExt)
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

		static void fetch( std::size_t pos, vector< T >& vecResult, AbstractExtractor* pExtractor, vector< shared_ptr< OcciDataBuffer > >& vDataBuf, size_t nFetchedNum )
		{
			assert( vDataBuf.size() == 1 );
			shared_ptr< OcciDataBuffer > pDataBuf = vDataBuf[ 0 ];
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
				if( obj[ i ].empty() )
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

		//static void extract(std::size_t pos, const vector< string >& obj, AbstractExtractor* pExt)
		static void extract(std::size_t pos, AbstractExtractor* pExt)
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

		static void fetch( std::size_t pos, vector< string >& vecResult, AbstractExtractor* pExtractor, vector< shared_ptr< OcciDataBuffer > >& vDataBuf, size_t nFetchedNum )
		{
			assert( vDataBuf.size() == 1 );
			shared_ptr< OcciDataBuffer > pDataBuf = vDataBuf[ 0 ];
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

		//static void extract(std::size_t pos, const vector< struct tm >& obj, AbstractExtractor* pExt)
		static void extract(std::size_t pos, AbstractExtractor* pExt)
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

		static void fetch( std::size_t pos, vector< struct tm >& vecResult, AbstractExtractor* pExtractor, vector< shared_ptr< OcciDataBuffer > >& vDataBuf, size_t nFetchedNum )
		{
			assert( vDataBuf.size() == 1 );
			shared_ptr< OcciDataBuffer > pDataBuf = vDataBuf[ 0 ];
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

		//static void extract( std::size_t pos, const vector< tuple< T1 > >& obj, AbstractExtractor* pExtractor )
		static void extract( std::size_t pos, AbstractExtractor* pExtractor )
		{
			assert( pExtractor != 0 );
			TypeHandler< vector< T1 > >::extract( pos, pExtractor );
		}

		static void fetch( std::size_t nPos, vector< tuple< T1 > >& vResult, AbstractExtractor* pExtractor, vector< shared_ptr< OcciDataBuffer > >& vDataBuf, size_t nFetchedNum )
		{
			assert( pExtractor != 0 );
			assert( vDataBuf.size() == 1 );
			shared_ptr< OcciDataBuffer > pDataBuf = vDataBuf[ 0 ];
			for( size_t i = 0; i < nFetchedNum; ++ i )
			{
				T1 obj = TypeConvertor< T1 >::retrieve( ( ( void* )( ( char* )pDataBuf->m_pBuffer + pDataBuf->m_nDataBufMaxPerLength * i ) ) , *( pDataBuf->m_pDataLength + i ), *( pDataBuf->m_pInd + i ) );
				vResult.push_back( make_tuple( obj ) );
			}
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

		static void extract( std::size_t pos, AbstractExtractor* pExtractor )
		{
			assert( pExtractor != 0 );
			TypeHandler< vector< T1 > >::extract( pos, pExtractor );
			TypeHandler< vector< T2 > >::extract( pos + 1, pExtractor );
		}

		static void fetch( std::size_t nPos, vector< tuple< T1, T2 > >& vResult, AbstractExtractor* pExtractor, vector< shared_ptr< OcciDataBuffer > >& vDataBuf, size_t nFetchedNum )
		{
			assert( pExtractor != 0 );
			assert( vDataBuf.size() == 2 );
			for( size_t i = 0; i < nFetchedNum; ++ i )
			{
				T1 obj1 = TypeConvertor< T1 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 0 ]->m_pBuffer + vDataBuf[ 0 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 0 ]->m_pDataLength + i ), *( vDataBuf[ 0 ]->m_pInd + i ) );
				T2 obj2 = TypeConvertor< T2 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 1 ]->m_pBuffer + vDataBuf[ 1 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 1 ]->m_pDataLength + i ), *( vDataBuf[ 1 ]->m_pInd + i ) );
				vResult.push_back( make_tuple( obj1, obj2 ) );
			}
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

		static void extract( std::size_t pos, AbstractExtractor* pExtractor )
		{
			assert( pExtractor != 0 );
			TypeHandler< vector< T1 > >::extract( pos, pExtractor );
			TypeHandler< vector< T2 > >::extract( pos + 1, pExtractor );
			TypeHandler< vector< T3 > >::extract( pos + 2, pExtractor );
		}

		static void fetch( std::size_t nPos, vector< tuple< T1, T2, T3 > >& vResult, AbstractExtractor* pExtractor, vector< shared_ptr< OcciDataBuffer > >& vDataBuf, size_t nFetchedNum )
		{
			assert( pExtractor != 0 );
			assert( vDataBuf.size() == 3 );
			for( size_t i = 0; i < nFetchedNum; ++ i )
			{
				T1 obj1 = TypeConvertor< T1 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 0 ]->m_pBuffer + vDataBuf[ 0 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 0 ]->m_pDataLength + i ), *( vDataBuf[ 0 ]->m_pInd + i ) );
				T2 obj2 = TypeConvertor< T2 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 1 ]->m_pBuffer + vDataBuf[ 1 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 1 ]->m_pDataLength + i ), *( vDataBuf[ 1 ]->m_pInd + i ) );
				T3 obj3 = TypeConvertor< T3 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 2 ]->m_pBuffer + vDataBuf[ 2 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 2 ]->m_pDataLength + i ), *( vDataBuf[ 2 ]->m_pInd + i ) );
				vResult.push_back( make_tuple( obj1, obj2, obj3 ) );
			}
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

		static void extract( std::size_t pos, AbstractExtractor* pExtractor )
		{
			assert( pExtractor != 0 );
			TypeHandler< vector< T1 > >::extract( pos, pExtractor );
			TypeHandler< vector< T2 > >::extract( pos + 1, pExtractor );
			TypeHandler< vector< T3 > >::extract( pos + 2, pExtractor );
			TypeHandler< vector< T4 > >::extract( pos + 3, pExtractor );
		}

		static void fetch( std::size_t nPos, vector< tuple< T1, T2, T3, T4 > >& vResult, AbstractExtractor* pExtractor, vector< shared_ptr< OcciDataBuffer > >& vDataBuf, size_t nFetchedNum )
		{
			assert( pExtractor != 0 );
			assert( vDataBuf.size() == 4 );
			for( size_t i = 0; i < nFetchedNum; ++ i )
			{
				T1 obj1 = TypeConvertor< T1 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 0 ]->m_pBuffer + vDataBuf[ 0 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 0 ]->m_pDataLength + i ), *( vDataBuf[ 0 ]->m_pInd + i ) );
				T2 obj2 = TypeConvertor< T2 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 1 ]->m_pBuffer + vDataBuf[ 1 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 1 ]->m_pDataLength + i ), *( vDataBuf[ 1 ]->m_pInd + i ) );
				T3 obj3 = TypeConvertor< T3 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 2 ]->m_pBuffer + vDataBuf[ 2 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 2 ]->m_pDataLength + i ), *( vDataBuf[ 2 ]->m_pInd + i ) );
				T4 obj4 = TypeConvertor< T4 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 3 ]->m_pBuffer + vDataBuf[ 3 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 3 ]->m_pDataLength + i ), *( vDataBuf[ 3 ]->m_pInd + i ) );
				vResult.push_back( make_tuple( obj1, obj2, obj3, obj4 ) );
			}
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

		static void extract( std::size_t pos, AbstractExtractor* pExtractor )
		{
			assert( pExtractor != 0 );
			TypeHandler< vector< T1 > >::extract( pos, pExtractor );
			TypeHandler< vector< T2 > >::extract( pos + 1, pExtractor );
			TypeHandler< vector< T3 > >::extract( pos + 2, pExtractor );
			TypeHandler< vector< T4 > >::extract( pos + 3, pExtractor );
			TypeHandler< vector< T5 > >::extract( pos + 4, pExtractor );
		}

		static void fetch( std::size_t nPos, vector< tuple< T1, T2, T3, T4, T5 > >& vResult, AbstractExtractor* pExtractor, vector< shared_ptr< OcciDataBuffer > >& vDataBuf, size_t nFetchedNum )
		{
			assert( pExtractor != 0 );
			assert( vDataBuf.size() == 5 );
			for( size_t i = 0; i < nFetchedNum; ++ i )
			{
				T1 obj1 = TypeConvertor< T1 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 0 ]->m_pBuffer + vDataBuf[ 0 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 0 ]->m_pDataLength + i ), *( vDataBuf[ 0 ]->m_pInd + i ) );
				T2 obj2 = TypeConvertor< T2 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 1 ]->m_pBuffer + vDataBuf[ 1 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 1 ]->m_pDataLength + i ), *( vDataBuf[ 1 ]->m_pInd + i ) );
				T3 obj3 = TypeConvertor< T3 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 2 ]->m_pBuffer + vDataBuf[ 2 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 2 ]->m_pDataLength + i ), *( vDataBuf[ 2 ]->m_pInd + i ) );
				T4 obj4 = TypeConvertor< T4 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 3 ]->m_pBuffer + vDataBuf[ 3 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 3 ]->m_pDataLength + i ), *( vDataBuf[ 3 ]->m_pInd + i ) );
				T5 obj5 = TypeConvertor< T5 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 4 ]->m_pBuffer + vDataBuf[ 4 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 4 ]->m_pDataLength + i ), *( vDataBuf[ 4 ]->m_pInd + i ) );
				vResult.push_back( make_tuple( obj1, obj2, obj3, obj4, obj5 ) );
			}
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

		static void extract( std::size_t pos, AbstractExtractor* pExtractor )
		{
			assert( pExtractor != 0 );
			TypeHandler< vector< T1 > >::extract( pos, pExtractor );
			TypeHandler< vector< T2 > >::extract( pos + 1, pExtractor );
			TypeHandler< vector< T3 > >::extract( pos + 2, pExtractor );
			TypeHandler< vector< T4 > >::extract( pos + 3, pExtractor );
			TypeHandler< vector< T5 > >::extract( pos + 4, pExtractor );
			TypeHandler< vector< T6 > >::extract( pos + 5, pExtractor );
		}

		static void fetch( std::size_t nPos, vector< tuple< T1, T2, T3, T4, T5, T6 > >& vResult, AbstractExtractor* pExtractor, vector< shared_ptr< OcciDataBuffer > >& vDataBuf, size_t nFetchedNum )
		{
			assert( pExtractor != 0 );
			assert( vDataBuf.size() == 6 );
			for( size_t i = 0; i < nFetchedNum; ++ i )
			{
				T1 obj1 = TypeConvertor< T1 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 0 ]->m_pBuffer + vDataBuf[ 0 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 0 ]->m_pDataLength + i ), *( vDataBuf[ 0 ]->m_pInd + i ) );
				T2 obj2 = TypeConvertor< T2 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 1 ]->m_pBuffer + vDataBuf[ 1 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 1 ]->m_pDataLength + i ), *( vDataBuf[ 1 ]->m_pInd + i ) );
				T3 obj3 = TypeConvertor< T3 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 2 ]->m_pBuffer + vDataBuf[ 2 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 2 ]->m_pDataLength + i ), *( vDataBuf[ 2 ]->m_pInd + i ) );
				T4 obj4 = TypeConvertor< T4 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 3 ]->m_pBuffer + vDataBuf[ 3 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 3 ]->m_pDataLength + i ), *( vDataBuf[ 3 ]->m_pInd + i ) );
				T5 obj5 = TypeConvertor< T5 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 4 ]->m_pBuffer + vDataBuf[ 4 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 4 ]->m_pDataLength + i ), *( vDataBuf[ 4 ]->m_pInd + i ) );
				T6 obj6 = TypeConvertor< T6 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 5 ]->m_pBuffer + vDataBuf[ 5 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 5 ]->m_pDataLength + i ), *( vDataBuf[ 5 ]->m_pInd + i ) );
				vResult.push_back( make_tuple( obj1, obj2, obj3, obj4, obj5, obj6 ) );
			}
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

		static void extract( std::size_t pos, AbstractExtractor* pExtractor )
		{
			assert( pExtractor != 0 );
			TypeHandler< vector< T1 > >::extract( pos, pExtractor );
			TypeHandler< vector< T2 > >::extract( pos + 1, pExtractor );
			TypeHandler< vector< T3 > >::extract( pos + 2, pExtractor );
			TypeHandler< vector< T4 > >::extract( pos + 3, pExtractor );
			TypeHandler< vector< T5 > >::extract( pos + 4, pExtractor );
			TypeHandler< vector< T6 > >::extract( pos + 5, pExtractor );
			TypeHandler< vector< T7 > >::extract( pos + 6, pExtractor );
		}

		static void fetch( std::size_t nPos, vector< tuple< T1, T2, T3, T4, T5, T6, T7 > >& vResult, AbstractExtractor* pExtractor, vector< shared_ptr< OcciDataBuffer > >& vDataBuf, size_t nFetchedNum )
		{
			assert( pExtractor != 0 );
			assert( vDataBuf.size() == 7 );
			for( size_t i = 0; i < nFetchedNum; ++ i )
			{
				T1 obj1 = TypeConvertor< T1 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 0 ]->m_pBuffer + vDataBuf[ 0 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 0 ]->m_pDataLength + i ), *( vDataBuf[ 0 ]->m_pInd + i ) );
				T2 obj2 = TypeConvertor< T2 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 1 ]->m_pBuffer + vDataBuf[ 1 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 1 ]->m_pDataLength + i ), *( vDataBuf[ 1 ]->m_pInd + i ) );
				T3 obj3 = TypeConvertor< T3 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 2 ]->m_pBuffer + vDataBuf[ 2 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 2 ]->m_pDataLength + i ), *( vDataBuf[ 2 ]->m_pInd + i ) );
				T4 obj4 = TypeConvertor< T4 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 3 ]->m_pBuffer + vDataBuf[ 3 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 3 ]->m_pDataLength + i ), *( vDataBuf[ 3 ]->m_pInd + i ) );
				T5 obj5 = TypeConvertor< T5 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 4 ]->m_pBuffer + vDataBuf[ 4 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 4 ]->m_pDataLength + i ), *( vDataBuf[ 4 ]->m_pInd + i ) );
				T6 obj6 = TypeConvertor< T6 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 5 ]->m_pBuffer + vDataBuf[ 5 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 5 ]->m_pDataLength + i ), *( vDataBuf[ 5 ]->m_pInd + i ) );
				T7 obj7 = TypeConvertor< T7 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 6 ]->m_pBuffer + vDataBuf[ 6 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 6 ]->m_pDataLength + i ), *( vDataBuf[ 6 ]->m_pInd + i ) );
				vResult.push_back( make_tuple( obj1, obj2, obj3, obj4, obj5, obj6, obj7 ) );
			}
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

		static void extract( std::size_t pos, AbstractExtractor* pExtractor )
		{
			assert( pExtractor != 0 );
			TypeHandler< vector< T1 > >::extract( pos, pExtractor );
			TypeHandler< vector< T2 > >::extract( pos + 1, pExtractor );
			TypeHandler< vector< T3 > >::extract( pos + 2, pExtractor );
			TypeHandler< vector< T4 > >::extract( pos + 3, pExtractor );
			TypeHandler< vector< T5 > >::extract( pos + 4, pExtractor );
			TypeHandler< vector< T6 > >::extract( pos + 5, pExtractor );
			TypeHandler< vector< T7 > >::extract( pos + 6, pExtractor );
			TypeHandler< vector< T8 > >::extract( pos + 7, pExtractor );
		}

		static void fetch( std::size_t nPos, vector< tuple< T1, T2, T3, T4, T5, T6, T7, T8 > >& vResult, AbstractExtractor* pExtractor, vector< shared_ptr< OcciDataBuffer > >& vDataBuf, size_t nFetchedNum )
		{
			assert( pExtractor != 0 );
			assert( vDataBuf.size() == 8 );
			for( size_t i = 0; i < nFetchedNum; ++ i )
			{
				T1 obj1 = TypeConvertor< T1 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 0 ]->m_pBuffer + vDataBuf[ 0 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 0 ]->m_pDataLength + i ), *( vDataBuf[ 0 ]->m_pInd + i ) );
				T2 obj2 = TypeConvertor< T2 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 1 ]->m_pBuffer + vDataBuf[ 1 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 1 ]->m_pDataLength + i ), *( vDataBuf[ 1 ]->m_pInd + i ) );
				T3 obj3 = TypeConvertor< T3 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 2 ]->m_pBuffer + vDataBuf[ 2 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 2 ]->m_pDataLength + i ), *( vDataBuf[ 2 ]->m_pInd + i ) );
				T4 obj4 = TypeConvertor< T4 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 3 ]->m_pBuffer + vDataBuf[ 3 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 3 ]->m_pDataLength + i ), *( vDataBuf[ 3 ]->m_pInd + i ) );
				T5 obj5 = TypeConvertor< T5 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 4 ]->m_pBuffer + vDataBuf[ 4 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 4 ]->m_pDataLength + i ), *( vDataBuf[ 4 ]->m_pInd + i ) );
				T6 obj6 = TypeConvertor< T6 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 5 ]->m_pBuffer + vDataBuf[ 5 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 5 ]->m_pDataLength + i ), *( vDataBuf[ 5 ]->m_pInd + i ) );
				T7 obj7 = TypeConvertor< T7 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 6 ]->m_pBuffer + vDataBuf[ 6 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 6 ]->m_pDataLength + i ), *( vDataBuf[ 6 ]->m_pInd + i ) );
				T8 obj8 = TypeConvertor< T8 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 7 ]->m_pBuffer + vDataBuf[ 7 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 7 ]->m_pDataLength + i ), *( vDataBuf[ 7 ]->m_pInd + i ) );
				vResult.push_back( make_tuple( obj1, obj2, obj3, obj4, obj5, obj6, obj7, obj8 ) );
			}
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

		static void extract( std::size_t pos, AbstractExtractor* pExtractor )
		{
			assert( pExtractor != 0 );
			TypeHandler< vector< T1 > >::extract( pos, pExtractor );
			TypeHandler< vector< T2 > >::extract( pos + 1, pExtractor );
			TypeHandler< vector< T3 > >::extract( pos + 2, pExtractor );
			TypeHandler< vector< T4 > >::extract( pos + 3, pExtractor );
			TypeHandler< vector< T5 > >::extract( pos + 4, pExtractor );
			TypeHandler< vector< T6 > >::extract( pos + 5, pExtractor );
			TypeHandler< vector< T7 > >::extract( pos + 6, pExtractor );
			TypeHandler< vector< T8 > >::extract( pos + 7, pExtractor );
			TypeHandler< vector< T9 > >::extract( pos + 8, pExtractor );
		}

		static void fetch( std::size_t nPos, vector< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9 > >& vResult, AbstractExtractor* pExtractor, vector< shared_ptr< OcciDataBuffer > >& vDataBuf, size_t nFetchedNum )
		{
			assert( pExtractor != 0 );
			assert( vDataBuf.size() == 9 );
			for( size_t i = 0; i < nFetchedNum; ++ i )
			{
				T1 obj1 = TypeConvertor< T1 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 0 ]->m_pBuffer + vDataBuf[ 0 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 0 ]->m_pDataLength + i ), *( vDataBuf[ 0 ]->m_pInd + i ) );
				T2 obj2 = TypeConvertor< T2 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 1 ]->m_pBuffer + vDataBuf[ 1 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 1 ]->m_pDataLength + i ), *( vDataBuf[ 1 ]->m_pInd + i ) );
				T3 obj3 = TypeConvertor< T3 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 2 ]->m_pBuffer + vDataBuf[ 2 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 2 ]->m_pDataLength + i ), *( vDataBuf[ 2 ]->m_pInd + i ) );
				T4 obj4 = TypeConvertor< T4 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 3 ]->m_pBuffer + vDataBuf[ 3 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 3 ]->m_pDataLength + i ), *( vDataBuf[ 3 ]->m_pInd + i ) );
				T5 obj5 = TypeConvertor< T5 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 4 ]->m_pBuffer + vDataBuf[ 4 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 4 ]->m_pDataLength + i ), *( vDataBuf[ 4 ]->m_pInd + i ) );
				T6 obj6 = TypeConvertor< T6 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 5 ]->m_pBuffer + vDataBuf[ 5 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 5 ]->m_pDataLength + i ), *( vDataBuf[ 5 ]->m_pInd + i ) );
				T7 obj7 = TypeConvertor< T7 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 6 ]->m_pBuffer + vDataBuf[ 6 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 6 ]->m_pDataLength + i ), *( vDataBuf[ 6 ]->m_pInd + i ) );
				T8 obj8 = TypeConvertor< T8 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 7 ]->m_pBuffer + vDataBuf[ 7 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 7 ]->m_pDataLength + i ), *( vDataBuf[ 7 ]->m_pInd + i ) );
				T9 obj9 = TypeConvertor< T8 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 8 ]->m_pBuffer + vDataBuf[ 8 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 8 ]->m_pDataLength + i ), *( vDataBuf[ 8 ]->m_pInd + i ) );
				vResult.push_back( make_tuple( obj1, obj2, obj3, obj4, obj5, obj6, obj7, obj8, obj9 ) );
			}
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

		static void extract( std::size_t pos, AbstractExtractor* pExtractor )
		{
			assert( pExtractor != 0 );
			TypeHandler< vector< T1 > >::extract( pos, pExtractor );
			TypeHandler< vector< T2 > >::extract( pos + 1, pExtractor );
			TypeHandler< vector< T3 > >::extract( pos + 2, pExtractor );
			TypeHandler< vector< T4 > >::extract( pos + 3, pExtractor );
			TypeHandler< vector< T5 > >::extract( pos + 4, pExtractor );
			TypeHandler< vector< T6 > >::extract( pos + 5, pExtractor );
			TypeHandler< vector< T7 > >::extract( pos + 6, pExtractor );
			TypeHandler< vector< T8 > >::extract( pos + 7, pExtractor );
			TypeHandler< vector< T9 > >::extract( pos + 8, pExtractor );
			TypeHandler< vector< T10 > >::extract( pos + 9, pExtractor );
		}

		static void fetch( std::size_t nPos, vector< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9, T10 > >& vResult, AbstractExtractor* pExtractor, vector< shared_ptr< OcciDataBuffer > >& vDataBuf, size_t nFetchedNum )
		{
			assert( pExtractor != 0 );
			assert( vDataBuf.size() == 10 );
			for( size_t i = 0; i < nFetchedNum; ++ i )
			{
				T1 obj1 = TypeConvertor< T1 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 0 ]->m_pBuffer + vDataBuf[ 0 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 0 ]->m_pDataLength + i ), *( vDataBuf[ 0 ]->m_pInd + i ) );
				T2 obj2 = TypeConvertor< T2 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 1 ]->m_pBuffer + vDataBuf[ 1 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 1 ]->m_pDataLength + i ), *( vDataBuf[ 1 ]->m_pInd + i ) );
				T3 obj3 = TypeConvertor< T3 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 2 ]->m_pBuffer + vDataBuf[ 2 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 2 ]->m_pDataLength + i ), *( vDataBuf[ 2 ]->m_pInd + i ) );
				T4 obj4 = TypeConvertor< T4 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 3 ]->m_pBuffer + vDataBuf[ 3 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 3 ]->m_pDataLength + i ), *( vDataBuf[ 3 ]->m_pInd + i ) );
				T5 obj5 = TypeConvertor< T5 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 4 ]->m_pBuffer + vDataBuf[ 4 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 4 ]->m_pDataLength + i ), *( vDataBuf[ 4 ]->m_pInd + i ) );
				T6 obj6 = TypeConvertor< T6 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 5 ]->m_pBuffer + vDataBuf[ 5 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 5 ]->m_pDataLength + i ), *( vDataBuf[ 5 ]->m_pInd + i ) );
				T7 obj7 = TypeConvertor< T7 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 6 ]->m_pBuffer + vDataBuf[ 6 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 6 ]->m_pDataLength + i ), *( vDataBuf[ 6 ]->m_pInd + i ) );
				T8 obj8 = TypeConvertor< T8 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 7 ]->m_pBuffer + vDataBuf[ 7 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 7 ]->m_pDataLength + i ), *( vDataBuf[ 7 ]->m_pInd + i ) );
				T9 obj9 = TypeConvertor< T8 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 8 ]->m_pBuffer + vDataBuf[ 8 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 8 ]->m_pDataLength + i ), *( vDataBuf[ 8 ]->m_pInd + i ) );
				T9 obj10 = TypeConvertor< T8 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 9 ]->m_pBuffer + vDataBuf[ 9 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 9 ]->m_pDataLength + i ), *( vDataBuf[ 9 ]->m_pInd + i ) );
				vResult.push_back( make_tuple( obj1, obj2, obj3, obj4, obj5, obj6, obj7, obj8, obj9, obj10 ) );
			}
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

	// specialize list for batched bind
	template < class T >
	class TypeHandler< list< T > >
	{
	public:
		static void bind(std::size_t pos, const list< T >& obj, AbstractBinder* pBinder)
		{
			assert( pBinder != 0 );
			size_t nListSize = obj.size();
			const size_t max_size = (numeric_limits< size_t >::max)() / sizeof( int );
			if( nListSize > max_size )
				throw BindException( "bind list<int> exceeding max row number" );
			size_t buf_length = sizeof(T) * nListSize;
			// set buffer
			T* p = ( T* )malloc( buf_length );
			size_t nIndex = 0;
			for( typename list< T >::const_iterator it = obj.begin(); it != obj.end(); ++ it, ++ nIndex )
			{
				*( p + nIndex ) = *it;
			}
			// set length array
			UInt16* p_length = ( UInt16* )malloc( sizeof( UInt16 ) *  nListSize );
			for( size_t i = 0; i < nListSize; i ++ )
			{
				*(p_length + i ) = sizeof( T );
			}
			// set indicator
			Int16* p_Ind = ( Int16* ) malloc( sizeof( Int16 ) * nListSize );
			for( size_t i = 0; i < nListSize; i ++ )
			{
				*( p_Ind + i ) = 0;
			}
			pBinder->BatchedBind( pos, p, sizeof(T), p_length, p_Ind, TypeConvertor< T >::Convert() );
		}

		static std::size_t size()
		{
			return TypeHandler< T >::size();
		}

		//static void extract(std::size_t pos, const list< T >& obj, AbstractExtractor* pExt)
		static void extract(std::size_t pos, AbstractExtractor* pExt)
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

		static void fetch( std::size_t pos, list< T >& vResult, AbstractExtractor* pExtractor, vector< shared_ptr< OcciDataBuffer > >& vDataBuf, size_t nFetchedNum )
		{
			assert( vDataBuf.size() == 1 );
			shared_ptr< OcciDataBuffer > pDataBuf = vDataBuf[ 0 ];
			for( size_t i = 0; i < nFetchedNum; ++ i )
			{
				T obj = TypeConvertor< T >::retrieve( ( ( void* )( ( char* )pDataBuf->m_pBuffer + pDataBuf->m_nDataBufMaxPerLength * i ) ) , *( pDataBuf->m_pDataLength + i ), *( pDataBuf->m_pInd + i ) );
				vResult.push_back( obj );
			}
		}

	private:
		TypeHandler();
		~TypeHandler();
		TypeHandler(const TypeHandler&);
		TypeHandler& operator = (const TypeHandler&);
	};

	// specialize list for batched bind
	template <>
	class TypeHandler< list< string > >
	{
	public:
		static void bind(std::size_t pos, const list< string >& obj, AbstractBinder* pBinder)
		{
			assert( pBinder != 0 );
			size_t nListSize = obj.size();
			size_t char_buf_max = occiwrapper::GetListMaxStringLength( obj ) + 1;
			const size_t max_size = ( numeric_limits< size_t >::max )() / sizeof( char_buf_max );
			if( nListSize > max_size )
				throw BindException( "bind list<string> exceeding max row number" );
			size_t buf_length =  char_buf_max * nListSize;
			// set buffer
			char* p = ( char* )malloc( buf_length );
			int nIndex = 0;
			for( list< string >::const_iterator it = obj.begin(); it != obj.end(); ++ it, ++ nIndex )
			{
				strcpy( p + nIndex * char_buf_max, it->c_str() );
			}
			// set length array
			UInt16* p_length = ( UInt16* )malloc( sizeof( UInt16 ) *  nListSize );
			// set indicator
			Int16* p_Ind = ( Int16* )malloc( sizeof( Int16 ) * nListSize );
			nIndex = 0;
			for( list< string >::const_iterator it = obj.begin(); it != obj.end(); ++ it, ++ nIndex )
			{
				if( it->empty() )
				{
					*( p_Ind + nIndex ) = -1;
				}
				else
				{
					*( p_Ind + nIndex ) = 0;
				}

				*(p_length + nIndex ) = it->size() + 1;
			}
			pBinder->BatchedBind( pos, p, char_buf_max, p_length, p_Ind, TypeConvertor< string >::Convert() );
		}

		static std::size_t size()
		{
			return TypeHandler< string >::size();
		}

		//static void extract(std::size_t pos, const list< string >& obj, AbstractExtractor* pExt)
		static void extract(std::size_t pos, AbstractExtractor* pExt)
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

		static void fetch( std::size_t pos, list< string >& vResult, AbstractExtractor* pExtractor, vector< shared_ptr< OcciDataBuffer > >& vDataBuf, size_t nFetchedNum )
		{
			assert( vDataBuf.size() == 1 );
			shared_ptr< OcciDataBuffer > pDataBuf = vDataBuf[ 0 ];
			for( size_t i = 0; i < nFetchedNum; ++ i )
			{
				string obj = TypeConvertor< string >::retrieve( ( ( void* )( ( char* )pDataBuf->m_pBuffer + pDataBuf->m_nDataBufMaxPerLength * i ) ) , *( pDataBuf->m_pDataLength + i ), *( pDataBuf->m_pInd + i ) );
				vResult.push_back( obj );
			}
		}

	private:
		TypeHandler();
		~TypeHandler();
		TypeHandler(const TypeHandler&);
		TypeHandler& operator = (const TypeHandler&);
	};

	// specialize list for batched bind
	template <>
	class TypeHandler< list< struct tm > >
	{
	public:
		static void bind(std::size_t pos, const list< struct tm >& obj, AbstractBinder* pBinder)
		{
			assert( pBinder != 0 );
			size_t nListSize = obj.size();
			size_t char_buf_max = sizeof( oracle::occi::Date );
			const size_t max_size = (numeric_limits< size_t >::max)() / char_buf_max;
			if( nListSize > max_size )
				throw BindException( "bind list<struct tm> exceeding max row number" );
			size_t buf_length =  char_buf_max * nListSize;
			// set buffer
			oracle::occi::Date* p = ( oracle::occi::Date* )malloc( buf_length );
			int nIndex = 0;
			for( list< struct tm >::const_iterator it = obj.begin(); it != obj.end(); ++ it , ++ nIndex )
			{
				* ( p + nIndex ) = occiwrapper::ToDate( *it, pBinder->GetEnv() );
			}
			// set length array
			UInt16* p_length = ( UInt16* )malloc( sizeof( UInt16 ) *  nListSize );
			// set indicator
			Int16* p_Ind = ( Int16* )malloc( sizeof( Int16 ) * nListSize );
			for( size_t i = 0; i < nListSize; ++ i )
			{
				*( p_length + i ) = char_buf_max;
				*( p_Ind + i ) = 0;
			}
			pBinder->BatchedBind( pos, p, char_buf_max, p_length, p_Ind, TypeConvertor< struct tm >::Convert() );
		}

		static std::size_t size()
		{
			return TypeHandler< struct tm >::size();
		}

		//static void extract(std::size_t pos, const list< struct tm >& obj, AbstractExtractor* pExt)
		static void extract(std::size_t pos, AbstractExtractor* pExt)
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

		static void fetch( std::size_t pos, list< struct tm >& vResult, AbstractExtractor* pExtractor, vector< shared_ptr< OcciDataBuffer > >& vDataBuf, size_t nFetchedNum )
		{
			assert( vDataBuf.size() == 1 );
			shared_ptr< OcciDataBuffer > pDataBuf = vDataBuf[ 0 ];
			for( size_t i = 0; i < nFetchedNum; ++ i )
			{
				struct tm obj = TypeConvertor< struct tm >::retrieve( ( ( void* )( ( char* )pDataBuf->m_pBuffer + pDataBuf->m_nDataBufMaxPerLength * i ) ) , *( pDataBuf->m_pDataLength + i ), *( pDataBuf->m_pInd + i ) );
				vResult.push_back( obj );
			}
		}

	private:
		TypeHandler();
		~TypeHandler();
		TypeHandler(const TypeHandler&);
		TypeHandler& operator = (const TypeHandler&);
	};

	// specialize list for batched bind
	template < class T1 >
	class TypeHandler< list< tuple< T1 > > >
	{
	public:
		static void bind(std::size_t pos, const list< tuple< T1 > >& obj, AbstractBinder* pBinder)
		{
			assert( pBinder != 0 );
			list< T1 > copy_obj;
			for( typename list< tuple< T1 > >::const_iterator it = obj.begin(); it != obj.end(); ++ it )
				copy_obj.push_back( get< 0 >( *it ) );
			TypeHandler< list< T1 > >::bind( pos, copy_obj, pBinder );
		}

		//static void extract( std::size_t pos, const list< tuple< T1 > >& obj, AbstractExtractor* pExtractor )
		static void extract( std::size_t pos, AbstractExtractor* pExtractor )
		{
			assert( pExtractor != 0 );
			TypeHandler< list< T1 > >::extract( pos, pExtractor );
		}

		static void fetch( std::size_t nPos, list< tuple< T1 > >& vResult, AbstractExtractor* pExtractor, vector< shared_ptr< OcciDataBuffer > >& vDataBuf, size_t nFetchedNum )
		{
			assert( pExtractor != 0 );
			assert( vDataBuf.size() == 1 );
			shared_ptr< OcciDataBuffer > pDataBuf = vDataBuf[ 0 ];
			for( size_t i = 0; i < nFetchedNum; ++ i )
			{
				T1 obj = TypeConvertor< T1 >::retrieve( ( ( void* )( ( char* )pDataBuf->m_pBuffer + pDataBuf->m_nDataBufMaxPerLength * i ) ) , *( pDataBuf->m_pDataLength + i ), *( pDataBuf->m_pInd + i ) );
				vResult.push_back( make_tuple( obj ) );
			}
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

	// specialize list for batched bind
	template < class T1, class T2 >
	class TypeHandler< list< tuple< T1, T2 > > >
	{
	public:
		static void bind(std::size_t pos, const list< tuple< T1, T2 > >& obj, AbstractBinder* pBinder)
		{
			assert( pBinder != 0 );
			list< T1 > copy_obj1;
			list< T2 > copy_obj2;
			for( typename list< tuple< T1, T2 > >::const_iterator it = obj.begin(); it != obj.end(); ++ it )
			{
				copy_obj1.push_back( get< 0 >( *it ) );
				copy_obj2.push_back( get< 1 >( *it ) );
			}
			TypeHandler< list< T1 > >::bind( pos, copy_obj1, pBinder );
			TypeHandler< list< T2 > >::bind( pos + 1, copy_obj2, pBinder );
		}

		static void extract( std::size_t pos, AbstractExtractor* pExtractor )
		{
			assert( pExtractor != 0 );
			TypeHandler< list< T1 > >::extract( pos, pExtractor );
			TypeHandler< list< T2 > >::extract( pos + 1, pExtractor );
		}

		static void fetch( std::size_t nPos, list< tuple< T1, T2 > >& vResult, AbstractExtractor* pExtractor, vector< shared_ptr< OcciDataBuffer > >& vDataBuf, size_t nFetchedNum )
		{
			assert( pExtractor != 0 );
			assert( vDataBuf.size() == 2 );
			for( size_t i = 0; i < nFetchedNum; ++ i )
			{
				T1 obj1 = TypeConvertor< T1 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 0 ]->m_pBuffer + vDataBuf[ 0 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 0 ]->m_pDataLength + i ), *( vDataBuf[ 0 ]->m_pInd + i ) );
				T2 obj2 = TypeConvertor< T2 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 1 ]->m_pBuffer + vDataBuf[ 1 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 1 ]->m_pDataLength + i ), *( vDataBuf[ 1 ]->m_pInd + i ) );
				vResult.push_back( make_tuple( obj1, obj2 ) );
			}
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

	// specialize list for batched bind
	template < class T1, class T2, class T3 >
	class TypeHandler< list< tuple< T1, T2, T3 > > >
	{
	public:
		static void bind(std::size_t pos, const list< tuple< T1, T2, T3 > >& obj, AbstractBinder* pBinder)
		{
			assert( pBinder != 0 );
			list< T1 > copy_obj1;
			list< T2 > copy_obj2;
			list< T3 > copy_obj3;
			for( typename list< tuple< T1, T2, T3 > >::const_iterator it = obj.begin(); it != obj.end(); ++ it )
			{
				copy_obj1.push_back( get< 0 >( *it ) );
				copy_obj2.push_back( get< 1 >( *it ) );
				copy_obj3.push_back( get< 2 >( *it ) );
			}
			TypeHandler< list< T1 > >::bind( pos, copy_obj1, pBinder );
			TypeHandler< list< T2 > >::bind( pos + 1, copy_obj2, pBinder );
			TypeHandler< list< T3 > >::bind( pos + 2, copy_obj3, pBinder );
		}

		static void extract( std::size_t pos, AbstractExtractor* pExtractor )
		{
			assert( pExtractor != 0 );
			TypeHandler< list< T1 > >::extract( pos, pExtractor );
			TypeHandler< list< T2 > >::extract( pos + 1, pExtractor );
			TypeHandler< list< T3 > >::extract( pos + 2, pExtractor );
		}

		static void fetch( std::size_t nPos, list< tuple< T1, T2, T3 > >& vResult, AbstractExtractor* pExtractor, vector< shared_ptr< OcciDataBuffer > >& vDataBuf, size_t nFetchedNum )
		{
			assert( pExtractor != 0 );
			assert( vDataBuf.size() == 3 );
			for( size_t i = 0; i < nFetchedNum; ++ i )
			{
				T1 obj1 = TypeConvertor< T1 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 0 ]->m_pBuffer + vDataBuf[ 0 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 0 ]->m_pDataLength + i ), *( vDataBuf[ 0 ]->m_pInd + i ) );
				T2 obj2 = TypeConvertor< T2 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 1 ]->m_pBuffer + vDataBuf[ 1 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 1 ]->m_pDataLength + i ), *( vDataBuf[ 1 ]->m_pInd + i ) );
				T3 obj3 = TypeConvertor< T3 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 2 ]->m_pBuffer + vDataBuf[ 2 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 2 ]->m_pDataLength + i ), *( vDataBuf[ 2 ]->m_pInd + i ) );
				vResult.push_back( make_tuple( obj1, obj2, obj3 ) );
			}
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

	// specialize list for batched bind
	template < class T1, class T2, class T3, class T4 >
	class TypeHandler< list< tuple< T1, T2, T3, T4 > > >
	{
	public:
		static void bind(std::size_t pos, const list< tuple< T1, T2, T3, T4 > >& obj, AbstractBinder* pBinder)
		{
			assert( pBinder != 0 );
			list< T1 > copy_obj1;
			list< T2 > copy_obj2;
			list< T3 > copy_obj3;
			list< T4 > copy_obj4;
			for( typename list< tuple< T1, T2, T3, T4 > >::const_iterator it = obj.begin(); it != obj.end(); ++ it )
			{
				copy_obj1.push_back( get< 0 >( *it ) );
				copy_obj2.push_back( get< 1 >( *it ) );
				copy_obj3.push_back( get< 2 >( *it ) );
				copy_obj4.push_back( get< 3 >( *it ) );
			}
			TypeHandler< list< T1 > >::bind( pos, copy_obj1, pBinder );
			TypeHandler< list< T2 > >::bind( pos + 1, copy_obj2, pBinder );
			TypeHandler< list< T3 > >::bind( pos + 2, copy_obj3, pBinder );
			TypeHandler< list< T4 > >::bind( pos + 3, copy_obj4, pBinder );
		}

		static void extract( std::size_t pos, AbstractExtractor* pExtractor )
		{
			assert( pExtractor != 0 );
			TypeHandler< list< T1 > >::extract( pos, pExtractor );
			TypeHandler< list< T2 > >::extract( pos + 1, pExtractor );
			TypeHandler< list< T3 > >::extract( pos + 2, pExtractor );
			TypeHandler< list< T4 > >::extract( pos + 3, pExtractor );
		}

		static void fetch( std::size_t nPos, list< tuple< T1, T2, T3, T4 > >& vResult, AbstractExtractor* pExtractor, vector< shared_ptr< OcciDataBuffer > >& vDataBuf, size_t nFetchedNum )
		{
			assert( pExtractor != 0 );
			assert( vDataBuf.size() == 4 );
			for( size_t i = 0; i < nFetchedNum; ++ i )
			{
				T1 obj1 = TypeConvertor< T1 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 0 ]->m_pBuffer + vDataBuf[ 0 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 0 ]->m_pDataLength + i ), *( vDataBuf[ 0 ]->m_pInd + i ) );
				T2 obj2 = TypeConvertor< T2 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 1 ]->m_pBuffer + vDataBuf[ 1 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 1 ]->m_pDataLength + i ), *( vDataBuf[ 1 ]->m_pInd + i ) );
				T3 obj3 = TypeConvertor< T3 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 2 ]->m_pBuffer + vDataBuf[ 2 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 2 ]->m_pDataLength + i ), *( vDataBuf[ 2 ]->m_pInd + i ) );
				T4 obj4 = TypeConvertor< T4 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 3 ]->m_pBuffer + vDataBuf[ 3 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 3 ]->m_pDataLength + i ), *( vDataBuf[ 3 ]->m_pInd + i ) );
				vResult.push_back( make_tuple( obj1, obj2, obj3, obj4 ) );
			}
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

	// specialize list for batched bind
	template < class T1, class T2, class T3, class T4, class T5 >
	class TypeHandler< list< tuple< T1, T2, T3, T4, T5 > > >
	{
	public:
		static void bind(std::size_t pos, const list< tuple< T1, T2, T3, T4, T5 > >& obj, AbstractBinder* pBinder)
		{
			assert( pBinder != 0 );
			list< T1 > copy_obj1;
			list< T2 > copy_obj2;
			list< T3 > copy_obj3;
			list< T4 > copy_obj4;
			list< T5 > copy_obj5;
			for( typename list< tuple< T1, T2, T3, T4, T5 > >::const_iterator it = obj.begin(); it != obj.end(); ++ it )
			{
				copy_obj1.push_back( get< 0 >( *it ) );
				copy_obj2.push_back( get< 1 >( *it ) );
				copy_obj3.push_back( get< 2 >( *it ) );
				copy_obj4.push_back( get< 3 >( *it ) );
				copy_obj5.push_back( get< 4 >( *it ) );
			}
			TypeHandler< list< T1 > >::bind( pos, copy_obj1, pBinder );
			TypeHandler< list< T2 > >::bind( pos + 1, copy_obj2, pBinder );
			TypeHandler< list< T3 > >::bind( pos + 2, copy_obj3, pBinder );
			TypeHandler< list< T4 > >::bind( pos + 3, copy_obj4, pBinder );
			TypeHandler< list< T5 > >::bind( pos + 4, copy_obj5, pBinder );
		}

		static void extract( std::size_t pos, AbstractExtractor* pExtractor )
		{
			assert( pExtractor != 0 );
			TypeHandler< list< T1 > >::extract( pos, pExtractor );
			TypeHandler< list< T2 > >::extract( pos + 1, pExtractor );
			TypeHandler< list< T3 > >::extract( pos + 2, pExtractor );
			TypeHandler< list< T4 > >::extract( pos + 3, pExtractor );
			TypeHandler< list< T5 > >::extract( pos + 4, pExtractor );
		}

		static void fetch( std::size_t nPos, list< tuple< T1, T2, T3, T4, T5 > >& vResult, AbstractExtractor* pExtractor, vector< shared_ptr< OcciDataBuffer > >& vDataBuf, size_t nFetchedNum )
		{
			assert( pExtractor != 0 );
			assert( vDataBuf.size() == 5 );
			for( size_t i = 0; i < nFetchedNum; ++ i )
			{
				T1 obj1 = TypeConvertor< T1 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 0 ]->m_pBuffer + vDataBuf[ 0 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 0 ]->m_pDataLength + i ), *( vDataBuf[ 0 ]->m_pInd + i ) );
				T2 obj2 = TypeConvertor< T2 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 1 ]->m_pBuffer + vDataBuf[ 1 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 1 ]->m_pDataLength + i ), *( vDataBuf[ 1 ]->m_pInd + i ) );
				T3 obj3 = TypeConvertor< T3 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 2 ]->m_pBuffer + vDataBuf[ 2 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 2 ]->m_pDataLength + i ), *( vDataBuf[ 2 ]->m_pInd + i ) );
				T4 obj4 = TypeConvertor< T4 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 3 ]->m_pBuffer + vDataBuf[ 3 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 3 ]->m_pDataLength + i ), *( vDataBuf[ 3 ]->m_pInd + i ) );
				T5 obj5 = TypeConvertor< T5 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 4 ]->m_pBuffer + vDataBuf[ 4 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 4 ]->m_pDataLength + i ), *( vDataBuf[ 4 ]->m_pInd + i ) );
				vResult.push_back( make_tuple( obj1, obj2, obj3, obj4, obj5 ) );
			}
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

	// specialize list for batched bind
	template < class T1, class T2, class T3, class T4, class T5, class T6 >
	class TypeHandler< list< tuple< T1, T2, T3, T4, T5, T6 > > >
	{
	public:
		static void bind(std::size_t pos, const list< tuple< T1, T2, T3, T4, T5, T6 > >& obj, AbstractBinder* pBinder)
		{
			assert( pBinder != 0 );
			list< T1 > copy_obj1;
			list< T2 > copy_obj2;
			list< T3 > copy_obj3;
			list< T4 > copy_obj4;
			list< T5 > copy_obj5;
			list< T6 > copy_obj6;
			for( typename list< tuple< T1, T2, T3, T4, T5, T6 > >::const_iterator it = obj.begin(); it != obj.end(); ++ it )
			{
				copy_obj1.push_back( get< 0 >( *it ) );
				copy_obj2.push_back( get< 1 >( *it ) );
				copy_obj3.push_back( get< 2 >( *it ) );
				copy_obj4.push_back( get< 3 >( *it ) );
				copy_obj5.push_back( get< 4 >( *it ) );
				copy_obj6.push_back( get< 5 >( *it ) );
			}
			TypeHandler< list< T1 > >::bind( pos, copy_obj1, pBinder );
			TypeHandler< list< T2 > >::bind( pos + 1, copy_obj2, pBinder );
			TypeHandler< list< T3 > >::bind( pos + 2, copy_obj3, pBinder );
			TypeHandler< list< T4 > >::bind( pos + 3, copy_obj4, pBinder );
			TypeHandler< list< T5 > >::bind( pos + 4, copy_obj5, pBinder );
			TypeHandler< list< T6 > >::bind( pos + 5, copy_obj6, pBinder );
		}

		static void extract( std::size_t pos, AbstractExtractor* pExtractor )
		{
			assert( pExtractor != 0 );
			TypeHandler< list< T1 > >::extract( pos, pExtractor );
			TypeHandler< list< T2 > >::extract( pos + 1, pExtractor );
			TypeHandler< list< T3 > >::extract( pos + 2, pExtractor );
			TypeHandler< list< T4 > >::extract( pos + 3, pExtractor );
			TypeHandler< list< T5 > >::extract( pos + 4, pExtractor );
			TypeHandler< list< T6 > >::extract( pos + 5, pExtractor );
		}

		static void fetch( std::size_t nPos, list< tuple< T1, T2, T3, T4, T5, T6 > >& vResult, AbstractExtractor* pExtractor, vector< shared_ptr< OcciDataBuffer > >& vDataBuf, size_t nFetchedNum )
		{
			assert( pExtractor != 0 );
			assert( vDataBuf.size() == 6 );
			for( size_t i = 0; i < nFetchedNum; ++ i )
			{
				T1 obj1 = TypeConvertor< T1 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 0 ]->m_pBuffer + vDataBuf[ 0 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 0 ]->m_pDataLength + i ), *( vDataBuf[ 0 ]->m_pInd + i ) );
				T2 obj2 = TypeConvertor< T2 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 1 ]->m_pBuffer + vDataBuf[ 1 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 1 ]->m_pDataLength + i ), *( vDataBuf[ 1 ]->m_pInd + i ) );
				T3 obj3 = TypeConvertor< T3 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 2 ]->m_pBuffer + vDataBuf[ 2 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 2 ]->m_pDataLength + i ), *( vDataBuf[ 2 ]->m_pInd + i ) );
				T4 obj4 = TypeConvertor< T4 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 3 ]->m_pBuffer + vDataBuf[ 3 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 3 ]->m_pDataLength + i ), *( vDataBuf[ 3 ]->m_pInd + i ) );
				T5 obj5 = TypeConvertor< T5 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 4 ]->m_pBuffer + vDataBuf[ 4 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 4 ]->m_pDataLength + i ), *( vDataBuf[ 4 ]->m_pInd + i ) );
				T6 obj6 = TypeConvertor< T6 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 5 ]->m_pBuffer + vDataBuf[ 5 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 5 ]->m_pDataLength + i ), *( vDataBuf[ 5 ]->m_pInd + i ) );
				vResult.push_back( make_tuple( obj1, obj2, obj3, obj4, obj5, obj6 ) );
			}
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

	// specialize list for batched bind
	template < class T1, class T2, class T3, class T4, class T5, class T6, class T7 >
	class TypeHandler< list< tuple< T1, T2, T3, T4, T5, T6, T7 > > >
	{
	public:
		static void bind(std::size_t pos, const list< tuple< T1, T2, T3, T4, T5, T6, T7 > >& obj, AbstractBinder* pBinder)
		{
			assert( pBinder != 0 );
			list< T1 > copy_obj1;
			list< T2 > copy_obj2;
			list< T3 > copy_obj3;
			list< T4 > copy_obj4;
			list< T5 > copy_obj5;
			list< T6 > copy_obj6;
			list< T7 > copy_obj7;
			for( typename list< tuple< T1, T2, T3, T4, T5, T6, T7 > >::const_iterator it = obj.begin(); it != obj.end(); ++ it )
			{
				copy_obj1.push_back( get< 0 >( *it ) );
				copy_obj2.push_back( get< 1 >( *it ) );
				copy_obj3.push_back( get< 2 >( *it ) );
				copy_obj4.push_back( get< 3 >( *it ) );
				copy_obj5.push_back( get< 4 >( *it ) );
				copy_obj6.push_back( get< 5 >( *it ) );
				copy_obj7.push_back( get< 6 >( *it ) );
			}
			TypeHandler< list< T1 > >::bind( pos, copy_obj1, pBinder );
			TypeHandler< list< T2 > >::bind( pos + 1, copy_obj2, pBinder );
			TypeHandler< list< T3 > >::bind( pos + 2, copy_obj3, pBinder );
			TypeHandler< list< T4 > >::bind( pos + 3, copy_obj4, pBinder );
			TypeHandler< list< T5 > >::bind( pos + 4, copy_obj5, pBinder );
			TypeHandler< list< T6 > >::bind( pos + 5, copy_obj6, pBinder );
			TypeHandler< list< T7 > >::bind( pos + 6, copy_obj7, pBinder );
		}

		static void extract( std::size_t pos, AbstractExtractor* pExtractor )
		{
			assert( pExtractor != 0 );
			TypeHandler< list< T1 > >::extract( pos, pExtractor );
			TypeHandler< list< T2 > >::extract( pos + 1, pExtractor );
			TypeHandler< list< T3 > >::extract( pos + 2, pExtractor );
			TypeHandler< list< T4 > >::extract( pos + 3, pExtractor );
			TypeHandler< list< T5 > >::extract( pos + 4, pExtractor );
			TypeHandler< list< T6 > >::extract( pos + 5, pExtractor );
			TypeHandler< list< T7 > >::extract( pos + 6, pExtractor );
		}

		static void fetch( std::size_t nPos, list< tuple< T1, T2, T3, T4, T5, T6, T7 > >& vResult, AbstractExtractor* pExtractor, vector< shared_ptr< OcciDataBuffer > >& vDataBuf, size_t nFetchedNum )
		{
			assert( pExtractor != 0 );
			assert( vDataBuf.size() == 7 );
			for( size_t i = 0; i < nFetchedNum; ++ i )
			{
				T1 obj1 = TypeConvertor< T1 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 0 ]->m_pBuffer + vDataBuf[ 0 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 0 ]->m_pDataLength + i ), *( vDataBuf[ 0 ]->m_pInd + i ) );
				T2 obj2 = TypeConvertor< T2 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 1 ]->m_pBuffer + vDataBuf[ 1 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 1 ]->m_pDataLength + i ), *( vDataBuf[ 1 ]->m_pInd + i ) );
				T3 obj3 = TypeConvertor< T3 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 2 ]->m_pBuffer + vDataBuf[ 2 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 2 ]->m_pDataLength + i ), *( vDataBuf[ 2 ]->m_pInd + i ) );
				T4 obj4 = TypeConvertor< T4 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 3 ]->m_pBuffer + vDataBuf[ 3 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 3 ]->m_pDataLength + i ), *( vDataBuf[ 3 ]->m_pInd + i ) );
				T5 obj5 = TypeConvertor< T5 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 4 ]->m_pBuffer + vDataBuf[ 4 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 4 ]->m_pDataLength + i ), *( vDataBuf[ 4 ]->m_pInd + i ) );
				T6 obj6 = TypeConvertor< T6 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 5 ]->m_pBuffer + vDataBuf[ 5 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 5 ]->m_pDataLength + i ), *( vDataBuf[ 5 ]->m_pInd + i ) );
				T7 obj7 = TypeConvertor< T7 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 6 ]->m_pBuffer + vDataBuf[ 6 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 6 ]->m_pDataLength + i ), *( vDataBuf[ 6 ]->m_pInd + i ) );
				vResult.push_back( make_tuple( obj1, obj2, obj3, obj4, obj5, obj6, obj7 ) );
			}
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

	// specialize list for batched bind
	template < class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8 >
	class TypeHandler< list< tuple< T1, T2, T3, T4, T5, T6, T7, T8 > > >
	{
	public:
		static void bind(std::size_t pos, const list< tuple< T1, T2, T3, T4, T5, T6, T7, T8 > >& obj, AbstractBinder* pBinder)
		{
			assert( pBinder != 0 );
			list< T1 > copy_obj1;
			list< T2 > copy_obj2;
			list< T3 > copy_obj3;
			list< T4 > copy_obj4;
			list< T5 > copy_obj5;
			list< T6 > copy_obj6;
			list< T7 > copy_obj7;
			list< T8 > copy_obj8;
			for( typename list< tuple< T1, T2, T3, T4, T5, T6, T7, T8 > >::const_iterator it = obj.begin(); it != obj.end(); ++ it )
			{
				copy_obj1.push_back( get< 0 >( *it ) );
				copy_obj2.push_back( get< 1 >( *it ) );
				copy_obj3.push_back( get< 2 >( *it ) );
				copy_obj4.push_back( get< 3 >( *it ) );
				copy_obj5.push_back( get< 4 >( *it ) );
				copy_obj6.push_back( get< 5 >( *it ) );
				copy_obj7.push_back( get< 6 >( *it ) );
				copy_obj8.push_back( get< 7 >( *it ) );
			}
			TypeHandler< list< T1 > >::bind( pos, copy_obj1, pBinder );
			TypeHandler< list< T2 > >::bind( pos + 1, copy_obj2, pBinder );
			TypeHandler< list< T3 > >::bind( pos + 2, copy_obj3, pBinder );
			TypeHandler< list< T4 > >::bind( pos + 3, copy_obj4, pBinder );
			TypeHandler< list< T5 > >::bind( pos + 4, copy_obj5, pBinder );
			TypeHandler< list< T6 > >::bind( pos + 5, copy_obj6, pBinder );
			TypeHandler< list< T7 > >::bind( pos + 6, copy_obj7, pBinder );
			TypeHandler< list< T8 > >::bind( pos + 7, copy_obj8, pBinder );
		}

		static void extract( std::size_t pos, AbstractExtractor* pExtractor )
		{
			assert( pExtractor != 0 );
			TypeHandler< list< T1 > >::extract( pos, pExtractor );
			TypeHandler< list< T2 > >::extract( pos + 1, pExtractor );
			TypeHandler< list< T3 > >::extract( pos + 2, pExtractor );
			TypeHandler< list< T4 > >::extract( pos + 3, pExtractor );
			TypeHandler< list< T5 > >::extract( pos + 4, pExtractor );
			TypeHandler< list< T6 > >::extract( pos + 5, pExtractor );
			TypeHandler< list< T7 > >::extract( pos + 6, pExtractor );
			TypeHandler< list< T8 > >::extract( pos + 7, pExtractor );
		}

		static void fetch( std::size_t nPos, list< tuple< T1, T2, T3, T4, T5, T6, T7, T8 > >& vResult, AbstractExtractor* pExtractor, vector< shared_ptr< OcciDataBuffer > >& vDataBuf, size_t nFetchedNum )
		{
			assert( pExtractor != 0 );
			assert( vDataBuf.size() == 8 );
			for( size_t i = 0; i < nFetchedNum; ++ i )
			{
				T1 obj1 = TypeConvertor< T1 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 0 ]->m_pBuffer + vDataBuf[ 0 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 0 ]->m_pDataLength + i ), *( vDataBuf[ 0 ]->m_pInd + i ) );
				T2 obj2 = TypeConvertor< T2 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 1 ]->m_pBuffer + vDataBuf[ 1 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 1 ]->m_pDataLength + i ), *( vDataBuf[ 1 ]->m_pInd + i ) );
				T3 obj3 = TypeConvertor< T3 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 2 ]->m_pBuffer + vDataBuf[ 2 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 2 ]->m_pDataLength + i ), *( vDataBuf[ 2 ]->m_pInd + i ) );
				T4 obj4 = TypeConvertor< T4 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 3 ]->m_pBuffer + vDataBuf[ 3 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 3 ]->m_pDataLength + i ), *( vDataBuf[ 3 ]->m_pInd + i ) );
				T5 obj5 = TypeConvertor< T5 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 4 ]->m_pBuffer + vDataBuf[ 4 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 4 ]->m_pDataLength + i ), *( vDataBuf[ 4 ]->m_pInd + i ) );
				T6 obj6 = TypeConvertor< T6 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 5 ]->m_pBuffer + vDataBuf[ 5 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 5 ]->m_pDataLength + i ), *( vDataBuf[ 5 ]->m_pInd + i ) );
				T7 obj7 = TypeConvertor< T7 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 6 ]->m_pBuffer + vDataBuf[ 6 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 6 ]->m_pDataLength + i ), *( vDataBuf[ 6 ]->m_pInd + i ) );
				T8 obj8 = TypeConvertor< T8 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 7 ]->m_pBuffer + vDataBuf[ 7 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 7 ]->m_pDataLength + i ), *( vDataBuf[ 7 ]->m_pInd + i ) );
				vResult.push_back( make_tuple( obj1, obj2, obj3, obj4, obj5, obj6, obj7, obj8 ) );
			}
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

	// specialize list for batched bind
	template < class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9 >
	class TypeHandler< list< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9 > > >
	{
	public:
		static void bind(std::size_t pos, const list< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9 > >& obj, AbstractBinder* pBinder)
		{
			assert( pBinder != 0 );
			list< T1 > copy_obj1;
			list< T2 > copy_obj2;
			list< T3 > copy_obj3;
			list< T4 > copy_obj4;
			list< T5 > copy_obj5;
			list< T6 > copy_obj6;
			list< T7 > copy_obj7;
			list< T8 > copy_obj8;
			list< T9 > copy_obj9;
			for( typename list< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9 > >::const_iterator it = obj.begin(); it != obj.end(); ++ it )
			{
				copy_obj1.push_back( get< 0 >( *it ) );
				copy_obj2.push_back( get< 1 >( *it ) );
				copy_obj3.push_back( get< 2 >( *it ) );
				copy_obj4.push_back( get< 3 >( *it ) );
				copy_obj5.push_back( get< 4 >( *it ) );
				copy_obj6.push_back( get< 5 >( *it ) );
				copy_obj7.push_back( get< 6 >( *it ) );
				copy_obj8.push_back( get< 7 >( *it ) );
				copy_obj9.push_back( get< 8 >( *it ) );
			}
			TypeHandler< list< T1 > >::bind( pos, copy_obj1, pBinder );
			TypeHandler< list< T2 > >::bind( pos + 1, copy_obj2, pBinder );
			TypeHandler< list< T3 > >::bind( pos + 2, copy_obj3, pBinder );
			TypeHandler< list< T4 > >::bind( pos + 3, copy_obj4, pBinder );
			TypeHandler< list< T5 > >::bind( pos + 4, copy_obj5, pBinder );
			TypeHandler< list< T6 > >::bind( pos + 5, copy_obj6, pBinder );
			TypeHandler< list< T7 > >::bind( pos + 6, copy_obj7, pBinder );
			TypeHandler< list< T8 > >::bind( pos + 7, copy_obj8, pBinder );
			TypeHandler< list< T9 > >::bind( pos + 8, copy_obj9, pBinder );
		}

		static void extract( std::size_t pos, AbstractExtractor* pExtractor )
		{
			assert( pExtractor != 0 );
			TypeHandler< list< T1 > >::extract( pos, pExtractor );
			TypeHandler< list< T2 > >::extract( pos + 1, pExtractor );
			TypeHandler< list< T3 > >::extract( pos + 2, pExtractor );
			TypeHandler< list< T4 > >::extract( pos + 3, pExtractor );
			TypeHandler< list< T5 > >::extract( pos + 4, pExtractor );
			TypeHandler< list< T6 > >::extract( pos + 5, pExtractor );
			TypeHandler< list< T7 > >::extract( pos + 6, pExtractor );
			TypeHandler< list< T8 > >::extract( pos + 7, pExtractor );
			TypeHandler< list< T9 > >::extract( pos + 8, pExtractor );
		}

		static void fetch( std::size_t nPos, list< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9 > >& vResult, AbstractExtractor* pExtractor, vector< shared_ptr< OcciDataBuffer > >& vDataBuf, size_t nFetchedNum )
		{
			assert( pExtractor != 0 );
			assert( vDataBuf.size() == 9 );
			for( size_t i = 0; i < nFetchedNum; ++ i )
			{
				T1 obj1 = TypeConvertor< T1 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 0 ]->m_pBuffer + vDataBuf[ 0 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 0 ]->m_pDataLength + i ), *( vDataBuf[ 0 ]->m_pInd + i ) );
				T2 obj2 = TypeConvertor< T2 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 1 ]->m_pBuffer + vDataBuf[ 1 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 1 ]->m_pDataLength + i ), *( vDataBuf[ 1 ]->m_pInd + i ) );
				T3 obj3 = TypeConvertor< T3 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 2 ]->m_pBuffer + vDataBuf[ 2 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 2 ]->m_pDataLength + i ), *( vDataBuf[ 2 ]->m_pInd + i ) );
				T4 obj4 = TypeConvertor< T4 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 3 ]->m_pBuffer + vDataBuf[ 3 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 3 ]->m_pDataLength + i ), *( vDataBuf[ 3 ]->m_pInd + i ) );
				T5 obj5 = TypeConvertor< T5 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 4 ]->m_pBuffer + vDataBuf[ 4 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 4 ]->m_pDataLength + i ), *( vDataBuf[ 4 ]->m_pInd + i ) );
				T6 obj6 = TypeConvertor< T6 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 5 ]->m_pBuffer + vDataBuf[ 5 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 5 ]->m_pDataLength + i ), *( vDataBuf[ 5 ]->m_pInd + i ) );
				T7 obj7 = TypeConvertor< T7 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 6 ]->m_pBuffer + vDataBuf[ 6 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 6 ]->m_pDataLength + i ), *( vDataBuf[ 6 ]->m_pInd + i ) );
				T8 obj8 = TypeConvertor< T8 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 7 ]->m_pBuffer + vDataBuf[ 7 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 7 ]->m_pDataLength + i ), *( vDataBuf[ 7 ]->m_pInd + i ) );
				T9 obj9 = TypeConvertor< T8 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 8 ]->m_pBuffer + vDataBuf[ 8 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 8 ]->m_pDataLength + i ), *( vDataBuf[ 8 ]->m_pInd + i ) );
				vResult.push_back( make_tuple( obj1, obj2, obj3, obj4, obj5, obj6, obj7, obj8, obj9 ) );
			}
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

	// specialize list for batched bind
	template < class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10 >
	class TypeHandler< list< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9, T10 > > >
	{
	public:
		static void bind(std::size_t pos, const list< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9, T10 > >& obj, AbstractBinder* pBinder)
		{
			assert( pBinder != 0 );
			list< T1 > copy_obj1;
			list< T2 > copy_obj2;
			list< T3 > copy_obj3;
			list< T4 > copy_obj4;
			list< T5 > copy_obj5;
			list< T6 > copy_obj6;
			list< T7 > copy_obj7;
			list< T8 > copy_obj8;
			list< T9 > copy_obj9;
			list< T10 > copy_obj10;
			for( typename list< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9, T10 > >::const_iterator it = obj.begin(); it != obj.end(); ++ it )
			{
				copy_obj1.push_back( get< 0 >( *it ) );
				copy_obj2.push_back( get< 1 >( *it ) );
				copy_obj3.push_back( get< 2 >( *it ) );
				copy_obj4.push_back( get< 3 >( *it ) );
				copy_obj5.push_back( get< 4 >( *it ) );
				copy_obj6.push_back( get< 5 >( *it ) );
				copy_obj7.push_back( get< 6 >( *it ) );
				copy_obj8.push_back( get< 7 >( *it ) );
				copy_obj9.push_back( get< 8 >( *it ) );
				copy_obj10.push_back( get< 9 >( *it ) );
			}
			TypeHandler< list< T1 > >::bind( pos, copy_obj1, pBinder );
			TypeHandler< list< T2 > >::bind( pos + 1, copy_obj2, pBinder );
			TypeHandler< list< T3 > >::bind( pos + 2, copy_obj3, pBinder );
			TypeHandler< list< T4 > >::bind( pos + 3, copy_obj4, pBinder );
			TypeHandler< list< T5 > >::bind( pos + 4, copy_obj5, pBinder );
			TypeHandler< list< T6 > >::bind( pos + 5, copy_obj6, pBinder );
			TypeHandler< list< T7 > >::bind( pos + 6, copy_obj7, pBinder );
			TypeHandler< list< T8 > >::bind( pos + 7, copy_obj8, pBinder );
			TypeHandler< list< T9 > >::bind( pos + 8, copy_obj9, pBinder );
			TypeHandler< list< T10 > >::bind( pos + 9, copy_obj10, pBinder );
		}

		static void extract( std::size_t pos, AbstractExtractor* pExtractor )
		{
			assert( pExtractor != 0 );
			TypeHandler< list< T1 > >::extract( pos, pExtractor );
			TypeHandler< list< T2 > >::extract( pos + 1, pExtractor );
			TypeHandler< list< T3 > >::extract( pos + 2, pExtractor );
			TypeHandler< list< T4 > >::extract( pos + 3, pExtractor );
			TypeHandler< list< T5 > >::extract( pos + 4, pExtractor );
			TypeHandler< list< T6 > >::extract( pos + 5, pExtractor );
			TypeHandler< list< T7 > >::extract( pos + 6, pExtractor );
			TypeHandler< list< T8 > >::extract( pos + 7, pExtractor );
			TypeHandler< list< T9 > >::extract( pos + 8, pExtractor );
			TypeHandler< list< T10 > >::extract( pos + 9, pExtractor );
		}

		static void fetch( std::size_t nPos, list< tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9, T10 > >& vResult, AbstractExtractor* pExtractor, vector< shared_ptr< OcciDataBuffer > >& vDataBuf, size_t nFetchedNum )
		{
			assert( pExtractor != 0 );
			assert( vDataBuf.size() == 10 );
			for( size_t i = 0; i < nFetchedNum; ++ i )
			{
				T1 obj1 = TypeConvertor< T1 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 0 ]->m_pBuffer + vDataBuf[ 0 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 0 ]->m_pDataLength + i ), *( vDataBuf[ 0 ]->m_pInd + i ) );
				T2 obj2 = TypeConvertor< T2 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 1 ]->m_pBuffer + vDataBuf[ 1 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 1 ]->m_pDataLength + i ), *( vDataBuf[ 1 ]->m_pInd + i ) );
				T3 obj3 = TypeConvertor< T3 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 2 ]->m_pBuffer + vDataBuf[ 2 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 2 ]->m_pDataLength + i ), *( vDataBuf[ 2 ]->m_pInd + i ) );
				T4 obj4 = TypeConvertor< T4 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 3 ]->m_pBuffer + vDataBuf[ 3 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 3 ]->m_pDataLength + i ), *( vDataBuf[ 3 ]->m_pInd + i ) );
				T5 obj5 = TypeConvertor< T5 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 4 ]->m_pBuffer + vDataBuf[ 4 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 4 ]->m_pDataLength + i ), *( vDataBuf[ 4 ]->m_pInd + i ) );
				T6 obj6 = TypeConvertor< T6 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 5 ]->m_pBuffer + vDataBuf[ 5 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 5 ]->m_pDataLength + i ), *( vDataBuf[ 5 ]->m_pInd + i ) );
				T7 obj7 = TypeConvertor< T7 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 6 ]->m_pBuffer + vDataBuf[ 6 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 6 ]->m_pDataLength + i ), *( vDataBuf[ 6 ]->m_pInd + i ) );
				T8 obj8 = TypeConvertor< T8 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 7 ]->m_pBuffer + vDataBuf[ 7 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 7 ]->m_pDataLength + i ), *( vDataBuf[ 7 ]->m_pInd + i ) );
				T9 obj9 = TypeConvertor< T8 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 8 ]->m_pBuffer + vDataBuf[ 8 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 8 ]->m_pDataLength + i ), *( vDataBuf[ 8 ]->m_pInd + i ) );
				T9 obj10 = TypeConvertor< T8 >::retrieve( ( ( void* )( ( char* )vDataBuf[ 9 ]->m_pBuffer + vDataBuf[ 9 ]->m_nDataBufMaxPerLength * i ) ) , *( vDataBuf[ 9 ]->m_pDataLength + i ), *( vDataBuf[ 9 ]->m_pInd + i ) );
				vResult.push_back( make_tuple( obj1, obj2, obj3, obj4, obj5, obj6, obj7, obj8, obj9, obj10 ) );
			}
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


