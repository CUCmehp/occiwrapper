#include "OcciWrapper/Common.h"
#include <stdio.h>
#include <sstream>
#include <time.h>
#include <stdlib.h>

#pragma warning( disable : 4996 )

size_t occiwrapper::GetVectorStringMaxLength( const vector< string >& vec )
{
	size_t max_value = 0;
	for( size_t i = 0; i < vec.size(); i++ )
	{
		if( vec[ i ].size() > max_value )
			max_value = vec[ i ].size();
	}
	return max_value;
}

size_t occiwrapper::GetListMaxStringLength(const list< string >& vList )
{
	{
		size_t nMaxValue = 0;
		for( list< string >::const_iterator it = vList.begin(); it != vList.end(); ++ it )
		{
			if( it->size() > nMaxValue )
			{
				nMaxValue = it->size();
			}
		}
		return nMaxValue;
	}
}

oracle::occi::Date occiwrapper::ToDate( const struct tm& tm_value, oracle::occi::Environment* pEnv )
{
	char strBuf[ 256 ];
	sprintf( strBuf, "%d-%d-%d %d:%d:%d", tm_value.tm_year + 1900, tm_value.tm_mon + 1, tm_value.tm_mday, tm_value.tm_hour, tm_value.tm_min, tm_value.tm_sec );
	//stringstream ss;
	//ss << tm_value.tm_year + 1900 << "-" << tm_value.tm_mon + 1 << "-" << tm_value.tm_mday << " " << tm_value.tm_hour << ":" << tm_value.tm_min << ":" << tm_value.tm_sec;
	oracle::occi::Date date;
	date.fromText( strBuf, "YYYY-MM-DD HH24-MI-SS","", pEnv );
	return date;
}

struct tm occiwrapper::GetTm( const oracle::occi::Date& date )
{
	struct tm temp;
	int year;
	occiwrapper::UInt32 mon, day, hour, minute, sec;
	date.getDate( year, mon, day, hour, minute, sec );
	temp.tm_year = year - 1900;
	temp.tm_mon = mon - 1;
	temp.tm_mday = day;
	temp.tm_hour = hour;
	temp.tm_min = minute;
	temp.tm_sec = sec;
	return temp;
}

occiwrapper::OcciDataBuffer::OcciDataBuffer( void* pBuffer, UInt16* pDataLength, Int16* pInd, Int32 nDataBufMaxPerLength, oracle::occi::Type type )
: m_pBuffer( pBuffer )
, m_pDataLength( pDataLength )
, m_nDataBufMaxPerLength( nDataBufMaxPerLength )
, m_pInd( pInd )
, m_eType( type )
{

}

occiwrapper::OcciDataBuffer::OcciDataBuffer()
{
	m_pBuffer =  NULL;
	m_pDataLength = NULL;
	m_pInd = NULL;
}

occiwrapper::OcciDataBuffer::~OcciDataBuffer()
{
	if( m_pBuffer != NULL )
	{
		free( m_pBuffer );
		m_pBuffer = NULL;
	}
	if( m_pDataLength != NULL )
	{
		free( m_pDataLength );
		m_pDataLength = NULL;
	}
	if( m_pInd != NULL )
	{
		free( m_pInd );
		m_pInd = NULL;
	}
}