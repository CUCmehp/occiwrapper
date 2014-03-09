#pragma once
#include <string>
#include <sstream>
#include "Common.h"
#include "Environment.h"
#include "ConnectionInfo.h"
#include "occi.h"

#pragma warning( disable : 4996 )
#pragma warning( disable : 4251 )

namespace occiwrapper
{
	/**
	*	@brief: class for database connection management
	*	@add by: CUCmehp
	*	@add since: 2012-05-05
	*/
	class __OCCI_WRAPPER_API Connection 
		//: public ValidatedObject
	{
	public:
		/***
		*	@brief: create connection to oracle database, use connection info
		*	@add by: CUCmehp
		*	@add since: 2012-05-05
		*	@parameters:
		*		pEnvironment: pointer of oracle environment
		*		connInfo: connection information
		*	@return: return connection, if failed, return NULL, call GetErrMsg to get error message.
		*/
		static Connection* CreateConnection( shared_ptr< occiwrapper::Environment > pEnviroment, const ConnectionInfo& connInfo );

		/***
		*	@brief: get oracle client environment
		*	@add by: CUCmehp
		*	@add since: 2012-05-05
		*	@return: return oracle Environment, if failed, return NULL, call GetErrMsg to get error message.
		*/
		oracle::occi::Environment* GetEnvirnment();

		/***
		*	@brief: create oracle occi statement with this conneciton
		*	@add by: CUCmehp
		*	@add since: 2012-05-05
		*	@return: return oracle Statement, if failed, return NULL, call GetErrMsg to get error message.
		*/
		oracle::occi::Statement* CreateStatement( const string sql = "" );

		/***
		*	@brief: terminate oracle occi statement with this connection.
		*	@add by: CUCmehp
		*	@add since: 2012-05-05
		*	@parameter:
		*		pOcciStat: oracle statement for terminate.
		*	@return: return success or not, if failed, call GetErrMsg to get error message.
		*/
		bool TerminateStatement( oracle::occi::Statement* pOcciStat );

		/***
		*	@brief: session commit operation
		*	@add by: CUCmehp
		*	@add since: 2012-05-05
		*	@return: return sessuss or not, if failed, call GetErrMsg to get error message.
		*/
		bool Commit();

		/***
		*	@brief: session rollback operation
		*	@add by: CUCmehp
		*	@add since: 2012-05-05
		*	@return: return succeed or not, if failed, call GetErrMsg to get error message.
		*/
		bool Rollback();

		/***
		*	@brief: destroyed connection object.
		*	@add by: CUCmehp
		*	@add since: 2012-05-05
		*/
		virtual ~Connection();

		/***
		*	@brief: declare this object is valid or not.
		*	@add by: CUCmehp
		*	@add since: 2012-05-05
		*/
		virtual Validity GetValidity();

		/***
		*	@brief: get error message
		*/
		string GetErrMsg();

	private:
		/***
		*	@brief: create a connection.
		*/
		Connection( shared_ptr< occiwrapper::Environment >& pParmEnviroment, const ConnectionInfo& connInfo );

		/***
		*	@brief: this function is not implemented
		*/
		Connection();

	private:
		shared_ptr< Environment >			m_pEnviroment;					// environment object
		oracle::occi::Connection*			m_pOcciConnection;				// occi connection
		ConnectionInfo						m_objConnInfo;
		Validity							m_eValidity;
		string								m_strErrMsg;
	};
};
