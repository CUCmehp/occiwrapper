#include "OcciWrapper/Session.h"
#include "OcciWrapper/StatementImpl.h"

occiwrapper::Session::Session( shared_ptr< occiwrapper::Connection > pConnection, bool bAutoCommit )
:m_bAutoCommit( bAutoCommit )
{
	this->m_pConnection = pConnection;
}

shared_ptr< occiwrapper::StatementImpl > occiwrapper::Session::CreateStatementImpl()
{
	// TODO: check connection
	if( m_pConnection == NULL || m_pConnection->GetValidity() == INVALID )
	{
		return shared_ptr< occiwrapper::StatementImpl >();
	}
	return shared_ptr< occiwrapper::StatementImpl >( new occiwrapper::StatementImpl( this->m_pConnection->CreateStatement( ), this->m_pConnection, this->m_bAutoCommit ) );
}

void occiwrapper::Session::Commit()
{
	if( m_pConnection != NULL )
	{
		this->m_pConnection->Commit();
	}
}

void occiwrapper::Session::SetAutoCommit( bool bAutoCommit )
{
	this->m_bAutoCommit = bAutoCommit;
}

void occiwrapper::Session::Rollback()
{
	if( m_pConnection != NULL )
	{
		this->m_pConnection->Rollback();
	}
}

occiwrapper::Session::~Session()
{
	
}