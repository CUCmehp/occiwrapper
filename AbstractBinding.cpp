#include "AbstractBinding.h"


occiwrapper::AbstractBinding::AbstractBinding()
	 : m_pBinder( NULL )
{

}

occiwrapper::AbstractBinding::~AbstractBinding()
{

}

void occiwrapper::AbstractBinding::SetBinder( occiwrapper::AbstractBinder* pBinder )
{
	m_pBinder = pBinder;
}
