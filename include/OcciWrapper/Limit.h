#pragma once
#include "OcciWrapper/Common.h"

namespace occiwrapper
{
	/***
	*	@brief: Limit stores information how many rows a query should return.
	*/
	class __OCCI_WRAPPER_API Limit
	{
	public:
		enum
		{
			LIMIT_UNLIMITED = 0xffffffffu
		};

		/***
		*	@brief: Creates the Limit. 
		*/
		Limit( UInt32 nValue );


		/***
		*	@brief: Destroys the Limit.
		*/
		~Limit();

		/***
		*	@brief: Returns the value of the limit
		*/
		inline UInt32 value() const;

	private:
		UInt32		 m_nValue;
	};

	template< typename T > Limit limit( T lim )
	{
		return Limit( UInt32( lim ) );
	}

	inline occiwrapper::UInt32 occiwrapper::Limit::value() const
	{
		return m_nValue;
	}
}

#define limit( x ) occiwrapper::limit( x )
