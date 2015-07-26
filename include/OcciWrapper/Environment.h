#pragma once
#include "OcciWrapper/Common.h"
#include "OcciWrapper/ConnectionInfo.h"

/***
*	@add by CUCmehp, since 2011-1-6
*	@brief: wrapper for occi::Environment
*/
namespace occiwrapper
{
	class __OCCI_WRAPPER_API Environment 
		//: public ValidatedObject
	{
	public:
		/***
		*	@brief: factory funciton to create Environment
		*/
		static shared_ptr< Environment > CreateEnvironment( string strCharSet = "", string strNCharSet = "" );

		/***
		*	@brief: destory Environment
		*/
		virtual ~Environment();

		/***
		*	@brief: get occi environment
		*/
		oracle::occi::Environment* GetEnvirnment();

	private:
		/***
		*	@brief: create Environment
		*/
		Environment( string strCharSet, string strNCharSet );

	private:
		oracle::occi::Environment*	m_pOcciEnviroment;
		Validity					m_eValidity;

		friend class Connection;
	};

}