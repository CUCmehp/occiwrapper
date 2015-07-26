#include "OcciWrapper/BlobStream.h"



occiwrapper::BlobStreamBuf::BlobStreamBuf( occiwrapper::LobBase& blob ): 
	_blob(blob),
	_it(_blob.begin())
{
}


occiwrapper::BlobStreamBuf::~BlobStreamBuf()
{
}


occiwrapper::UnbufferedStreamBuf::int_type occiwrapper::BlobStreamBuf::readFromDevice()
{
	if( _it != _blob.end() )
		return charToInt( *_it++ );
	else
		return -1;
}


occiwrapper::UnbufferedStreamBuf::int_type occiwrapper::BlobStreamBuf::writeToDevice( char c )
{
	_blob._pContent->push_back( c );
	return 1;
}


//
// BlobIOS
//
occiwrapper::BlobIOS::BlobIOS( occiwrapper::LobBase& blob, openmode mode ) :_buf( blob )
{
	init( &_buf );
}
	

occiwrapper::BlobIOS::~BlobIOS()
{
}


occiwrapper::BlobStreamBuf* occiwrapper::BlobIOS::rdbuf()
{
	return &_buf;
}


//
// BLOBOutputStream
//
occiwrapper::LobBaseOutputStream::LobBaseOutputStream( occiwrapper::LobBase& blob )
	: BlobIOS( blob, std::ios::out )
	, std::ostream( &_buf )
{
}

occiwrapper::LobBaseOutputStream::~LobBaseOutputStream()
{
}


//
// BLOBInputStream
//


occiwrapper::LobBaseInputStream::LobBaseInputStream( occiwrapper::LobBase& blob )
	: BlobIOS( blob, std::ios::in )
	, std::istream( &_buf )
{
}

occiwrapper::LobBaseInputStream::~LobBaseInputStream()
{
}
