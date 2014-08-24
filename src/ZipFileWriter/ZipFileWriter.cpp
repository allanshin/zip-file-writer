#include "stdafx.h"
#include "ZipFileWriter.h"

//=============================================================================
IZipFileWriter * CreateZipFile ( LPCTSTR szPathname )
{
	IZipFileWriter * pRes = NULL ;

	try
	{
		pRes = new ZipFileWriter ( szPathname ) ;
	}
	catch ( LONG dwErr )
	{
		ASSERT ( FALSE ) ;
#ifdef	_DEBUG
		ZipFileWriter::String err ;
		err.Format ( TEXT ( "Error 0x%08X (%d) in 'new ZipFileWriter ( %s )'\n" ), dwErr, dwErr, szPathname ) ;
		OutputDebugString ( err ) ;
#endif
	}
	catch (...)
	{
		ASSERT ( FALSE ) ;
#ifdef	_DEBUG
		ZipFileWriter::String err ;
		err.Format ( TEXT ( "Unknown Exception in 'new ZipFileWriter ( %s )'\n" ), szPathname ) ;
		OutputDebugString ( err ) ;
#endif
	}

	return pRes ;
}

//=============================================================================
ZipFileWriter::ZipFileWriter ( LPCTSTR szPathname )
: m_hz(NULL), m_szFileName ( szPathname )
{
	LONG dwErr = 0 ;

	// Create temp file in the same directory as ZIP file
	int nSlashPos = m_szFileName.ReverseFind ( '\\' ) ;

	if ( nSlashPos > 0 )
	{
		m_szTempName = m_szFileName.Left ( nSlashPos - 1 ) ;
	}
	else
	{
	}
	m_szTempName = TEXT ( "." ) ;

	TCHAR szTempFile[MAX_PATH] ;
	GetTempFileName ( m_szTempName, TEXT ( "zfw" ), 0, szTempFile ) ;

	m_szTempName = szTempFile ;

	m_hz = CreateZip( m_szTempName ,0);
}
//-----------------------------------------------------------------------------
int ZipFileWriter::Commit ()
{
	int nRes = ERROR_SUCCESS ;
	
	if ( m_hz != NULL )
	{		
		nRes = CloseZip(m_hz);
	}

	return nRes ;
}
//-----------------------------------------------------------------------------
int ZipFileWriter::Close()
{
	int nRes = Commit () ;

	if ( nRes == ERROR_SUCCESS )
	{
		nRes = DeleteFile ( m_szFileName ) ;

		if ( nRes == ERROR_SUCCESS || nRes == ERROR_FILE_NOT_FOUND )
		{
			nRes = MoveFile ( m_szTempName, m_szFileName ) ;
		}
	}

	return nRes ;
}
//-----------------------------------------------------------------------------
int ZipFileWriter::Release()
{
	Commit () ;	// Clean up memory

	return DeleteFile ( m_szTempName ) ;
}
//-----------------------------------------------------------------------------
int ZipFileWriter::AddData ( LPCTSTR		szFileName, 
						     bool			bBinary, 
							 unsigned long	uDataSize, 
							 const PBYTE	pData 
						   )
{
	int nRes = -1 ;

	if ( m_hz != NULL )
	{
		ZipAdd(m_hz, szFileName, pData, uDataSize);		
		nRes = GetLastError () ;
	}

	return nRes ;
}
//=============================================================================
