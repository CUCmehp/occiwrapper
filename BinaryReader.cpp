#pragma warning( disable : 4244 )

#include "OcciWrapper/BinaryReader.h"
#include "OcciWrapper/ByteOrder.h"




occiwrapper::BinaryReader::BinaryReader(std::istream& istr, occiwrapper::BinaryReader::StreamByteOrder byteOrder ):
	_istr(istr)
{
#if defined( ARCH_BIG_ENDIAN )
	_flipBytes = ( byteOrder == occiwrapper::BinaryReader::LITTLE_ENDIAN_BYTE_ORDER );
#else
	_flipBytes = ( byteOrder == occiwrapper::BinaryReader::BIG_ENDIAN_BYTE_ORDER );
#endif
}


occiwrapper::BinaryReader::~BinaryReader()
{
}


occiwrapper::BinaryReader& occiwrapper::BinaryReader::operator >> ( bool& value )
{
	_istr.read( ( char* )&value, sizeof( value ) );
	return *this;
}


occiwrapper::BinaryReader& occiwrapper::BinaryReader::operator >> ( char& value )
{
	_istr.read( ( char* )&value, sizeof( value ) );
	return *this;
}


occiwrapper::BinaryReader& occiwrapper::BinaryReader::operator >> ( occiwrapper::UInt8& value )
{
	_istr.read( ( char* )&value, sizeof( value ) );
	return *this;
}


occiwrapper::BinaryReader& occiwrapper::BinaryReader::operator >> ( occiwrapper::Int8& value)
{
	_istr.read( ( char* )&value, sizeof( value ) );
	return *this;
}

occiwrapper::BinaryReader& occiwrapper::BinaryReader::operator >> ( occiwrapper::Int16& value )
{
	_istr.read( ( char* )&value, sizeof( value ) );
	if( _flipBytes ) 
	{
		value = ByteOrder::flipBytes( value );
	}
	return *this;
}


occiwrapper::BinaryReader& occiwrapper::BinaryReader::operator >> ( occiwrapper::UInt16& value )
{
	_istr.read( (char*) &value, sizeof( value ) );
	if( _flipBytes )
	{
		value = ByteOrder::flipBytes(value);
	}
	return *this;
}


occiwrapper::BinaryReader& occiwrapper::BinaryReader::operator >> ( occiwrapper::Int32& value )
{
	_istr.read((char*) &value, sizeof(value));
	if (_flipBytes) 
	{
		value = ByteOrder::flipBytes(value);
	}
	return *this;
}


occiwrapper::BinaryReader& occiwrapper::BinaryReader::operator >> ( occiwrapper::UInt32& value )
{
	_istr.read((char*) &value, sizeof(value));
	if( _flipBytes )
	{
		value = ByteOrder::flipBytes(value);
	}
	return *this;
}


//occiwrapper::BinaryReader& occiwrapper::BinaryReader::operator >> ( long& value )
//{
//	_istr.read((char*) &value, sizeof(value));
//#if defined(POCO_LONG_IS_64_BIT)
//	if (_flipBytes) value = ByteOrder::flipBytes((Int64) value);
//#else
//	if (_flipBytes) value = ByteOrder::flipBytes((Int32) value);
//#endif
//	return *this;
//}


//BinaryReader& BinaryReader::operator >>( unsigned long& value )
//{
//	_istr.read((char*) &value, sizeof(value));
//#if defined(POCO_LONG_IS_64_BIT)
//	if (_flipBytes) value = ByteOrder::flipBytes((UInt64) value);
//#else
//	if (_flipBytes) value = ByteOrder::flipBytes((UInt32) value);
//#endif
//	return *this;
//}


occiwrapper::BinaryReader& occiwrapper::BinaryReader::operator >> ( float& value )
{
	if (_flipBytes)
	{
		char* ptr = (char*) &value;
		ptr += sizeof(value);
		for (unsigned i = 0; i < sizeof(value); ++i)
			_istr.read(--ptr, 1);
	}
	else
	{
		_istr.read((char*) &value, sizeof(value));
	}
	return *this;
}


occiwrapper::BinaryReader& occiwrapper::BinaryReader::operator >> (double& value)
{
	if (_flipBytes)
	{
		char* ptr = (char*) &value;
		ptr += sizeof(value);
		for (unsigned i = 0; i < sizeof(value); ++i)
			_istr.read(--ptr, 1);
	}
	else
	{
		_istr.read((char*) &value, sizeof(value));
	}
	return *this;
}

occiwrapper::BinaryReader& occiwrapper::BinaryReader::operator >> ( Int64& value )
{
	_istr.read( (char*) &value, sizeof( value ) );
	if (_flipBytes) 
	{
		value = ByteOrder::flipBytes(value);
	}
	return *this;
}


occiwrapper::BinaryReader& occiwrapper::BinaryReader::operator >> ( UInt64& value )
{
	_istr.read((char*) &value, sizeof(value));
	if (_flipBytes)
	{
		value = ByteOrder::flipBytes(value);
	}
	return *this;
}


occiwrapper::BinaryReader& occiwrapper::BinaryReader::operator >> ( std::string& value )
{
	UInt32 size = 0;
	read7BitEncoded(size);
	value.clear();
	value.reserve(size);
	while (size--)
	{
		char c;
		_istr.read(&c, 1);
		value += c;
	}
	return *this;
}




void occiwrapper::BinaryReader::read7BitEncoded( occiwrapper::UInt32& value)
{
	char c;
	value = 0;
	int s = 0;
	do
	{
		c = 0;
		_istr.read(&c, 1);
		UInt32 x = (c & 0x7F);
		x <<= s;
		value += x;
		s += 7;
	}while( c & 0x80 );
}

void occiwrapper::BinaryReader::read7BitEncoded( occiwrapper::UInt64& value )
{
	char c;
	value = 0;
	int s = 0;
	do
	{
		c = 0;
		_istr.read(&c, 1);
		UInt64 x = (c & 0x7F);
		x <<= s;
		value += x;
		s += 7;
	}
	while( c & 0x80 );
}

void occiwrapper::BinaryReader::readRaw( std::streamsize length, std::string& value )
{
	value.clear();
	value.reserve( length );
	while (length--)
	{
		char c;
		_istr.read( &c, 1 );
		value += c;
	}
}


void occiwrapper::BinaryReader::readRaw( char* buffer, std::streamsize length )
{
	_istr.read( buffer, length );
}


void occiwrapper::BinaryReader::readBOM()
{
	occiwrapper::UInt16 bom;
	_istr.read( ( char* )&bom, sizeof( bom ) );
	_flipBytes = bom != 0xFEFF;
}
