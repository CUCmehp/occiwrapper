#include "Statement.h"
#include "Session.h"

//occiwrapper::Statement::~Statement()
//{
//
//}

occiwrapper::Statement::Statement( Session& session )
:_executed( false )
{
	this->pImp = session.CreateStatementImpl( );
}


//occiwrapper::Statement& occiwrapper::Statement::operator ,( occiwrapper::Manipulator manip ) /*Statement& operator , (AbstractBinding* info)*/



//occiwrapper::Statement::Statement( shared_ptr< StatementImpl > pImp )
//{
//	this->pImp = pImp;
//}

//void occiwrapper::Manipulator::operator()( Statement& statement )
//{
//	statement.execute();
//}