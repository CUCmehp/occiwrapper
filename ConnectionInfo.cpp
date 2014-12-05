#include "OcciWrapper/ConnectionInfo.h"


occiwrapper::ConnectionInfo::ConnectionInfo( const string& ip /*= "127.0.0.1"*/, const UInt32& port /*= 1521*/, const string& username /*= ""*/, const string& password /*= ""*/, const string& sid /*= "" */ )
{
	this->ip = ip;
	this->port = port;
	this->username = username;
	this->password = password;
	this->sid = sid;
}

occiwrapper::ConnectionInfo::ConnectionInfo( const ConnectionInfo& copy )
{
	*this = copy;
}

occiwrapper::ConnectionInfo::~ConnectionInfo()
{
	this->ip = "";
	this->port = 0;
	this->username = "";
	this->password = "";
	this->sid = "";
}

occiwrapper::ConnectionInfo& occiwrapper::ConnectionInfo::operator=( const ConnectionInfo& rhs )
{
	this->ip = rhs.ip;
	this->port = rhs.port;
	this->username = rhs.username;
	this->password = rhs.password;
	this->sid = rhs.sid;
	return *this;
}

string occiwrapper::ConnectionInfo::GetHashString() const
{
	stringstream ss;
	ss<< ip << "_" << port << "_" << username << "_" << password << "_" << sid;
	return ss.str();
}
