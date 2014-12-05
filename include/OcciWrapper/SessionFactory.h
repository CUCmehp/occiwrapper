#pragma once
#include "OcciWrapper/ConnectionInfo.h"
#include "OcciWrapper/ConnectionPool.h"
#include "OcciWrapper/Session.h"

namespace occiwrapper
{
	/***
	*	@brief: A SessionFactory is a class that stores Connectors and allows to create Sessions.
	*	@add by CUCmehp
	*/
	class __OCCI_WRAPPER_API SessionFactory
	{
	public:
		/***
		*	@brief: Creates a Session for the given connection info.
		*	@add by CUCmehp
		*	@parameters:
		*		connInfo: oracle connect information
		*		bAutoCommit: the session is auto committed or not.
		*/
		Session Create( const ConnectionInfo& connInfo, bool bAutoCommit = true );

		SessionFactory();
		~SessionFactory();
	private:

		SessionFactory(const SessionFactory&);
		SessionFactory& operator = (const SessionFactory& );

	private:
		ConnectionPool					m_objConnectionPool;
	};
}