#include "OcciWrapper/BinaryWriter.h"
#include "OcciWrapper/ByteOrder.h"
#include <iostream>
#include <assert.h>
#include <string.h>

using namespace std;


occiwrapper::BinaryWriter::BinaryWriter( std::ostream& ostr, occiwrapper::BinaryWriter::StreamByteOrder byteOrder )
	: _ostr(ostr)
{
#if defined( ARCH_BIG_ENDIAN )
	_flipBytes = ( byteOrder == occiwrapper::BinaryWriter::LITTLE_ENDIAN_BYTE_ORDER );
#else
	_flipBytes = ( byteOrder == occiwrapper::BinaryWriter::BIG_ENDIAN_BYTE_ORDER );
#endif
}


occiwrapper::BinaryWriter::~BinaryWriter()
{
}


occiwrapper::BinaryWriter& occiwrapper::BinaryWriter::operator << ( bool value )
{
	_ostr.write( ( const char* )&value, sizeof( value ) );
	return *this;
}


occiwrapper::BinaryWriter& occiwrapper::BinaryWriter::operator << ( char value )
{
	_ostr.write( ( const char* )&value, sizeof( value ) );
	return *this;
}


occiwrapper::BinaryWriter& occiwrapper::BinaryWriter::operator << ( occiwrapper::UInt8 value )
{
	_ostr.write( ( const char* ) &value, sizeof( value ) );
	return *this;
}


occiwrapper::BinaryWriter& occiwrapper::BinaryWriter::operator << ( occiwrapper::Int8 value )
{
	_ostr.write( ( const char* )&value, sizeof( value ) );
	return *this;
}


occiwrapper::BinaryWriter& occiwrapper::BinaryWriter::operator << ( occiwrapper::Int16 value )
{
	if( _flipBytes )
	{
		short fValue = ByteOrder::flipBytes( value );
		_ostr.write( (const char*)&fValue, sizeof( fValue ) );
	}
	else
	{
		_ostr.write( ( const char* )&value, sizeof( value) );
	}
	return *this;
}


occiwrapper::BinaryWriter& occiwrapper::BinaryWriter::operator << ( occiwrapper::UInt16 value )
{
	if( _flipBytes )
	{
		unsigned short fValue = occiwrapper::ByteOrder::flipBytes( value );
		_ostr.write( ( const char* )&fValue, sizeof( fValue ) );
	}
	else
	{
		_ostr.write( ( const char* )&value, sizeof( value ) );
	}
	return *this;
}


occiwrapper::BinaryWriter& occiwrapper::BinaryWriter::operator << ( occiwrapper::Int32 value )
{
	if( _flipBytes )
	{
		int fValue = occiwrapper::ByteOrder::flipBytes( value );
		_ostr.write( ( const char* )&fValue, sizeof( fValue ) );
	}
	else
	{
		_ostr.write( ( const char* )&value, sizeof( value ) );
	}
	return *this;
}


occiwrapper::BinaryWriter& occiwrapper::BinaryWriter::operator << ( occiwrapper::UInt32 value )
{
	if( _flipBytes )
	{
		unsigned int fValue = ByteOrder::flipBytes( value );
		_ostr.write( ( const char* )&fValue, sizeof( fValue ) );
	}
	else
	{
		_ostr.write( ( const char* )&value, sizeof( value ) );
	}
	return *this;
}

occiwrapper::BinaryWriter& occiwrapper::BinaryWriter::operator << ( float value )
{
	if( _flipBytes )
	{
		const char* ptr = ( const char* ) &value;
		ptr += sizeof( value );
		for( unsigned i = 0; i < sizeof(value); ++i )
		{
			_ostr.write( --ptr, 1 );
		}
	}
	else
	{
		_ostr.write((const char*) &value, sizeof(value));
	}
	return *this;
}


occiwrapper::BinaryWriter& occiwrapper::BinaryWriter::operator << ( double value )
{
	if (_flipBytes)
	{
		const char* ptr = (const char*) &value;
		ptr += sizeof(value);
		for (unsigned i = 0; i < sizeof(value); ++i)
		{
			_ostr.write(--ptr, 1);
		}
	}
	else
	{
		_ostr.write((const char*) &value, sizeof(value));
	}
	return *this;
}

occiwrapper::BinaryWriter& occiwrapper::BinaryWriter::operator << ( occiwrapper::Int64 value )
{
	if (_flipBytes)
	{
		Int64 fValue = ByteOrder::flipBytes(value);
		_ostr.write((const char*) &fValue, sizeof(fValue));
	}
	else
	{
		_ostr.write((const char*) &value, sizeof(value));
	}
	return *this;
}


occiwrapper::BinaryWriter& occiwrapper::BinaryWriter::operator << ( occiwrapper::UInt64 value )
{
	if (_flipBytes)
	{
		UInt64 fValue = ByteOrder::flipBytes(value);
		_ostr.write((const char*) &fValue, sizeof(fValue));
	}
	else
	{
		_ostr.write((const char*) &value, sizeof(value));
	}
	return *this;
}


occiwrapper::BinaryWriter& occiwrapper::BinaryWriter::operator << ( const std::string& value )
{
	UInt32 length = (UInt32) value.size();
	write7BitEncoded(length);
	_ostr.write(value.data(), length);
	return *this;
}


occiwrapper::BinaryWriter& occiwrapper::BinaryWriter::operator << ( const char* value )
{
	assert( value != NULL );
	UInt32 length = ( UInt32 )strlen( value );
	write7BitEncoded(length);
	_ostr.write(value, length);
	return *this;
}


void occiwrapper::BinaryWriter::write7BitEncoded( occiwrapper::UInt32 value )
{
	do
	{
		unsigned char c = (unsigned char) (value & 0x7F);
		value >>= 7;
		if( value ) 
		{
			c |= 0x80;
		}
		_ostr.write( ( const char*) &c, 1 );
	}
	while( value );
}

void occiwrapper::BinaryWriter::write7BitEncoded( occiwrapper::UInt64 value )
{
	do
	{
		unsigned char c = ( unsigned char ) ( value & 0x7F );
		value >>= 7;
		if (value) 
		{
			c |= 0x80;
		}
		_ostr.write( ( const char* ) &c, 1 );
	}
	while( value );
}

void occiwrapper::BinaryWriter::writeRaw( const std::string& rawData )
{
	_ostr.write(rawData.data(), (std::streamsize) rawData.length());
}


void occiwrapper::BinaryWriter::writeRaw( const char* buffer, std::streamsize length )
{
	_ostr.write(buffer, length);
}


void occiwrapper::BinaryWriter::writeBOM()
{
	UInt16 value = 0xFEFF;
	if( _flipBytes )
	{
		value = ByteOrder::flipBytes( value );
	}
	_ostr.write( ( const char* )&value, sizeof( value ) );
}


void occiwrapper::BinaryWriter::flush()
{
	_ostr.flush();
}
