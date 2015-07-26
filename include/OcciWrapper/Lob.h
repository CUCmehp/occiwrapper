#pragma once
#include "Common.h"
#include "LobBase.h"

namespace occiwrapper
{
	class __OCCI_WRAPPER_API Blob : public LobBase
	{
	public:
		/// Creates an empty Blob.
		Blob();

		/// Creates the Blob, content is deep-copied.
		Blob( const std::vector<char>& content );

		/// Creates the Blob by deep-copying pContent.
		Blob(const char* const pContent, std::size_t size);

		/// Creates a Blob from a string.		
		Blob(const std::string& content);

		/// Creates a Blob by copying another one.
		Blob( const Blob& other );

		/// Destroys the Blob.
		~Blob();

		/// Assignment operator.
		Blob& operator = ( const Blob& other );

		/// Compares for equality Blob by value.
		bool operator == ( const Blob& other ) const;

		/// Compares for inequality Blob by value.	
		bool operator != ( const Blob& other ) const;

		/// Swaps the Blob with another one.
		void Swap( Blob& other );

		/// update to db
		void UpdateToOracle();

		/// set occi blob object
		void SetOcciBlob( oracle::occi::Blob& occiBlob );

	private:
		oracle::occi::Blob m_occiBlob;
	};


	class __OCCI_WRAPPER_API Clob : public LobBase
	{
	public:
		/// Creates an empty Blob.
		Clob();

		/// Creates the Blob, content is deep-copied.
		Clob( const std::vector<char>& content );

		/// Creates the Blob by deep-copying pContent.
		Clob(const char* const pContent, std::size_t size);

		/// Creates a Blob from a string.		
		Clob(const std::string& content);

		/// Creates a Blob by copying another one.
		Clob( const Clob& other );

		/// Destroys the Blob.
		~Clob();

		/// Assignment operator.
		Clob& operator = ( const Clob& other );

		/// Compares for equality Blob by value.
		bool operator == ( const Clob& other ) const;

		/// Compares for inequality Blob by value.	
		bool operator != ( const Clob& other ) const;

		/// Swaps the Blob with another one.
		void Swap( Clob& other );

		/// update to db
		void UpdateToOracle();

		/// set occi blob object
		void SetOcciClob( oracle::occi::Clob& occiBlob );

	private:
		oracle::occi::Clob m_occiClob;
	};
}