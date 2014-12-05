#include "OcciWrapper/SessionFactory.h"

occiwrapper::SessionFactory::SessionFactory()
{
	
}

occiwrapper::SessionFactory::~SessionFactory()
{

}

occiwrapper::Session occiwrapper::SessionFactory::Create( const ConnectionInfo& connInfo, bool bAutoCommit )
{
	shared_ptr< occiwrapper::Connection > p = m_objConnectionPool.GetConnection( connInfo );
	return Session( p, bAutoCommit );
}
