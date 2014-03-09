#pragma once

#include "Common.h"

namespace occiwrapper
{
	/***
	*	@brief: 
	*		Interface for Binding data types to placeholders. The default placeholder format 
	*		in the SQL query is ":name".
	*/
	class __OCCI_WRAPPER_API AbstractBinder
	{
	public:
		/***
		*	@brief: Creates the AbstractBinder.
		*/
		AbstractBinder();

		/***
		*	@brief: Destroys the AbstractBinder.
		*/
		virtual ~AbstractBinder();

		/***
		*	@brief: binds an Int8.
		*/
		virtual void Bind( std::size_t nPos, const Int8& val ) = 0;

		/***
		*	@brief: retrieve an Int8.
		*/
		virtual void Retrieve( std::size_t nPos, Int8& val ) = 0;

		/***
		*	@brief: binds an UInt8.
		*/
		virtual void Bind( std::size_t nPos, const UInt8& val ) = 0;

		/***
		*	@brief: retrieve an UInt8.
		*/
		virtual void Retrieve( std::size_t nPos, UInt8& val ) = 0;

		/***
		*	@brief: binds an Int16.
		*/
		virtual void Bind( std::size_t nPos, const Int16& val ) = 0;

		/***
		*	@brief: retrieve an Int16.
		*/
		virtual void Retrieve( std::size_t nPos, Int16& val ) = 0;

		/***
		*	@brief: binds an UInt16.
		*/
		virtual void Bind( std::size_t nPos, const UInt16& val ) = 0;

		/***
		*	@brief: retrieve an UInt16.
		*/
		virtual void Retrieve( std::size_t nPos, UInt16& val ) = 0;

		/***
		*	@brief: binds an Int32.
		*/
		virtual void Bind( std::size_t nPos, const Int32& val ) = 0;
		
		/***
		*	@brief: retrieve an Int32.
		*/
		virtual void Retrieve( std::size_t nPos, Int32& val ) = 0;

		/***
		*	@brief: binds an UInt32.
		*/
		virtual void Bind( std::size_t nPos, const UInt32& val ) = 0;

		/***
		*	@brief: retrieve an UInt32.
		*/
		virtual void Retrieve( std::size_t nPos, UInt32& val ) = 0;

		/***
		*	@brief: binds an Int64.
		*/
		virtual void Bind( std::size_t nPos, const Int64& val ) = 0;

		/***
		*	@brief: retrieve an Int64.
		*/
		virtual void Retrieve( std::size_t nPos, Int64& val ) = 0;

		/***
		*	@brief: binds an UInt64.
		*/
		virtual void Bind( std::size_t nPos, const UInt64& val ) = 0;

		/***
		*	@brief: retrieve an UInt64.
		*/
		virtual void Retrieve( std::size_t nPos, UInt64& val ) = 0;

		/***
		*	@brief: binds a bool.
		*/
		virtual void Bind( std::size_t nPos, const bool& val ) = 0;

		/***
		*	@brief: retrieve a bool.
		*/
		virtual void Retrieve( std::size_t nPos, bool& val ) = 0;
		
		/***
		*	@brief: binds a float.
		*/
		virtual void Bind( std::size_t nPos, const float& val ) = 0;

		/***
		*	@brief: retrieve a float.
		*/
		virtual void Retrieve( std::size_t nPos, float& val ) = 0;

		/***
		*	@brief: binds a double.
		*/
		virtual void Bind( std::size_t nPos, const double& val ) = 0;

		/***
		*	@brief: retrieve a Number.
		*/
		virtual void Retrieve( std::size_t nPos, double& val ) = 0;
		
		/***
		*	@brief: bind a Number.
		*/
		virtual void Bind( std::size_t nPos, const oracle::occi::Number& val ) = 0;

		/***
		*	@brief: retrieve a Number.
		*/
		virtual void Retrieve( std::size_t nPos, oracle::occi::Number& val ) = 0;

		/***
		*	@brief: binds a const char ptr.
		*/
		virtual void Bind( std::size_t nPos, const char* const &val ) = 0;

		/***
		*	@brief: retrieve a const char ptr.
		*/
		virtual void Retrieve( std::size_t nPos, const char* const& val ) = 0;
		
		/***
		*	@brief: binds a string.
		*/
		virtual void Bind( std::size_t nPos, const std::string& val ) = 0;

		/***
		*	@brief: retrieve a string.
		*/
		virtual void Retrieve( std::size_t nPos, string& val ) = 0;
		
		/***
		*	@brief: binds a struct tm.
		*/
		virtual void Bind( std::size_t nPos, const struct tm& val ) = 0;

		/***
		*	@brief: retrieve a struct tm.
		*/
		virtual void Retrieve( std::size_t nPos, struct tm& val ) = 0;

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
		virtual void BatchedBind(std::size_t nPos, void* pBuf, const size_t nEachBufLength, UInt16* pLength, Int16* pInd, enum oracle::occi::Type type ) = 0;

		/***
		*	@brief: get environment.
		*	@parameters:
		*		nPos: parameter index.
		*		pBuf: buffer pointer.
		*		nEachBufLength: buffer length for every data item, data length must less than nEachBufLength.
		*		pLength: pointer to length of every data item.
		*		pInd: pointer to the data is NULL or not, if the value is -1, then the data referred to is NULL.
		*		type: occi data type.
		*/
		virtual oracle::occi::Environment* GetEnv() = 0;

		/***
		*	@brief: registered as out variable
		*	@parameters:
		*		eDirection: set parameter direction
		*/
		virtual void SetDirection( const DataDirection_E& eDirection );

		/***
		*	@brief: declare the parameter is an out parameter or not.
		*	@return: return true, if the parameter is a out parameter.
		*/
		virtual bool IsOut();

		/***
		*	@brief: declare the parameter is a in parameter or not.
		*	@return: return true, if the parameter is a in parameter.
		*/
		virtual bool IsIn();

	protected:
		// is registered as out variable
		occiwrapper::DataDirection_E m_eDataDirection;
	};

}
