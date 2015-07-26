#include "OcciWrapper/LobBase.h"

namespace occiwrapper
{


LobBase::LobBase():
	_pContent(new std::vector<char>())
{
}


LobBase::LobBase( const std::vector<char>& content ):
	_pContent( new std::vector<char>(content) )
{
}


LobBase::LobBase(const char* const pContent, std::size_t size):
	_pContent(new std::vector<char>( pContent, pContent + size ) )
{
}


LobBase::LobBase( const std::string& content ):
	_pContent(new std::vector<char>( content.begin(), content.end() ) )
{
}


LobBase::LobBase(const LobBase& other):
	_pContent(other._pContent)
{
}


LobBase::~LobBase()
{
}


LobBase& LobBase::operator = (const LobBase& other)
{
	LobBase tmp(other);
	Swap(tmp);
	return *this;
}



} // namespace occiwrapper
