#include "OcciWrapper/AbstractExtraction.h"

occiwrapper::AbstractExtraction::AbstractExtraction()
{
	this->m_nLimit = Limit::LIMIT_UNLIMITED;
	this->m_pExtractor = NULL;
}

occiwrapper::AbstractExtraction::~AbstractExtraction()
{

}


void occiwrapper::AbstractExtraction::SetLimit( UInt32 limit )
{
	m_nLimit = limit;
}

occiwrapper::UInt32 occiwrapper::AbstractExtraction::GetLimit() const
{
	return m_nLimit;
}