#pragma once

#include <ostream>
#include "OcciWrapper/Common.h"


namespace occiwrapper
{

/// This class writes basic types in binary form into an output stream.
/// It provides an inserter-based interface similar to ostream.
/// The writer also supports automatic conversion from big-endian
/// (network byte order) to little-endian and vice-versa.
/// Use a BinaryReader to read from a stream created by a BinaryWriter.
/// Be careful when exchanging data between systems with different
/// data type sizes (e.g., 32-bit and 64-bit architectures), as the sizes
/// of some of the basic types may be different. For example, writing a
/// long integer on a 64-bit system and reading it on a 32-bit system
/// may yield an incorrect result. Use fixed-size types (Int32, Int64, etc.)
/// in such a case.
class __OCCI_WRAPPER_API BinaryWriter
{
public:
	enum StreamByteOrder
	{
		NATIVE_BYTE_ORDER        = 1, /// the host's native byte-order
		BIG_ENDIAN_BYTE_ORDER    = 2, /// big-endian (network) byte-order
		NETWORK_BYTE_ORDER       = 2, /// big-endian (network) byte-order
		LITTLE_ENDIAN_BYTE_ORDER = 3  /// little-endian byte-order
	};
	
	/// Creates the BinaryWriter.
	BinaryWriter( std::ostream& ostr, StreamByteOrder byteOrder = NATIVE_BYTE_ORDER );
		
	/// Destroys the BinaryWriter.
	~BinaryWriter();
		

	BinaryWriter& operator << ( bool value );
	BinaryWriter& operator << ( char value );
	BinaryWriter& operator << ( UInt8 value );
	BinaryWriter& operator << ( Int8 value);
	BinaryWriter& operator << ( Int16 value);
	BinaryWriter& operator << ( UInt16 value);
	BinaryWriter& operator << ( Int32 value);
	BinaryWriter& operator << ( UInt32 value);
	//BinaryWriter& operator << ( long value);
	//BinaryWriter& operator << ( unsigned long value);
	BinaryWriter& operator << ( float value);
	BinaryWriter& operator << ( double value);

	BinaryWriter& operator << ( Int64 value );
	BinaryWriter& operator << ( UInt64 value );

	BinaryWriter& operator << ( const std::string& value );
	BinaryWriter& operator << ( const char* value );
	
	/// Writes a 32-bit unsigned integer in a compressed format.
	/// The value is written out seven bits at a time, starting 
	/// with the seven least-significant bits. 
	/// The high bit of a byte indicates whether there are more bytes to be 
	/// written after this one.
	/// If value will fit in seven bits, it takes only one byte of space. 
	/// If value will not fit in seven bits, the high bit is set on the first byte and 
	/// written out. value is then shifted by seven bits and the next byte is written. 
	/// This process is repeated until the entire integer has been written.
	void write7BitEncoded( UInt32 value );
		
	/// Writes a 64-bit unsigned integer in a compressed format.
	/// The value written out seven bits at a time, starting 
	/// with the seven least-significant bits. 
	/// The high bit of a byte indicates whether there are more bytes to be 
	/// written after this one.
	/// If value will fit in seven bits, it takes only one byte of space. 
	/// If value will not fit in seven bits, the high bit is set on the first byte and 
	/// written out. value is then shifted by seven bits and the next byte is written. 
	/// This process is repeated until the entire integer has been written.
	void write7BitEncoded( UInt64 value );
		
	/// Writes the string as-is to the stream.
	void writeRaw( const std::string& rawData );
		
	/// Writes length raw bytes from the given buffer to the stream.		
	void writeRaw( const char* buffer, std::streamsize length );
		
	/// Writes a byte-order mark to the stream. A byte order mark is
	/// a 16-bit integer with a value of 0xFEFF, written in host byte-order. 
	/// A BinaryReader uses the byte-order mark to determine the byte-order 
	/// of the stream.
	void writeBOM();
		
	/// Flushes the underlying stream.
	void flush();
		
	/// Returns _ostr.good();		
	bool good();
		
	/// Returns _ostr.fail();		
	bool fail();
		
	/// Returns _ostr.bad();
	bool bad();
		
	/// Returns the underlying stream.		
	std::ostream& stream() const;
		
	/// Returns the byte ordering used by the writer, which is
	/// either BIG_ENDIAN_BYTE_ORDER or LITTLE_ENDIAN_BYTE_ORDER.		
	StreamByteOrder byteOrder() const;
		

private:
	std::ostream& _ostr;
	bool          _flipBytes;
};


//
// inlines
//


inline std::ostream& BinaryWriter::stream() const
{
	return _ostr;
}


inline bool BinaryWriter::good()
{
	return _ostr.good();
}


inline bool BinaryWriter::fail()
{
	return _ostr.fail();
}


inline bool BinaryWriter::bad()
{
	return _ostr.bad();
}


inline BinaryWriter::StreamByteOrder BinaryWriter::byteOrder() const
{
#if defined( ARCH_BIG_ENDIAN )
	return _flipBytes ? LITTLE_ENDIAN_BYTE_ORDER : BIG_ENDIAN_BYTE_ORDER;
#else
	return _flipBytes ? BIG_ENDIAN_BYTE_ORDER : LITTLE_ENDIAN_BYTE_ORDER;
#endif
}


} // namespace occiwrapper

