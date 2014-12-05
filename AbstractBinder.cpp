#include "OcciWrapper/AbstractBinder.h"

occiwrapper::AbstractBinder::AbstractBinder()
{

}

occiwrapper::AbstractBinder::~AbstractBinder()
{

}

void occiwrapper::AbstractBinder::SetDirection( const DataDirection_E& eDirection )
{
	this->m_eDataDirection = eDirection;
}

bool occiwrapper::AbstractBinder::IsOut()
{
	return this->m_eDataDirection == PAR_OUT || this->m_eDataDirection == PAR_IN_OUT;
}

bool occiwrapper::AbstractBinder::IsIn()
{
	return this->m_eDataDirection == PAR_IN || this->m_eDataDirection == PAR_IN_OUT;
}