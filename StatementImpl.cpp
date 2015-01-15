#include "OcciWrapper/StatementImpl.h"

occiwrapper::StatementImpl::StatementImpl( oracle::occi::Statement* pOcciStat, shared_ptr< occiwrapper::Connection >& pConn, bool bAutoCommit )
:m_eState( occiwrapper::StatementImpl::ST_INITIALIZED )
,m_objLimit( ( UInt32 )occiwrapper::Limit::LIMIT_UNLIMITED )
,m_nColumnsExtracted( 0 )
,m_bHasExtractor( false )
,m_bAutoCommit( bAutoCommit )
,m_bSuccessed( false )
,m_strErrMsg( "" )
,m_nBatchedNum( 0 )
,m_bBatched( false )
,m_bHasNext( false )
,m_bGotEnoughData( false )
{
	this->m_pOcciStat = pOcciStat;
	this->m_pOcciResult = NULL;
	this->m_pConnection = pConn;
	this->m_objBinder = new occiwrapper::Binder( this->m_pOcciStat, pConn->GetEnvirnment() );
	this->m_pExtrator = new occiwrapper::Extractor( pConn->GetEnvirnment() );
}

occiwrapper::StatementImpl::~StatementImpl()
{
	//first , close ResultSet
	if( m_pOcciResult )
	{
		if( !m_pOcciStat )
		{
			m_strErrMsg = "when StatementImpl constructing, the oracle statement is NULL, but the ResultSet is not closed";
			throw InvalidResultSetException( "Invalid ResultSet" );
		}
		else
		{
			m_pOcciStat->closeResultSet( m_pOcciResult );
		}
	}

	//¹Ø±ÕStatement
	if( m_pOcciStat )
	{
		if( !m_pConnection->TerminateStatement( m_pOcciStat ) )
		{
			m_strErrMsg = "m_pConnection->TerminateStatement( m_pOcciStat ) failed!";
		}
		else
		{
			this->m_pOcciStat = NULL;
		}
	}
	else
	{
		m_strErrMsg = "m_pOcciStat is NULL, when StatementImpl destroyed";
	}

	if( m_objBinder != NULL )
	{
		delete m_objBinder;
		m_objBinder = NULL;
	}
	
	if( m_pExtrator != NULL )
	{
		delete m_pExtrator;
		m_pExtrator = NULL;
	}
}

void occiwrapper::StatementImpl::Reset()
{
	m_eState = ST_RESET;
	Compile();
}

void occiwrapper::StatementImpl::AddBinding( shared_ptr< occiwrapper::AbstractBinding > pBinding )
{
	pBinding->SetBinder( this->m_objBinder );
	this->m_bBatched = pBinding->IsBatchedBind();
	if( m_bBatched )
	{
		this->m_nBatchedNum = pBinding->GetBatchedNum();
	}
	this->m_vBindings.push_back( pBinding );
}

void occiwrapper::StatementImpl::AddExtract( shared_ptr< occiwrapper::AbstractExtraction > pExtraction )
{
	pExtraction->SetExtractor( this->m_pExtrator );
	this->m_vExtractions.push_back( pExtraction );
}

void occiwrapper::StatementImpl::SetExtractionLimit( const occiwrapper::Limit& extrLimit )
{
	this->m_objLimit = extrLimit;
}

bool occiwrapper::StatementImpl::Execute()
{
	try
	{
		ExecuteImpl();

		if( m_bAutoCommit )
			m_pConnection->Commit();

		//get statement out variable
		ReverseBinding();

		//fetch result
		Fetch();

		// clear m_vBindings
		ResetBinding();

		m_bSuccessed = true;
	}
	catch ( OcciSqlException& exc )
	{
		stringstream ss;
		ss << "excute sql( " << ToString().c_str() << " ) error, reason: " << exc.what();
		m_bSuccessed = false;
		m_strErrMsg = ss.str();
	}
	catch ( occiwrapper::LimitException& exc )
	{
		stringstream ss;
		ss << "excute sql( " << ToString().c_str() << " ) error, reason: " << exc.what();
		m_bSuccessed = false;
		m_strErrMsg = ss.str();
	}
	catch( occiwrapper::BindException& exc )
	{
		stringstream ss;
		ss << "excute sql( " << ToString().c_str() << " ) error, reason: " << exc.what();
		m_bSuccessed = false;
		m_strErrMsg = ss.str();
	}

	return m_bSuccessed;
}

bool occiwrapper::StatementImpl::GetSuccessed()
{
	//if( this->m_eState == ST_DONE )
	//{
	//	return m_bSuccessed;
	//}
	//return false;
	return m_bSuccessed;
}

const string occiwrapper::StatementImpl::GetErrMsg()
{
	return this->m_strErrMsg;
}

occiwrapper::StatementImpl::State occiwrapper::StatementImpl::GetState() const
{
	return this->m_eState;
}

int occiwrapper::StatementImpl::GetExtractionMinLimit()
{
	int nMinValue = numeric_limits< int >::max();
	for( size_t i = 0; i < m_vExtractions.size(); ++ i )
	{
		if( m_vExtractions[ i ]->GetLimit() == Limit::LIMIT_UNLIMITED )
		{
			continue;
		}
		else
		{
			if( m_vExtractions[ i ]->GetLimit() < ( occiwrapper::UInt32 )nMinValue )
			{
				nMinValue = m_vExtractions[ i ]->GetLimit();
			}
		}
	}
	return nMinValue;
}

void occiwrapper::StatementImpl::Compile()
{
	if ( m_eState == ST_INITIALIZED )
	{
		this->m_pOcciStat->setSQL( ToString() );
		m_eState = ST_COMPILED;

		this->m_bHasExtractor = !m_vExtractions.empty();
		// if has extractor, set limit from extractions.
		if( m_bHasExtractor )
		{
			int nLimitValue = this->m_objLimit.value() == Limit::LIMIT_UNLIMITED ? numeric_limits< int >::max() : this->m_objLimit.value();
			int nExtractionMinLimit = GetExtractionMinLimit();
			int nMinLimit = min( nLimitValue, nExtractionMinLimit );
			this->SetExtractionLimit( nMinLimit );
		}

	}
	else if ( m_eState == ST_RESET)
	{
		m_eState = ST_COMPILED;
	}
}

void occiwrapper::StatementImpl::BindImpl()
{
	vector< shared_ptr< AbstractBinding > > binds = GetBindings();
	size_t pos = 1;
	vector< shared_ptr< AbstractBinding > >::iterator it = binds.begin();
	vector< shared_ptr< AbstractBinding > >::iterator itEnd = binds.end();

	for (; it != itEnd && (*it)->CanBind(); ++it)
	{
		if( this->m_bBatched )
		{
			if( ( *it )->GetBatchedNum() != m_nBatchedNum )
				throw BindException( "Batched insert, buf buffer size is not the same. " );
		}

		(*it)->Bind(pos);
		pos += (*it)->NumOfColumnsHandled();
	}
}

void occiwrapper::StatementImpl::Bind()
{
	if( m_eState == ST_COMPILED )
	{
		//do binding here
		BindImpl();

		m_eState = ST_BOUND;
	}
}

void occiwrapper::StatementImpl::ExtractImpl()
{
	vector< shared_ptr< AbstractExtraction > > extracts = GetExtractions();
	size_t pos = 1;
	vector< shared_ptr< AbstractExtraction > >::iterator it = extracts.begin();
	vector< shared_ptr< AbstractExtraction > >::iterator itEnd = extracts.end();

	for( ; it != itEnd; ++it )
	{
		( *it )->Extract( pos );
		pos += ( *it )->NumOfColumnsHandled();
	}
}

void occiwrapper::StatementImpl::Extract()
{
	if( m_eState == ST_BOUND )
	{
		//do extraction here
		ExtractImpl();
	}
}

void occiwrapper::StatementImpl::Fetch()
{
	if( m_eState == ST_BOUND )
	{
		FetchImpl();
		if( !m_bHasNext || m_bGotEnoughData )
		{
			m_eState = ST_DONE;
		}
	}
}

void occiwrapper::StatementImpl::FetchImpl()
{
	vector< shared_ptr< OcciDataBuffer > >& pVecDataBufs = this->m_pExtrator->GetExatractDataBuffers();
	try
	{
		UInt32 nNextBatchedCount = nBatchedRetrieveOnceCount < m_objLimit.value() ? nBatchedRetrieveOnceCount : m_objLimit.value();
		UInt32 nTotalBatchedCount = 0;
		oracle::occi::ResultSet::Status eState = oracle::occi::ResultSet::DATA_AVAILABLE;
		while( ( eState = this->m_pOcciResult->next( nNextBatchedCount ) ) != oracle::occi::ResultSet::END_OF_FETCH )
		{
			int nRowFetched = m_pOcciResult->getNumArrayRows();
			size_t pos = 1;
			for( size_t i = 0; i < this->m_vExtractions.size(); ++ i )
			{
				m_vExtractions[ i ]->Fetch( pos, nRowFetched );
				pos += m_vExtractions[ i ]->NumOfColumnsHandled();
			}
			nTotalBatchedCount += nRowFetched;

			if( nTotalBatchedCount + nBatchedRetrieveOnceCount > this->m_objLimit.value() )
			{
				nNextBatchedCount = this->m_objLimit.value() - nTotalBatchedCount;
			}
			else
			{
				nNextBatchedCount = nBatchedRetrieveOnceCount;
			}

			// if has get enough data, then break
			if( nTotalBatchedCount >= this->m_objLimit.value() )
			{
				m_bGotEnoughData = true;
				break;
			}
			else
			{
				m_bGotEnoughData = false;
			}
		}

		// set m_bHasNext flag
		if( eState == oracle::occi::ResultSet::END_OF_FETCH )
		{
			m_bGotEnoughData = true;
			m_bHasNext = false;
		}
		else
		{
			m_bHasNext = true;
		}
		
	}
	catch( oracle::occi::SQLException& exc )
	{
		throw OcciSqlException( exc.what() );
	}
	catch( std::exception& exc )
	{
		throw exc;
	}
	catch( ... )
	{
		throw OcciSqlException( "occi unknown exception when executeWithoutLimit" );
	}
}

void occiwrapper::StatementImpl::ReverseBinding()
{
	if( m_eState != ST_DONE )
		return;
	vector< shared_ptr< AbstractBinding > > binds = GetBindings();
	size_t pos = 1;
	vector< shared_ptr< AbstractBinding > >::iterator it = binds.begin();
	vector< shared_ptr< AbstractBinding > >::iterator itEnd = binds.end();

	for (; it != itEnd; ++it)
	{
		if( ( *it )->IsOut() )
		{
			if( this->m_bBatched )
			{
				throw BindException( "Batched binding can not registered as out variable!" );
			}
			(*it)->ReverseBind(pos);
		}
		pos += (*it)->NumOfColumnsHandled();
	}
}

vector< shared_ptr< occiwrapper::AbstractBinding > >& occiwrapper::StatementImpl::GetBindings()
{
	return this->m_vBindings;
}

vector< shared_ptr< occiwrapper::AbstractExtraction > >& occiwrapper::StatementImpl::GetExtractions()
{
	return this->m_vExtractions;
}

void occiwrapper::StatementImpl::ResetBinding()
{
	this->m_vBindings.clear();
}

bool occiwrapper::StatementImpl::HasNext()
{
	return m_bHasNext;
}

void occiwrapper::StatementImpl::ExecuteImpl()
{
	UInt32 count = 0;
	assert( m_eState != ST_DONE );
	Compile();

	Bind();

	try
	{
		if( !this->m_bHasExtractor )
		{
			if( !m_bBatched )
			{
				m_pOcciStat->execute();
			}
			else
			{
				m_pOcciStat->executeArrayUpdate( this->m_nBatchedNum );
			}
			m_eState = ST_DONE;
		}
		// execute query
		else
		{
			if( !m_bHasNext )
			{
				m_pOcciResult = m_pOcciStat->executeQuery();
				this->m_pExtrator->SetOcciResultSet( m_pOcciResult );
				Extract();
			}
		}
	}
	catch( oracle::occi::SQLException& exc )
	{
		throw OcciSqlException( exc.what() );
	}
	catch( ... )
	{
		throw OcciSqlException( "occi unknown exception when ExecuteImpl" );
	}
}

