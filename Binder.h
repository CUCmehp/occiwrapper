#pragma once
#include "Common.h"
#include "AbstractBinder.h"
#include "occiCommon.h"
#include "Exception.h"
#include <limits>

#pragma warning( disable : 4251 )

namespace occiwrapper
{
	
	/***
	*	@brief: Binds placeholders in the sql query to the provided values. Performs data types mapping.
	*/
	class __OCCI_WRAPPER_API Binder : public AbstractBinder
	{
	public:

		/***
		*	@brief: construction for Binder
		*	@parameters:
		*		pOcciStat: occi statement for this binder.
		*		pEnv: point to occi environment.
		*/
		Binder( oracle::occi::Statement* pOcciStat, oracle::occi::Environment* pEnv );

		/***
		*	@brief: set occi statement for this binder.
		*	@parameters:
		*		pOcciStat: occi statement for this binder.
		*/
		void SetStatement( oracle::occi::Statement* pOcciStat );

		/***
		*	@brief: set occi environment for this binder.
		*	@parameters:
		*		pOcciStat: occi environment for this binder.
		*/
		void SetEnv( oracle::occi::Environment* p_env );

		/***
		*	@brief: get occi environment for this binder.
		*	@return: 
		*		occi environment for this binder.
		*/
		virtual oracle::occi::Environment* GetEnv();

		/***
		*	@brief: destroys the binder.
		*/
		virtual ~Binder();

		/***
		*	@brief: Binds an Int8.
		*	@parameters:
		*		nPos: parameter index.
		*		val:  parameter value
		*/
		virtual void Bind( std::size_t nPos, const Int8& val );

		/***
		*	@brief: Retrive an Int8.
		*	@parameters:
		*		nPos: parameter index.
		*		val:  parameter value
		*/
		virtual void Retrieve( std::size_t nPos, Int8& val );
		
		/***
		*	@brief: Binds an UInt8.
		*	@parameters:
		*		nPos: parameter index.
		*		val:  parameter value
		*/
		virtual void Bind( std::size_t nPos, const UInt8& val );

		/***
		*	@brief: Retrieve an UInt8.
		*	@parameters:
		*		nPos: parameter index.
		*		val:  parameter value
		*/
		virtual void Retrieve( std::size_t nPos, UInt8& val );
		
		/***
		*	@brief: Binds an Int16.
		*	@parameters:
		*		nPos: parameter index.
		*		val:  parameter value
		*/
		virtual void Bind( std::size_t nPos, const Int16& val );

		/***
		*	@brief: Retrieve an Int16.
		*	@parameters:
		*		nPos: parameter index.
		*		val:  parameter value
		*/
		virtual void Retrieve( std::size_t nPos, Int16& val );
		
		/***
		*	@brief: Binds an UInt16.
		*	@parameters:
		*		nPos: parameter index.
		*		val:  parameter value
		*/
		virtual void Bind( std::size_t nPos, const UInt16& val );

		/***
		*	@brief: Retrieve an UInt16.
		*	@parameters:
		*		nPos: parameter index.
		*		val:  parameter value
		*/
		virtual void Retrieve( std::size_t nPos, UInt16& val );
		
		/***
		*	@brief: Binds an Int32.
		*	@parameters:
		*		nPos: parameter index.
		*		val:  parameter value
		*/
		virtual void Bind( std::size_t nPos, const Int32& val );

		/***
		*	@brief: Retrieve an Int32.
		*	@parameters:
		*		nPos: parameter index.
		*		val:  parameter value
		*/
		virtual void Retrieve( std::size_t nPos, Int32& val);
		
		/***
		*	@brief: Binds an UInt32.
		*	@parameters:
		*		nPos: parameter index.
		*		val:  parameter value
		*/
		virtual void Bind(std::size_t nPos, const UInt32& val );

		/***
		*	@brief: Retrieve an UInt32.
		*	@parameters:
		*		nPos: parameter index.
		*		val:  parameter value
		*/
		virtual void Retrieve( std::size_t nPos, UInt32& val );
		
		/***
		*	@brief: Binds an Int64.
		*	@parameters:
		*		nPos: parameter index.
		*		val:  parameter value
		*/
		virtual void Bind( std::size_t nPos, const Int64& val );

		/***
		*	@brief: Retrieve an Int64.
		*	@parameters:
		*		nPos: parameter index.
		*		val:  parameter value
		*/
		virtual void Retrieve( std::size_t nPos, Int64& val );
		
		/***
		*	@brief: Binds an UInt64.
		*	@parameters:
		*		nPos: parameter index.
		*		val:  parameter value
		*/
		virtual void Bind( std::size_t nPos, const UInt64& val );

		/***
		*	@brief: Retrieve an UInt64.
		*	@parameters:
		*		nPos: parameter index.
		*		val:  parameter value
		*/
		virtual void Retrieve( std::size_t nPos, UInt64& val );
		
		/***
		*	@brief: Binds a bool.
		*	@parameters:
		*		nPos: parameter index.
		*		val:  parameter value
		*/
		virtual void Bind( std::size_t nPos, const bool& val );

		/***
		*	@brief: Retrieve a bool.
		*	@parameters:
		*		nPos: parameter index.
		*		val:  parameter value
		*/
		virtual void Retrieve( std::size_t nPos, bool& val );
		
		/***
		*	@brief: Binds a float.
		*	@parameters:
		*		nPos: parameter index.
		*		val:  parameter value
		*/
		virtual void Bind(std::size_t nPos, const float& val );

		/***
		*	@brief: Retrieve a float.
		*	@parameters:
		*		nPos: parameter index.
		*		val:  parameter value
		*/
		virtual void Retrieve( std::size_t nPos, float& val );

		/***
		*	@brief: Binds a double.
		*	@parameters:
		*		nPos: parameter index.
		*		val:  parameter value
		*/
		virtual void Bind(std::size_t nPos, const double& val );

		/***
		*	@brief: Retrieve a double.
		*	@parameters:
		*		nPos: parameter index.
		*		val:  parameter value
		*/
		virtual void Retrieve( std::size_t nPos, double& val );

		/***
		*	@brief: Binds a Number.
		*	@parameters:
		*		nPos: parameter index.
		*		val:  parameter value
		*/
		virtual void Bind( std::size_t nPos, const oracle::occi::Number& val );

		/***
		*	@brief: Retrieve a Number.
		*	@parameters:
		*		nPos: parameter index.
		*		val:  parameter value
		*/
		virtual void Retrieve( std::size_t nPos, oracle::occi::Number& val );
		
		/***
		*	@brief: Binds a string.
		*	@parameters:
		*		nPos: parameter index.
		*		val:  parameter value
		*/
		virtual void Bind( std::size_t nPos, const std::string& val );

		/***
		*	@brief: Retrieve a string.
		*	@parameters:
		*		nPos: parameter index.
		*		val:  parameter value
		*/
		virtual void Retrieve( std::size_t nPos, string& val );
		
		/***
		*	@brief: Binds a date.
		*	@parameters:
		*		nPos: parameter index.
		*		val:  parameter value
		*/
		virtual void Bind(std::size_t nPos, const struct tm& val);

		/***
		*	@brief: Retrieve a date.
		*	@parameters:
		*		nPos: parameter index.
		*		val:  parameter value
		*/
		virtual void Retrieve( std::size_t nPos, struct tm& val );

		/***
		*	@brief: Binds a char*.
		*	@parameters:
		*		nPos: parameter index.
		*		val:  parameter value
		*/
		virtual void Bind(std::size_t nPos, const char* const& str );

		/***
		*	@brief: Retrieve a const char*.
		*	@parameters:
		*		nPos: parameter index.
		*		val:  parameter value
		*/
		virtual void Retrieve( std::size_t nPos, const char* const& val );

		/***
		*	@brief: batched bind a buf to oracle parameter.
		*	@parameters:
		*		nPos: parameter index.
		*		pBuf: buffer pointer.
		*		nEachBufLength: buffer length for every data item, data length must less than nEachBufLength.
		*		pLength: pointer to length of every data item.
		*		pInd: pointer to the data is NULL or not, if the value is -1, then the data referred to is NULL.
		*		type: occi data type.
		*/
		virtual void BatchedBind(std::size_t pos, void* p_buf, const size_t each_buf_length, UInt16* p_length, Int16* p_Ind, enum oracle::occi::Type type );

	private:
		/// Creates the Binder.
		Binder();

		// Occi Statement
		oracle::occi::Statement* m_pOcciStat;

		// Occi Enironment
		oracle::occi::Environment* m_pEnv;

		// for binding
		std::vector< shared_ptr< OcciDataBuffer > > m_vBindArray;
		
		// for bind starting
		bool m_bBindStart;

		// how many data to bind on each column, >1 for batch insert
		UInt16 m_nDataCount;
	};
}