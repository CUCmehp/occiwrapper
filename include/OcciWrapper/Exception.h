#pragma once
#include <string>
#include <iostream>
using namespace std;

namespace occiwrapper
{
#define DEFINE_EXCEPTION( EXCEPTION_NAME ) \
	class EXCEPTION_NAME : public std::exception	\
	{	\
	public:	\
		EXCEPTION_NAME( const string& msg )	\
			:msg( msg )	\
		{	\
		}	\
		virtual const char* what() const throw() \
		{	\
			return msg.c_str();	\
		}	\
		virtual ~EXCEPTION_NAME() throw() \
		{	\
		}	\
	private:	\
		string msg;	\
	};

	// invalid connection exception
	DEFINE_EXCEPTION( InValidConnectionException )

	// unknown exception
	DEFINE_EXCEPTION( UnknownException )

	// limit exception
	DEFINE_EXCEPTION( LimitException )

	// occi exception
	DEFINE_EXCEPTION( OcciSqlException )

	// when execute oracle statement pramater binding, some exception thrown by occi
	DEFINE_EXCEPTION( BindException )

	// has extract already, can't extract again
	DEFINE_EXCEPTION( ExtractException )

	// invalid ResultSet for Statement is invalid, but the ResultSet is not closed
	DEFINE_EXCEPTION( InvalidResultSetException )
}