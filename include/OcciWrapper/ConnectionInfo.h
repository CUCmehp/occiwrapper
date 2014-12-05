#pragma once
#include "OcciWrapper/Common.h"
#include "OcciWrapper/Type.h"
#include <sstream>

#pragma warning( disable : 4251 )

namespace occiwrapper
{
	struct __OCCI_WRAPPER_API ConnectionInfo
	{
		//ip address
		string ip;

		//oracle server port
		UInt32 port;

		//oracle username
		string username;

		//oracle password
		string password;

		//oracle sid
		string sid;

		/***
		*	@brief: Construction
		*/
		ConnectionInfo( const string& ip = "127.0.0.1", const UInt32& port = 1521, const string& username = "", const string& password = "", const string& sid = "" );

		/***
		*	@brief: Destroyed function
		*/
		~ConnectionInfo();

		/***
		*	@brief: Copy Construction
		*/
		ConnectionInfo( const ConnectionInfo& copy );

		/***
		*	@brief: assign function
		*/
		ConnectionInfo& operator = ( const ConnectionInfo& rhs );

		/***
		*	@brief: hash to string
		*/
		string GetHashString() const;
	};
}