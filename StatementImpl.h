#pragma once
#include "Common.h"
#include "occi.h"
#include "Connection.h"
#include <sstream>
#include "Limit.h"
#include "Exception.h"
#include <assert.h>
#include "Binding.h"
#include "Binder.h"
#include "AbstractExtraction.h"
#include "Extraction.h"
#include "AbstractExtractor.h"
#include "Extractor.h"

namespace occiwrapper
{
	// forward declaration
	class Extractor;

	class __OCCI_WRAPPER_API StatementImpl
	{
	public:
		enum State
		{
			ST_INITIALIZED,
			ST_COMPILED,
			ST_BOUND,
			ST_DONE,
			ST_RESET
		};

		/***
		*	@brief: create StatementImpl
		*	@add by CUCmehp
		*	@parameters:
		*		pOcciStat: occi statement
		*		pConn: pointer to Connection
		*		bAutoCommit: auto commit or not
		*/
		StatementImpl( oracle::occi::Statement* pOcciStat, shared_ptr< Connection >& pConn, bool bAutoCommit );

		/***
		*	@brief: destroyed StatementImpl
		*/
		~StatementImpl();

		/***
		*	@brief: Appends SQl statement (fragments).
		*	@add by CUCmehp
		*/
		template <typename T> 
		void Add(const T& t)
		{
			m_strStream << t;
		}
		
		/***
		*	@brief: Resets the statement, so that we can reuse all bindings and re-execute again.
		*	@add by CUCmehp.
		*/
		void Reset();

		/***
		*	@brief: Registers the Binding at the StatementImpl.
		*	@add by CUCmehp.
		*	@parameters:
		*		pBinding: pointer to the binding holder.
		*/
		void AddBinding( shared_ptr< AbstractBinding > pBinding );

		/***
		*	@brief: Registers objects used for extracting data at the StatementImpl.
		*	@add by CUCmehp
		*	@parameters:
		*		pExtraction: add a extraction.
		*/
		void AddExtract( shared_ptr< AbstractExtraction > pExtraction );

		/***
		*	@brief: Changes the extractionLimit to extrLimit. Per default no limit (EXTRACT_UNLIMITED) is set.
		*	@add by CUCmehp
		*	@parameters:
		*		extrLimit: extract limit
		*/
		void SetExtractionLimit( const Limit& extrLimit );


		// Create a string version of the SQL statement.
		inline string ToString() const;

		/***
		*	@brief: execute a statement
		*	@add by CUCmehp
		*	@since: 2012-5-5
		*	@return: execute success or not
		*/
		bool Execute();

		/***
		*	@brief: get succeeded.
		*	@add by CUCmehp
		*	@since: 2012-5-5
		*	@return: execute success or not
		*/
		bool GetSuccessed();

		/***
		*	@brief: get error message
		*	@add by CUCmehp
		*/
		const string GetErrMsg();

		//void reset();
		/// Resets the statement, so that we can reuse all bindings and re-execute again.

		/***
		*	@brief: Returns the state of the Statement.
		*	@add by CUCmehp
		*/
		State GetState() const;
		
	private:
		StatementImpl();
		StatementImpl(const StatementImpl& stmt);
		StatementImpl& operator = (const StatementImpl& stmt);

		/***
		*	@brief:Compiles the statement, if not yet compiled. doesn't bind yet
		*	@add by CUCmehp
		*/
		void Compile();

		/***
		*	@brief: bind operation.
		*	@add by CUCmehp
		*/
		void BindImpl();

		/***
		*	@brief: Binds the statement, if not yet bound.
		*	@add by CUCmehp
		*/
		void Bind();

		/***
		*	@brief: reset binding
		*/
		void ResetBinding();

		/***
		*	@brief: extract operation implementation
		*	@add by CUCmehp
		*/
		void ExtractImpl();

		/***
		*	@brief: extract
		*/
		void Extract();

		/***
		*	@brief: fetch
		*/
		void Fetch();

		/***
		*	@brief: fetch implementation
		*/
		void FetchImpl();

		/***
		*	@brief: Executes with an upper limit set.
		*/
		void ExecuteWithLimit();

		/***
		*	@brief: Executes without upper limit set.
		*/
		void ExecuteWithoutLimit();

		/***
		*	@brief: reverse binding is getting result from database for out parameters
		*/
		void ReverseBinding();

		/***
		*	@brief: get all bindings of this statement.
		*/
		vector< shared_ptr< AbstractBinding > >& GetBindings();

		/***
		*	@brief: get all extractions of this statement.
		*/
		vector< shared_ptr< AbstractExtraction > >& GetExtractions();

		/***
		*	@brief: if the query has next data
		*/
		bool HasNext();

	private:
		oracle::occi::Statement*							m_pOcciStat;
		shared_ptr< Connection >							m_pConnection;
		oracle::occi::ResultSet*							m_pOcciResult;
		stringstream										m_strStream;
		State												m_eState;
		Limit												m_objLimit;
		int													m_nColumnsExtracted;
		Binder*												m_objBinder;						// bind parameters
		vector< shared_ptr< AbstractBinding > >				m_vBindings;
		bool												m_bBatched;							// using for batched insert
		size_t												m_nBatchedNum;						// using for batched insert
		Extractor*											m_pExtrator;						// extraction parameters
		vector< shared_ptr< AbstractExtraction > >			m_vExtractions;
		bool												m_bHasExtractor;
		bool												m_bHasNext;							// next fetch will get data
		bool												m_bAutoCommit;
		bool												m_bSuccessed;						//execute succeed or not
		string												m_strErrMsg;						// if failed, saved error message

		friend class Statement; 
	};

	inline string occiwrapper::StatementImpl::ToString() const
	{
		return m_strStream.str();
	}
}
