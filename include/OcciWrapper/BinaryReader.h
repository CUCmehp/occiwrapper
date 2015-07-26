#pragma once

#include "OcciWrapper/Common.h"
#include <istream>


namespace occiwrapper
{

/// This class reads basic types in binary form into an input stream.
/// It provides an extractor-based interface similar to istream.
/// The reader also supports automatic conversion from big-endian
/// (network byte order) to little-endian and vice-versa.
/// Use a BinaryWriter to create a stream suitable for a BinaryReader.
class __OCCI_WRAPPER_API BinaryReader
{
public:
	enum StreamByteOrder
	{
		NATIVE_BYTE_ORDER        = 1,  /// the host's native byte-order
		BIG_ENDIAN_BYTE_ORDER    = 2,  /// big-endian (network) byte-order
		NETWORK_BYTE_ORDER       = 2,  /// big-endian (network) byte-order
		LITTLE_ENDIAN_BYTE_ORDER = 3,  /// little-endian byte-order
		UNSPECIFIED_BYTE_ORDER   = 4   /// unknown, byte-order will be determined by reading the byte-order mark
	};

	/// Creates the BinaryReader.
	BinaryReader( std::istream& istr, StreamByteOrder byteOrder = NATIVE_BYTE_ORDER );
		
	/// Destroys the BinaryReader.
	~BinaryReader();
		

	BinaryReader& operator >> ( bool& value );
	BinaryReader& operator >> ( char& value);
	//BinaryReader& operator >> ( long& value );
	//BinaryReader& operator >> ( unsigned long& value );
	BinaryReader& operator >> ( float& value );
	BinaryReader& operator >> ( double& value );

	BinaryReader& operator >> ( Int8& value );
	BinaryReader& operator >> ( UInt8& value );
	BinaryReader& operator >> ( Int16& value );
	BinaryReader& operator >> ( UInt16& value );
	BinaryReader& operator >> ( Int32& value );
	BinaryReader& operator >> ( UInt32& value );
	BinaryReader& operator >> ( Int64& value );
	BinaryReader& operator >> ( UInt64& value );

	BinaryReader& operator >> (std::string& value);

	/// Reads a 32-bit unsigned integer in compressed format.
	/// See BinaryWriter::write7BitEncoded() for a description
	/// of the compression algorithm.
	void read7BitEncoded(UInt32& value);

	/// Reads a 64-bit unsigned integer in compressed format.
	/// See BinaryWriter::write7BitEncoded() for a description
	/// of the compression algorithm.
	void read7BitEncoded(UInt64& value);
		
	/// Reads length bytes of raw data into value.
	void readRaw(std::streamsize length, std::string& value);
		
	/// Reads length bytes of raw data into buffer.
	void readRaw(char* buffer, std::streamsize length);
		
	/// Reads a byte-order mark from the stream and configures
	/// the reader for the encountered byte order.
	/// A byte-order mark is a 16-bit integer with a value of 0xFEFF,
	/// written in host byte order.
	void readBOM();
		
	/// Returns _istr.good();		
	bool good();
		
	/// Returns _istr.fail();		
	bool fail();
		
	/// Returns _istr.bad();
	bool bad();
	
	/// Returns _istr.eof();
	bool eof();
		
	/// Returns the underlying stream.
	std::istream& stream() const;
		

	/// Returns the byte-order used by the reader, which is
	/// either BIG_ENDIAN_BYTE_ORDER or LITTLE_ENDIAN_BYTE_ORDER.
	StreamByteOrder byteOrder() const;
		

private:
	std::istream& _istr;
	bool          _flipBytes; 
};


//
// inlines
//


inline bool BinaryReader::good()
{
	return _istr.good();
}

	
inline bool BinaryReader::fail()
{
	return _istr.fail();
}


inline bool BinaryReader::bad()
{
	return _istr.bad();
}


inline bool BinaryReader::eof()
{
	return _istr.eof();
}


inline std::istream& BinaryReader::stream() const
{
	return _istr;
}

	
inline BinaryReader::StreamByteOrder BinaryReader::byteOrder() const
{
#if defined( ARCH_BIG_ENDIAN )
	return _flipBytes ? LITTLE_ENDIAN_BYTE_ORDER : BIG_ENDIAN_BYTE_ORDER;
#else
	return _flipBytes ? BIG_ENDIAN_BYTE_ORDER : LITTLE_ENDIAN_BYTE_ORDER;
#endif
}


} // namespace occiwrapper

