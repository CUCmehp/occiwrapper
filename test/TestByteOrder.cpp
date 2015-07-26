#include "TestByteOrder.h"
#include "OcciWrapper/ByteOrder.h"
#include <assert.h>
#include <iostream>

using namespace std;

void TestByteOrderFlip()
{
	{
		occiwrapper::Int16 norm = ( occiwrapper::Int16 )0xAABB;
		occiwrapper::Int16 flip = occiwrapper::ByteOrder::flipBytes( norm );
		assert( occiwrapper::UInt16( flip ) == 0xBBAA );
		flip = occiwrapper::ByteOrder::flipBytes( flip );
		assert( flip == norm );
	}
	{
		occiwrapper::UInt16 norm = ( occiwrapper::UInt16 )0xAABB;
		occiwrapper::UInt16 flip = occiwrapper::ByteOrder::flipBytes( norm );
		assert( flip == 0xBBAA );
		flip = occiwrapper::ByteOrder::flipBytes( flip );
		assert ( flip == norm );
	}
	{
		occiwrapper::Int32 norm = 0xAABBCCDD;
		occiwrapper::Int32 flip = occiwrapper::ByteOrder::flipBytes( norm );
		assert( occiwrapper::UInt32( flip ) == 0xDDCCBBAA );
		flip = occiwrapper::ByteOrder::flipBytes( flip );
		assert( flip == norm );
	}
	{
		occiwrapper::UInt32 norm = 0xAABBCCDD;
		occiwrapper::UInt32 flip = occiwrapper::ByteOrder::flipBytes( norm );
		assert( flip == 0xDDCCBBAA );
		flip = occiwrapper::ByteOrder::flipBytes( flip );
		assert( flip == norm );
	}
	{
		occiwrapper::Int64 norm = ( occiwrapper::Int64( 0x8899AABB ) << 32 ) + 0xCCDDEEFF;
		occiwrapper::Int64 flip = occiwrapper::ByteOrder::flipBytes( norm );
		assert( flip == ( occiwrapper::Int64( 0xFFEEDDCC ) << 32 ) + 0xBBAA9988 );
		flip = occiwrapper::ByteOrder::flipBytes( flip );
		assert( flip == norm );
	}
	{
		occiwrapper::UInt64 norm = ( occiwrapper::UInt64( 0x8899AABB ) << 32 ) + 0xCCDDEEFF;
		occiwrapper::UInt64 flip = occiwrapper::ByteOrder::flipBytes( norm );
		assert( flip == ( occiwrapper::UInt64( 0xFFEEDDCC ) << 32 ) + 0xBBAA9988 );
		flip = occiwrapper::ByteOrder::flipBytes( flip );
		assert( flip == norm );
	}
}


void TestByteOrderBigEndian()
{
#if defined( ARCH_BIG_ENDIAN )
	//
	// big-endian systems
	//
	{
		occiwrapper::Int16 norm = 4;
		occiwrapper::Int16 flip = occiwrapper::ByteOrder::toBigEndian( norm );
		assert( norm == flip );
	}
	{
		occiwrapper::UInt16 norm = 4;
		occiwrapper::UInt16 flip = occiwrapper::ByteOrder::toBigEndian( norm );
		assert( norm == flip );
	}
	{
		occiwrapper::Int32 norm = 4;
		occiwrapper::Int32 flip = occiwrapper::ByteOrder::toBigEndian( norm );
		assert ( norm == flip );
	}
	{
		occiwrapper::UInt32 norm = 4;
		occiwrapper::UInt32 flip = occiwrapper::ByteOrder::toBigEndian( norm );
		assert( norm == flip );
	}
	{
		occiwrapper::Int64 norm = 4;
		occiwrapper::Int64 flip = occiwrapper::ByteOrder::toBigEndian( norm );
		assert( norm == flip );
	}
	{
		occiwrapper::UInt64 norm = 4;
		occiwrapper::UInt64 flip = occiwrapper::ByteOrder::toBigEndian( norm );
		assert( norm == flip );
	}
	{
		occiwrapper::Int16 norm = 4;
		occiwrapper::Int16 flip = occiwrapper::ByteOrder::fromBigEndian( norm );
		assert( norm == flip );
	}
	{
		occiwrapper::UInt16 norm = 4;
		occiwrapper::UInt16 flip = occiwrapper::ByteOrder::fromBigEndian( norm );
		assert( norm == flip );
	}
	{
		occiwrapper::Int32 norm = 4;
		occiwrapper::Int32 flip = occiwrapper::ByteOrder::fromBigEndian( norm );
		assert( norm == flip );
	}
	{
		occiwrapper::UInt32 norm = 4;
		occiwrapper::UInt32 flip = occiwrapper::ByteOrder::fromBigEndian( norm );
		assert( norm == flip );
	}
	{
		occiwrapper::Int64 norm = 4;
		occiwrapper::Int64 flip = occiwrapper::ByteOrder::fromBigEndian( norm );
		assert( norm == flip );
	}
	{
		occiwrapper::UInt64 norm = 4;
		occiwrapper::UInt64 flip = occiwrapper::ByteOrder::fromBigEndian( norm );
		assert( norm == flip );
	}
#else
	//
	// little-endian systems
	//
	{
		occiwrapper::Int16 norm = 4;
		occiwrapper::Int16 flip = occiwrapper::ByteOrder::toBigEndian( norm );
		assert( norm != flip );
		flip = occiwrapper::ByteOrder::flipBytes( flip );
		assert( norm == flip );
	}
	{
		occiwrapper::UInt16 norm = 4;
		occiwrapper::UInt16 flip = occiwrapper::ByteOrder::toBigEndian( norm );
		assert( norm != flip );
		flip = occiwrapper::ByteOrder::flipBytes( flip );
		assert( norm == flip );
	}
	{
		occiwrapper::Int32 norm = 4;
		occiwrapper::Int32 flip = occiwrapper::ByteOrder::toBigEndian( norm );
		assert( norm != flip );
		flip = occiwrapper::ByteOrder::flipBytes( flip );
		assert( norm == flip );
	}
	{
		occiwrapper::UInt32 norm = 4;
		occiwrapper::UInt32 flip = occiwrapper::ByteOrder::toBigEndian( norm );
		assert( norm != flip );
		flip = occiwrapper::ByteOrder::flipBytes( flip );
		assert( norm == flip );
	}
	{
		occiwrapper::Int64 norm = 4;
		occiwrapper::Int64 flip = occiwrapper::ByteOrder::toBigEndian(norm);
		assert( norm != flip );
		flip = occiwrapper::ByteOrder::flipBytes( flip );
		assert( norm == flip );
	}
	{
		occiwrapper::UInt64 norm = 4;
		occiwrapper::UInt64 flip = occiwrapper::ByteOrder::toBigEndian( norm );
		assert( norm != flip );
		flip = occiwrapper::ByteOrder::flipBytes( flip );
		assert( norm == flip );
	}
	{
		occiwrapper::Int16 norm = 4;
		occiwrapper::Int16 flip = occiwrapper::ByteOrder::fromBigEndian( norm );
		assert( norm != flip );
		flip = occiwrapper::ByteOrder::flipBytes( flip );
		assert( norm == flip );
	}
	{
		occiwrapper::UInt16 norm = 4;
		occiwrapper::UInt16 flip = occiwrapper::ByteOrder::fromBigEndian( norm );
		assert( norm != flip );
		flip = occiwrapper::ByteOrder::flipBytes( flip );
		assert( norm == flip );
	}
	{
		occiwrapper::Int32 norm = 4;
		occiwrapper::Int32 flip = occiwrapper::ByteOrder::fromBigEndian( norm );
		assert( norm != flip );
		flip = occiwrapper::ByteOrder::flipBytes( flip );
		assert( norm == flip );
	}
	{
		occiwrapper::UInt32 norm = 4;
		occiwrapper::UInt32 flip = occiwrapper::ByteOrder::fromBigEndian( norm );
		assert( norm != flip );
		flip = occiwrapper::ByteOrder::flipBytes( flip );
		assert( norm == flip );
	}
	{
		occiwrapper::Int64 norm = 4;
		occiwrapper::Int64 flip = occiwrapper::ByteOrder::fromBigEndian( norm );
		assert( norm != flip );
		flip = occiwrapper::ByteOrder::flipBytes( flip );
		assert( norm == flip );
	}
	{
		occiwrapper::UInt64 norm = 4;
		occiwrapper::UInt64 flip = occiwrapper::ByteOrder::fromBigEndian( norm );
		assert( norm != flip );
		flip = occiwrapper::ByteOrder::flipBytes( flip );
		assert( norm == flip );
	}
#endif
}

void TestByteOrderLittleEndian()
{
#if defined( ARCH_LITTLE_ENDIAN )
	//
	// little-endian systems
	//
	{
		occiwrapper::Int16 norm = 4;
		occiwrapper::Int16 flip = occiwrapper::ByteOrder::toLittleEndian( norm );
		assert( norm == flip );
	}
	{
		occiwrapper::UInt16 norm = 4;
		occiwrapper::UInt16 flip = occiwrapper::ByteOrder::toLittleEndian( norm );
		assert( norm == flip );
	}
	{
		occiwrapper::Int32 norm = 4;
		occiwrapper::Int32 flip = occiwrapper::ByteOrder::toLittleEndian( norm );
		assert( norm == flip );
	}
	{
		occiwrapper::UInt32 norm = 4;
		occiwrapper::UInt32 flip = occiwrapper::ByteOrder::toLittleEndian( norm );
		assert( norm == flip );
	}
	{
		occiwrapper::Int64 norm = 4;
		occiwrapper::Int64 flip = occiwrapper::ByteOrder::toLittleEndian( norm );
		assert( norm == flip );
	}
	{
		occiwrapper::UInt64 norm = 4;
		occiwrapper::UInt64 flip = occiwrapper::ByteOrder::toLittleEndian( norm );
		assert( norm == flip );
	}
	{
		occiwrapper::Int16 norm = 4;
		occiwrapper::Int16 flip = occiwrapper::ByteOrder::toLittleEndian( norm );
		assert( norm == flip );
	}
	{
		occiwrapper::UInt16 norm = 4;
		occiwrapper::UInt16 flip = occiwrapper::ByteOrder::toLittleEndian( norm );
		assert( norm == flip );
	}
	{
		occiwrapper::Int32 norm = 4;
		occiwrapper::Int32 flip = occiwrapper::ByteOrder::toLittleEndian( norm );
		assert( norm == flip );
	}
	{
		occiwrapper::UInt32 norm = 4;
		occiwrapper::UInt32 flip = occiwrapper::ByteOrder::toLittleEndian( norm );
		assert( norm == flip );
	}
	{
		occiwrapper::Int64 norm = 4;
		occiwrapper::Int64 flip = occiwrapper::ByteOrder::toLittleEndian( norm );
		assert( norm == flip );
	}
	{
		occiwrapper::UInt64 norm = 4;
		occiwrapper::UInt64 flip = occiwrapper::ByteOrder::toLittleEndian( norm );
		assert( norm == flip );
	}
#else
	//
	// big-endian systems
	//
	{
		occiwrapper::Int16 norm = 4;
		occiwrapper::Int16 flip = occiwrapper::ByteOrder::toLittleEndian( norm );
		assert( norm != flip );
		flip = occiwrapper::ByteOrder::flipBytes( flip );
		assert( norm == flip );
	}
	{
		occiwrapper::UInt16 norm = 4;
		occiwrapper::UInt16 flip = occiwrapper::ByteOrder::toLittleEndian( norm );
		assert( norm != flip );
		flip = occiwrapper::ByteOrder::flipBytes( flip );
		assert( norm == flip );
	}
	{
		occiwrapper::Int32 norm = 4;
		occiwrapper::Int32 flip = occiwrapper::ByteOrder::toLittleEndian( norm );
		assert( norm != flip );
		flip = occiwrapper::ByteOrder::flipBytes( flip );
		assert( norm == flip );
	}
	{
		occiwrapper::UInt32 norm = 4;
		occiwrapper::UInt32 flip = occiwrapper::ByteOrder::toLittleEndian( norm );
		assert( norm != flip );
		flip = occiwrapper::ByteOrder::flipBytes( flip );
		assert( norm == flip );
	}
	{
		occiwrapper::Int64 norm = 4;
		occiwrapper::Int64 flip = occiwrapper::ByteOrder::toLittleEndian( norm );
		assert( norm != flip );
		flip = occiwrapper::ByteOrder::flipBytes( flip );
		assert( norm == flip );
	}
	{
		occiwrapper::UInt64 norm = 4;
		occiwrapper::UInt64 flip = occiwrapper::ByteOrder::toLittleEndian( norm );
		assert( norm != flip );
		flip = occiwrapper::ByteOrder::flipBytes( flip );
		assert( norm == flip );
	}
	{
		occiwrapper::Int16 norm = 4;
		occiwrapper::Int16 flip = occiwrapper::ByteOrder::fromLittleEndian( norm );
		assert( norm != flip );
		flip = occiwrapper::ByteOrder::flipBytes( flip );
		assert (norm == flip);
	}
	{
		occiwrapper::UInt16 norm = 4;
		occiwrapper::UInt16 flip = occiwrapper::ByteOrder::fromLittleEndian( norm );
		assert( norm != flip );
		flip = occiwrapper::ByteOrder::flipBytes( flip );
		assert( norm == flip );
	}
	{
		occiwrapper::Int32 norm = 4;
		occiwrapper::Int32 flip = occiwrapper::ByteOrder::fromLittleEndian( norm );
		assert( norm != flip );
		flip = occiwrapper::ByteOrder::flipBytes( flip );
		assert( norm == flip );
	}
	{
		occiwrapper::UInt32 norm = 4;
		occiwrapper::UInt32 flip = occiwrapper::ByteOrder::fromLittleEndian( norm );
		assert( norm != flip );
		flip = occiwrapper::ByteOrder::flipBytes( flip );
		assert( norm == flip );
	}
	{
		occiwrapper::Int64 norm = 4;
		occiwrapper::Int64 flip = occiwrapper::ByteOrder::fromLittleEndian( norm );
		assert( norm != flip );
		flip = occiwrapper::ByteOrder::flipBytes( flip );
		assert( norm == flip );
	}
	{
		occiwrapper::UInt64 norm = 4;
		occiwrapper::UInt64 flip = occiwrapper::ByteOrder::fromLittleEndian(norm);
		assert( norm != flip );
		flip = occiwrapper::ByteOrder::flipBytes( flip );
		assert ( norm == flip );
	}
#endif
}


void TestByteOrderNetwork()
{
#if defined( ARCH_BIG_ENDIAN )
	//
	// big-endian systems
	//
	{
		occiwrapper::Int16 norm = 4;
		occiwrapper::Int16 flip = occiwrapper::ByteOrder::toNetwork(norm);
		assert( norm == flip );
	}
	{
		occiwrapper::UInt16 norm = 4;
		occiwrapper::UInt16 flip = occiwrapper::ByteOrder::toNetwork( norm );
		assert( norm == flip );
	}
	{
		occiwrapper::Int32 norm = 4;
		occiwrapper::Int32 flip = occiwrapper::ByteOrder::toNetwork( norm );
		assert( norm == flip );
	}
	{
		occiwrapper::UInt32 norm = 4;
		occiwrapper::UInt32 flip = occiwrapper::ByteOrder::toNetwork( norm );
		assert( norm == flip );
	}
	{
		occiwrapper::Int64 norm = 4;
		occiwrapper::Int64 flip = occiwrapper::ByteOrder::toNetwork( norm );
		assert( norm == flip );
	}
	{
		occiwrapper::UInt64 norm = 4;
		occiwrapper::UInt64 flip = occiwrapper::ByteOrder::toNetwork( norm );
		assert( norm == flip );
	}
	{
		occiwrapper::Int16 norm = 4;
		occiwrapper::Int16 flip = occiwrapper::ByteOrder::fromNetwork( norm );
		assert( norm == flip );
	}
	{
		occiwrapper::UInt16 norm = 4;
		occiwrapper::UInt16 flip = occiwrapper::ByteOrder::fromNetwork( norm );
		assert( norm == flip );
	}
	{
		occiwrapper::Int32 norm = 4;
		occiwrapper::Int32 flip = occiwrapper::ByteOrder::fromNetwork( norm );
		assert( norm == flip );
	}
	{
		occiwrapper::UInt32 norm = 4;
		occiwrapper::UInt32 flip = occiwrapper::ByteOrder::fromNetwork( norm );
		assert( norm == flip );
	}
	{
		occiwrapper::Int64 norm = 4;
		occiwrapper::Int64 flip = occiwrapper::ByteOrder::fromNetwork( norm );
		assert( norm == flip );
	}
	{
		occiwrapper::UInt64 norm = 4;
		occiwrapper::UInt64 flip = occiwrapper::ByteOrder::fromNetwork( norm );
		assert( norm == flip );
	}
#else
	//
	// little-endian systems
	//
	{
		occiwrapper::Int16 norm = 4;
		occiwrapper::Int16 flip = occiwrapper::ByteOrder::toNetwork( norm );
		assert( norm != flip );
		flip = occiwrapper::ByteOrder::flipBytes( flip );
		assert( norm == flip );
	}
	{
		occiwrapper::UInt16 norm = 4;
		occiwrapper::UInt16 flip = occiwrapper::ByteOrder::toNetwork( norm );
		assert( norm != flip );
		flip = occiwrapper::ByteOrder::flipBytes( flip );
		assert( norm == flip );
	}
	{
		occiwrapper::Int32 norm = 4;
		occiwrapper::Int32 flip = occiwrapper::ByteOrder::toNetwork( norm );
		assert( norm != flip );
		flip = occiwrapper::ByteOrder::flipBytes( flip );
		assert( norm == flip );
	}
	{
		occiwrapper::UInt32 norm = 4;
		occiwrapper::UInt32 flip = occiwrapper::ByteOrder::toNetwork( norm );
		assert( norm != flip );
		flip = occiwrapper::ByteOrder::flipBytes( flip );
		assert( norm == flip );
	}
	{
		occiwrapper::Int64 norm = 4;
		occiwrapper::Int64 flip = occiwrapper::ByteOrder::toNetwork( norm );
		assert( norm != flip );
		flip = occiwrapper::ByteOrder::flipBytes( flip );
		assert( norm == flip );
	}
	{
		occiwrapper::UInt64 norm = 4;
		occiwrapper::UInt64 flip = occiwrapper::ByteOrder::toNetwork( norm );
		assert( norm != flip );
		flip = occiwrapper::ByteOrder::flipBytes( flip );
		assert( norm == flip );
	}
	{
		occiwrapper::Int16 norm = 4;
		occiwrapper::Int16 flip = occiwrapper::ByteOrder::fromNetwork( norm );
		assert( norm != flip );
		flip = occiwrapper::ByteOrder::flipBytes( flip );
		assert( norm == flip );
	}
	{
		occiwrapper::UInt16 norm = 4;
		occiwrapper::UInt16 flip = occiwrapper::ByteOrder::fromNetwork( norm );
		assert( norm != flip );
		flip = occiwrapper::ByteOrder::flipBytes( flip );
		assert( norm == flip );
	}
	{
		occiwrapper::Int32 norm = 4;
		occiwrapper::Int32 flip = occiwrapper::ByteOrder::fromNetwork( norm );
		assert( norm != flip );
		flip = occiwrapper::ByteOrder::flipBytes( flip );
		assert( norm == flip );
	}
	{
		occiwrapper::UInt32 norm = 4;
		occiwrapper::UInt32 flip = occiwrapper::ByteOrder::fromNetwork( norm );
		assert( norm != flip );
		flip = occiwrapper::ByteOrder::flipBytes( flip );
		assert( norm == flip );
	}
	{
		occiwrapper::Int64 norm = 4;
		occiwrapper::Int64 flip = occiwrapper::ByteOrder::fromNetwork( norm );
		assert( norm != flip );
		flip = occiwrapper::ByteOrder::flipBytes( flip );
		assert( norm == flip );
	}
	{
		occiwrapper::UInt64 norm = 4;
		occiwrapper::UInt64 flip = occiwrapper::ByteOrder::fromNetwork( norm );
		assert( norm != flip );
		flip = occiwrapper::ByteOrder::flipBytes( flip );
		assert( norm == flip );
	}
#endif
}



void TestByteOrderAll()
{
	std::cout << "start to run TestByteOrderFlip" << std::endl;
	TestByteOrderFlip();
	std::cout << "TestByteOrderFlip finishes!" << std::endl;

	std::cout << "start to run TestByteOrderBigEndian" << std::endl;
	TestByteOrderBigEndian();
	std::cout << "TestByteOrderBigEndian finishes!" << std::endl;

	std::cout << "start to run TestByteOrderLittleEndian" << std::endl;
	TestByteOrderLittleEndian();
	std::cout << "TestByteOrderLittleEndian finishes!" << std::endl;
	
	std::cout << "start to run TestByteOrderNetwork" << std::endl;
	TestByteOrderNetwork();
	std::cout << "TestByteOrderNetwork finishes!" << std::endl;
}