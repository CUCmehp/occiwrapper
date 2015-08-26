#pragma once
#include "OcciWrapper/Common.h"
#include "occi.h"
#include "OcciWrapper/StatementImpl.h"
#include <functional>
#include "OcciWrapper/AbstractBinding.h"

using occiwrapper::use;
using occiwrapper::batched_use;

namespace occiwrapper
{
	// forward declaration
	class Session;

	/****
	*	@brief: A Statement is used to execute SQL statements. 
	*			It does not contain code of its own.
	*			Its main purpose is to forward calls to the concrete StatementImpl stored inside.
	*/
	class Statement
	{
	public:
		class Manipulator 
			: public unary_function< void, Statement >
		{
		public:
			void operator()( Statement& statement )
			{
				statement.Execute();
			}
		};

		Statement( shared_ptr< StatementImpl > pImp )
			:_executed( false )
		{
			this->m_pImp = pImp;
		}

		~Statement()
		{

		}

		/* 
		*	Creates the Statement for the given Session.
		*
		*	The following:
		*
		*		Statement stmt(sess);
		*		stmt << "SELECT * FROM Table", ...
		*
		*	is equivalent to:
		*		Statement stmt(sess << "SELECT * FROM Table", ...);
		*
		*	but in some cases better readable.
		*/
		explicit Statement( Session& session );

		template< typename T>
		Statement& operator << ( const T& t )
		{
			if( m_pImp != NULL )
			{
				m_pImp->Add( t );
			}
			return *this;
		}

		// Handles manipulators, such as now.
		Statement& operator , (Manipulator manip)
		{
			manip( *this );
			return *this;
		}

		Statement& operator , ( bool& bSuccessed )
		{
			if( this->m_pImp != NULL )
			{
				bSuccessed = this->m_pImp->GetSuccessed();
			}
			else
			{
				bSuccessed = false;
			}
			return *this;
		}

		Statement& operator , ( string& strErrorMsg )
		{
			if( this->m_pImp != NULL )
			{
				strErrorMsg = this->m_pImp->GetErrMsg();
			}
			else
			{
				strErrorMsg = "Statement is invalid, please check db connection!";
			}
			return *this;
		}

		// Registers the Binding at the Statement
		Statement& operator , (AbstractBinding* info)
		{
			if( m_pImp != NULL )
			{
				this->m_pImp->AddBinding( shared_ptr< AbstractBinding >( info ) );
			}
			return *this;
		}

		// Registers the Binding at the Statement
		Statement& AddBinding( AbstractBinding* info )
		{
			if( m_pImp != NULL )
			{
				this->m_pImp->AddBinding( shared_ptr< AbstractBinding >( info ) );
			}
			return *this;
		}
		
		// Registers objects used for extracting data at the Statement.
		Statement& operator , ( AbstractExtraction* extract )
		{
			if( m_pImp != NULL )
			{
				this->m_pImp->AddExtract( shared_ptr< AbstractExtraction >( extract ) );
			}
			return *this;
		}

		// Registers objects used for extracting data at the Statement.
		Statement& AddExtract( AbstractExtraction* extract )
		{
			if( m_pImp != NULL )
			{
				this->m_pImp->AddExtract( shared_ptr< AbstractExtraction >( extract ) );
			}
			return *this;
		}


		// Sets a limit on the maximum number of rows a select is allowed to return.
		// Set per default to Limit::LIMIT_UNLIMITED which disables the limit.
		Statement& operator , (const Limit& extrLimit)
		{
			if( m_pImp != NULL )
			{
				this->m_pImp->SetExtractionLimit( extrLimit );
			}
			return *this;
		}
		// Sets a limit on the maximum number of rows a select is allowed to return.
		// Set per default to Limit::LIMIT_UNLIMITED which disables the limit.
		Statement& SetExtractionLimit(const Limit& extrLimit)
		{
			if( m_pImp != NULL )
			{
				this->m_pImp->SetExtractionLimit( extrLimit );
			}
			return *this;
		}

		// Creates a string from the accumulated SQL statement
		inline std::string ToString() const
		{
			if( m_pImp != NULL )
			{
				return this->m_pImp->ToString();
			}
			else
			{
				return "";
			}
		}

		inline bool Execute()
		{
			if( m_pImp == NULL )
			{
				return false;
			}

			if( Done() )
			{
				m_pImp->Reset();
			}
			_executed = true;
			this->m_pImp->Execute();
			return m_pImp->GetSuccessed();
		}

		// Returns if the statement was completely executed or if a previously set limit stopped it
		// and there is more work to do. When no limit is set, it will always - after calling execute() - return true.
		bool Done()
		{
			if( m_pImp == NULL )
			{
				return false;
			}
			else
			{
				return m_pImp->GetState() == StatementImpl::ST_DONE;
			}
		}

		// check if the query statement has next data
		bool HasNext()
		{
			if( m_pImp == NULL )
			{
				return false;
			}
			else
			{
				return m_pImp->HasNext();
			}
		}

		string GetErrMsg()
		{
			return m_pImp->GetErrMsg();
		}

	private:
		shared_ptr< StatementImpl > m_pImp;
		bool _executed;
	};


#define now occiwrapper::Statement::Manipulator()
}
