#pragma once
#include "OcciWrapper/Common.h"
#include <vector>

#pragma warning( disable : 4251 )

namespace occiwrapper
{

/// Representation of a Binary Large OBject.
///
/// A BLOB can hold arbitrary binary data.
/// The maximum size depends on the underlying database.
///
/// The BLOBInputStream and BLOBOutputStream classes provide
/// a convenient way to access the data in a BLOB.
class __OCCI_WRAPPER_API LobBase
{
public:
	typedef std::vector<char>::const_iterator Iterator;

	/// Creates an empty Blob.
	LobBase();
		
	/// Creates the Blob, content is deep-copied.
	LobBase( const std::vector<char>& content );
		
	/// Creates the Blob by deep-copying pContent.
	LobBase(const char* const pContent, std::size_t size);
		
	/// Creates a Blob from a string.		
	LobBase(const std::string& content);
		
	/// Creates a Blob by copying another one.
	LobBase( const LobBase& other );
		
	/// Destroys the Blob.
	~LobBase();
		
	/// Assignment operator.
	LobBase& operator = ( const LobBase& other );
		
	/// Compares for equality Blob by value.
	bool operator == ( const LobBase& other ) const;
		
	/// Compares for inequality Blob by value.	
	bool operator != ( const LobBase& other ) const;
		
	/// Swaps the Blob with another one.
	void Swap( LobBase& other );
		
	/// Returns the content.
	const std::vector<char>& content() const;
		
	/// Returns the raw content.
	///
	/// If the BLOB is empty, returns NULL.
	const char* RawContent() const;
		
	/// Assigns raw content to internal storage.
	void AssignRaw(const char* pChar, std::size_t count);
		
	/// Assigns raw content to internal storage.
	void AppendRaw(const char* pChar, std::size_t count);
		
	/// Clears the content of the Blob.
	/// If doCompact is true, trims the excess capacity.
	void Clear( bool doCompact = false );
		
	/// Trims the internal storage excess capacity.
	void Compact();
		

	Iterator begin() const;
	Iterator end() const;

	/// Returns the size of the Blob in bytes.
	std::size_t size() const;

protected:
	shared_ptr< std::vector<char> > _pContent;
	friend class BlobStreamBuf;
};


//
// inlines
//
inline const std::vector<char>& LobBase::content() const
{
	return *_pContent;
}


inline const char* LobBase::RawContent() const
{
	if( _pContent->empty() )
		return 0;
	else
		return &(*_pContent)[0];
}


inline std::size_t LobBase::size() const
{
	return _pContent->size();
}


inline bool LobBase::operator == ( const LobBase& other ) const
{
	return *_pContent == *other._pContent;
}


inline bool LobBase::operator != ( const LobBase& other ) const
{
	return *_pContent != *other._pContent;
}


inline LobBase::Iterator LobBase::begin() const
{
	return _pContent->begin();
}


inline LobBase::Iterator LobBase::end() const
{
	return _pContent->end();
}


inline void LobBase::AssignRaw(const char* pChar, std::size_t count)
{
	LobBase tmp( pChar, count );
	Swap( tmp );
}


inline void LobBase::AppendRaw( const char* pChar, std::size_t count )
{
	_pContent->insert( _pContent->end(), pChar, pChar+count );
}


inline void LobBase::Swap( LobBase& other )
{
	using std::swap;
	swap( _pContent, other._pContent );
}


inline void LobBase::Clear( bool doCompact )
{
	_pContent->clear();
	if ( doCompact ) 
	{
		Compact();
	}
}


inline void LobBase::Compact()
{
	std::vector<char>( *_pContent ).swap( *_pContent );
}


} // namespace occiwrapper
