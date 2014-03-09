#pragma once
#include "Common.h"
#include "occi.h"
#include "StatementImpl.h"
#include <functional>
#include "AbstractBinding.h"

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
			this->pImp = pImp;
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
			pImp->Add( t );
			return *this;
		}

		// Handles manipulators, such as now.
		Statement& operator , (Manipulator manip)
		{
			manip( *this );
			return *this;
		}

		Statement& operator , ( bool& successed )
		{
			successed = this->pImp->GetSuccessed();
			return *this;
		}

		Statement& operator , ( string& errorMsg )
		{
			errorMsg = this->pImp->GetErrMsg();
			return *this;
		}

		// Registers the Binding at the Statement
		Statement& operator , (AbstractBinding* info)
		{
			this->pImp->AddBinding( shared_ptr< AbstractBinding >( info ) );
			return *this;
		}
		
		// Registers objects used for extracting data at the Statement.
		Statement& operator , ( AbstractExtraction* extract )
		{
			this->pImp->AddExtract( shared_ptr< AbstractExtraction >( extract ) );
			return *this;
		}


		// Sets a limit on the maximum number of rows a select is allowed to return.
		// Set per default to Limit::LIMIT_UNLIMITED which disables the limit.
		Statement& operator , (const Limit& extrLimit)
		{
			this->pImp->SetExtractionLimit( extrLimit );
			return *this;
		}

		// Creates a string from the accumulated SQL statement
		inline std::string ToString() const
		{
			return this->pImp->ToString();
		}

		inline bool Execute()
		{
			if( Done() )
			{
				pImp->Reset();
			}
			_executed = true;
			this->pImp->Execute();
			return pImp->GetSuccessed();
		}

		// Returns if the statement was completely executed or if a previously set limit stopped it
		// and there is more work to do. When no limit is set, it will always - after calling execute() - return true.
		bool Done()
		{
			return pImp->GetState() == StatementImpl::ST_DONE;
		}

		// check if the query statement has next data
		bool HasNext()
		{
			return pImp->HasNext();
		}

	private:
		shared_ptr< StatementImpl > pImp;
		bool _executed;
	};


#define now occiwrapper::Statement::Manipulator()
}
