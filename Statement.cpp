#include "OcciWrapper/Statement.h"
#include "OcciWrapper/Session.h"

occiwrapper::Statement::Statement( Session& session )
:_executed( false )
{
	this->m_pImp = session.CreateStatementImpl( );
}
