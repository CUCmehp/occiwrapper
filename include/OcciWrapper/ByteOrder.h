#pragma once

#include "OcciWrapper/Common.h"


namespace occiwrapper
{

/// This class contains a number of static methods
/// to convert between big-endian and little-endian
/// integers of various sizes.
class __OCCI_WRAPPER_API ByteOrder
{
public:
	static Int16 flipBytes( Int16 value );
	static UInt16 flipBytes( UInt16 value );
	static Int32 flipBytes( Int32 value );
	static UInt32 flipBytes( UInt32 value );
	static Int64 flipBytes( Int64 value);
	static UInt64 flipBytes( UInt64 value );

	static Int16 toBigEndian( Int16 value );
	static UInt16 toBigEndian( UInt16 value );
	static Int32 toBigEndian( Int32 value );
	static UInt32 toBigEndian( UInt32 value );
	static Int64 toBigEndian( Int64 value );
	static UInt64 toBigEndian( UInt64 value );

	static Int16 fromBigEndian( Int16 value );
	static UInt16 fromBigEndian( UInt16 value );
	static Int32 fromBigEndian( Int32 value );
	static UInt32 fromBigEndian( UInt32 value );
	static Int64 fromBigEndian( Int64 value );
	static UInt64 fromBigEndian( UInt64 value );

	static Int16 toLittleEndian( Int16 value );
	static UInt16 toLittleEndian( UInt16 value );
	static Int32 toLittleEndian( Int32 value );
	static UInt32 toLittleEndian( UInt32 value );
	static Int64 toLittleEndian( Int64 value );
	static UInt64 toLittleEndian( UInt64 value );

	static Int16 fromLittleEndian( Int16 value );
	static UInt16 fromLittleEndian( UInt16 value );
	static Int32 fromLittleEndian( Int32 value );
	static UInt32 fromLittleEndian( UInt32 value );
	static Int64 fromLittleEndian( Int64 value );
	static UInt64 fromLittleEndian( UInt64 value );

	static Int16 toNetwork( Int16 value );
	static UInt16 toNetwork( UInt16 value );
	static Int32 toNetwork( Int32 value );
	static UInt32 toNetwork( UInt32 value );
	static Int64 toNetwork( Int64 value );
	static UInt64 toNetwork( UInt64 value );

	static Int16 fromNetwork( Int16 value );
	static UInt16 fromNetwork( UInt16 value );
	static Int32 fromNetwork( Int32 value );
	static UInt32 fromNetwork( UInt32 value );
	static Int64 fromNetwork( Int64 value );
	static UInt64 fromNetwork( UInt64 value );
};


//
// inlines
//
inline UInt16 ByteOrder::flipBytes( UInt16 value )
{
	return ( (value >> 8 ) & 0x00FF) | ((value << 8) & 0xFF00);
}


inline Int16 ByteOrder::flipBytes( Int16 value )
{
	return Int16(flipBytes(UInt16(value)));
}


inline UInt32 ByteOrder::flipBytes( UInt32 value )
{
	return ( ( value >> 24) & 0x000000FF ) | ( ( value >> 8 ) & 0x0000FF00 )
	     | ( ( value << 8 ) & 0x00FF0000 ) | ( ( value << 24 ) & 0xFF000000 );
}


inline Int32 ByteOrder::flipBytes( Int32 value )
{
	return Int32( flipBytes( UInt32( value ) ) );
}

inline UInt64 ByteOrder::flipBytes( UInt64 value )
{
	UInt32 hi = UInt32( value >> 32 );
	UInt32 lo = UInt32( value & 0xFFFFFFFF );
	return UInt64( flipBytes( hi ) ) | ( UInt64( flipBytes( lo ) ) << 32 );
}


inline Int64 ByteOrder::flipBytes(Int64 value)
{
	return Int64( flipBytes( UInt64(value) ) );
}

//
// some macro trickery to automate the method implementation
//
#define OCCIWRAPPER_IMPLEMENT_BYTEORDER_NOOP_( op, type ) \
	inline type ByteOrder::op( type value )		\
	{											\
		return value;							\
	}
#define OCCIWRAPPER_IMPLEMENT_BYTEORDER_FLIP_( op, type ) \
	inline type ByteOrder::op( type value )		\
	{											\
		return flipBytes( value );				\
	}


#define OCCIWRAPPER_IMPLEMENT_BYTEORDER_NOOP( op ) \
	OCCIWRAPPER_IMPLEMENT_BYTEORDER_NOOP_( op, Int16 )	\
	OCCIWRAPPER_IMPLEMENT_BYTEORDER_NOOP_( op, UInt16 )	\
	OCCIWRAPPER_IMPLEMENT_BYTEORDER_NOOP_( op, Int32 )	\
	OCCIWRAPPER_IMPLEMENT_BYTEORDER_NOOP_( op, UInt32 )	\
	OCCIWRAPPER_IMPLEMENT_BYTEORDER_NOOP_( op, Int64 )	\
	OCCIWRAPPER_IMPLEMENT_BYTEORDER_NOOP_( op, UInt64 )
#define OCCIWRAPPER_IMPLEMENT_BYTEORDER_FLIP(op) \
	OCCIWRAPPER_IMPLEMENT_BYTEORDER_FLIP_( op, Int16 )	\
	OCCIWRAPPER_IMPLEMENT_BYTEORDER_FLIP_( op, UInt16 )	\
	OCCIWRAPPER_IMPLEMENT_BYTEORDER_FLIP_( op, Int32 )	\
	OCCIWRAPPER_IMPLEMENT_BYTEORDER_FLIP_( op, UInt32 )	\
	OCCIWRAPPER_IMPLEMENT_BYTEORDER_FLIP_( op, Int64 )	\
	OCCIWRAPPER_IMPLEMENT_BYTEORDER_FLIP_( op, UInt64 )


#if defined( ARCH_BIG_ENDIAN )
	#define OCCIWRAPPER_IMPLEMENT_BYTEORDER_BIG OCCIWRAPPER_IMPLEMENT_BYTEORDER_NOOP
	#define OCCIWRAPPER_IMPLEMENT_BYTEORDER_LIT OCCIWRAPPER_IMPLEMENT_BYTEORDER_FLIP
#else
	#define OCCIWRAPPER_IMPLEMENT_BYTEORDER_BIG OCCIWRAPPER_IMPLEMENT_BYTEORDER_FLIP
	#define OCCIWRAPPER_IMPLEMENT_BYTEORDER_LIT OCCIWRAPPER_IMPLEMENT_BYTEORDER_NOOP
#endif


OCCIWRAPPER_IMPLEMENT_BYTEORDER_BIG( toBigEndian )
OCCIWRAPPER_IMPLEMENT_BYTEORDER_BIG( fromBigEndian )
OCCIWRAPPER_IMPLEMENT_BYTEORDER_BIG( toNetwork )
OCCIWRAPPER_IMPLEMENT_BYTEORDER_BIG( fromNetwork )
OCCIWRAPPER_IMPLEMENT_BYTEORDER_LIT( toLittleEndian )
OCCIWRAPPER_IMPLEMENT_BYTEORDER_LIT( fromLittleEndian )


} // namespace occiwrapper
