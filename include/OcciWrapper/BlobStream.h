#pragma once
#include "OcciWrapper/Common.h"
#include "OcciWrapper/UnbufferedStreamBuf.h"
#include "OcciWrapper/LobBase.h"
#include <istream>
#include <ostream>


namespace occiwrapper
{
	/// This is the streambuf class used for reading from and writing to a Blob.
	class __OCCI_WRAPPER_API BlobStreamBuf
		: public UnbufferedStreamBuf
	{
	public:	
		/// Creates BlobStreamBuf.
		BlobStreamBuf( LobBase& blob);
		
		/// Destroys BlobStreamBuf.
		~BlobStreamBuf();
		

	protected:
		int_type readFromDevice();
		int_type writeToDevice(char c);

	private:
		LobBase&          _blob;
		LobBase::Iterator _it;
	};


	/// The base class for BLOBInputStream and
	/// BLOBOutputStream.
	///
	/// This class is needed to ensure the correct initialization
	/// order of the stream buffer and base classes.
	class __OCCI_WRAPPER_API BlobIOS: public virtual std::ios
	{
	public:
		/// Creates the BlobIOS with the given Blob.
		BlobIOS( LobBase& blob, openmode mode );
		
		/// Destroys the BlobIOS.
		~BlobIOS();
		
		/// Returns a pointer to the internal BLOBStreamBuf.
		BlobStreamBuf* rdbuf();
		
	protected:
		BlobStreamBuf _buf;
	};

	/// An output stream for writing to a Blob.
	class __OCCI_WRAPPER_API LobBaseOutputStream
		: public BlobIOS, public std::ostream
	{
	public:
		/// Creates the BLOBOutputStream with the given Blob.
		LobBaseOutputStream( LobBase& blob );
		
		/// Destroys the BLOBOutputStream.
		~LobBaseOutputStream();
	};

	/// An input stream for reading from a Blob.
	class __OCCI_WRAPPER_API LobBaseInputStream
		: public BlobIOS, public std::istream
		
	{
	public:
		/// Creates the BLOBInputStream with the given Blob.
		LobBaseInputStream( LobBase& blob );
		
		/// Destroys the BLOBInputStream.
		~LobBaseInputStream();
	};
}

