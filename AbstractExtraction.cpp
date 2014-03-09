#include "AbstractExtraction.h"

occiwrapper::AbstractExtraction::AbstractExtraction()
{
	//this->m_nLimit = nlimit;
	this->m_pExtractor = NULL;
}

occiwrapper::AbstractExtraction::~AbstractExtraction()
{

}

//
//inline void occiwrapper::AbstractExtraction::SetLimit( UInt32 limit )
//{
//	m_nLimit = limit;
//}
//
//inline occiwrapper::UInt32 occiwrapper::AbstractExtraction::GetLimit() const
//{
//	return m_nLimit;
//}