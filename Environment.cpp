#include "OcciWrapper/Environment.h"
#include <iostream>
using namespace std;

shared_ptr< occiwrapper::Environment > occiwrapper::Environment::CreateEnvironment( string strCharSet /*= ""*/, string strNCharSet /*= "" */ )
{
	return shared_ptr< occiwrapper::Environment >( new occiwrapper::Environment( strCharSet, strNCharSet ) );
}

occiwrapper::Environment::~Environment()
{
	try
	{
		if( m_pOcciEnviroment && m_eValidity == VALID )
		{
			oracle::occi::Environment::terminateEnvironment( m_pOcciEnviroment );
			m_pOcciEnviroment = NULL;
		}
		this->m_eValidity = INVALID;
	}
	catch( oracle::occi::SQLException& exc )
	{
		cerr << "exception in ~Environment" << exc.what() << endl;
	}
	catch( ... )
	{
		cerr << "exception in ~Environment, unknown exception" << endl;
	}
}

oracle::occi::Environment* occiwrapper::Environment::GetEnvirnment()
{
	return this->m_pOcciEnviroment;
}

occiwrapper::Environment::Environment( string strCharSet, string strNCharSet )
{
	try
	{
		if( !strCharSet.empty() && !strNCharSet.empty() )
		{
			this->m_pOcciEnviroment = oracle::occi::Environment::createEnvironment( strCharSet, strNCharSet, oracle::occi::Environment::THREADED_UNMUTEXED );
		}
		else
		{
			this->m_pOcciEnviroment = oracle::occi::Environment::createEnvironment( oracle::occi::Environment::THREADED_UNMUTEXED );
		}
		
		this->m_eValidity = this->m_pOcciEnviroment != NULL ? VALID : INVALID;
	}
	catch( oracle::occi::SQLException& exc )
	{
		cerr << "exception in ~Environment" << exc.what() << endl;
	}
	catch( ... )
	{
		cerr << "exception in ~Environment, unknown exception" << endl;
	}
}