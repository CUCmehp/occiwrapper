#pragma once
#include "OcciWrapper/Common.h"
#include "OcciWrapper/TypeHandler.h"

using namespace std;

namespace occiwrapper
{
	// forward declaration
	class __OCCI_WRAPPER_API AbstractBinder;

	/***
	*	@brief: AbstractBinding connects a value with a placeholder via an AbstractBinder interface.
	*	@add by CUCmehp.
	*/
	class __OCCI_WRAPPER_API AbstractBinding
	{
	public:
		/***
		*	@brief: Creates the AbstractBinding.
		*/
		AbstractBinding();

		/***
		*	@brief: Destroys the AbstractBinding.
		*/
		virtual ~AbstractBinding();

		/***
		*	@brief: Sets the object used for binding; object does NOT take ownership of the pointer.
		*/
		virtual void SetBinder( AbstractBinder* pBinder );

		/***
		*	@brief:
		*		Returns the AbstractBinder used for binding data.
		*/
		inline AbstractBinder* GetBinder() const
		{
			return m_pBinder;
		}


		/***
		*	@brief: The trivial case will be one single column but when
		*			complex types are used this value can be larger than one.
		*	@return:
		*		the number of columns that the binding handles.
		*/
		virtual std::size_t NumOfColumnsHandled() const = 0;

		/***
		*	@brief: The trivial case will be one single row but 
		*			for collection data types (ie vector) it can be larger.
		*	@return:
		*		the number of rows that the binding handles.
		*/
		virtual std::size_t NumOfRowsHandled() const = 0;

		/***
		*	@return: 
		*		true if we have enough data to bind
		*/
		virtual bool CanBind() const = 0;

		/***
		*	@brief: Binds a value to the given column position
		*/
		virtual void Bind( std::size_t nPos ) = 0;

		/***
		*	@brief: retrieve value from statement
		*	@parameters:
		*		nPos: parameter index.
		*/
		virtual void ReverseBind( std::size_t nPos ) = 0;

		/***
		*	@brief: Allows a binding to be reused.
		*/
		virtual void Reset() = 0;
		
		/***
		*	@return:
		*		true if is batched bind, false or not.
		*/
		virtual bool IsBatchedBind() = 0;

		/***
		*	@brief:	set batched bind number.
		*/
		virtual void SetBatchedNum( size_t nBatchedNum ) = 0;

		/***
		*	@brief:	get batched bind number.
		*/
		virtual int GetBatchedNum() = 0;

		/***
		*	@brief: is registered as out variable
		*/
		virtual bool IsOut() = 0;

		/***
		*	@brief: is registered as in variable
		*/
		virtual bool IsIn() = 0;

	private:
		AbstractBinder* m_pBinder;
	};
}