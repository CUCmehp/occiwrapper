#pragma once

#include "OcciWrapper/Common.h"
#include "OcciWrapper/Connection.h"
#include "OcciWrapper/ConnectionInfo.h"
#include "OcciWrapper/ConnectionPool.h"
#include "OcciWrapper/StatementImpl.h"
#include "OcciWrapper/Statement.h"

#define into( x ) occiwrapper::into( x )

namespace occiwrapper
{
	class __OCCI_WRAPPER_API Session
	{
	public:
		/***
		*	@brief: Creates a new session, using the given connector 
		*	@add by CUCmehp.
		*/
		Session( shared_ptr< occiwrapper::Connection > pConnection, bool bAutoCommit );

		/***
		*	@brief: destroy instance
		*	@add by CUCmehp, since 2012-07-15
		*/
		virtual ~Session();
		
		/***
		*	@brief: Creates a Statement with the given data as SQLContent
		*	@add by CUCmehp
		*/
		template <typename T>
		Statement operator << (const T& t)
		{
			Statement statement( this->CreateStatementImpl() );
			statement << t;
			return statement;
		}

		/***
		*	@brief: Creates a StatementImpl
		*	@add by CUCmehp
		*/
		shared_ptr< StatementImpl > CreateStatementImpl();

		/***
		*	@brief: Commits and ends a transaction.
		*	@add by CUCmehp
		*/
		void Commit();

		/***
		*	@brief: Rolls back and ends a transaction.
		*/
		void Rollback();

		/***
		*	@brief: set auto commit
		*	@add by CUCmehp
		*/
		void SetAutoCommit( bool isAutoCommit );

		/***
		*	@brief: Session is valid or not
		*	@return:
		*		if session is valid, return true, else return false
		*/
		inline bool IsValid()
		{
			return m_pConnection != NULL;
		}

	private:
		Session();

		//hold the oracle connection
		shared_ptr< occiwrapper::Connection >	m_pConnection;
		bool									m_bAutoCommit;
	};
} 

