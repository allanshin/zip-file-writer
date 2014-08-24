#pragma once

#include <ZipFileWriterInterface.h>
#include <vector>
#include "zip.h"

class ZipFileWriter : public IZipFileWriter
{
	friend IZipFileWriter * CreateZipFile ( LPCTSTR szPathname ) ;
	
private:

	class String : public std::vector<TCHAR>
	{
	private:
		enum { BUF_SIZE = 0x8000 } ;
	protected:
		String ( size_t length )
		{
			resize ( length ) ;
		}
	public:
		String () {}
		String ( const String & r )
		{
			__super::operator = ( r ) ;
		}
		String ( LPCTSTR p )
		{
			if ( p != NULL )
			{
				resize ( lstrlen ( p ) + 1 ) ;
				lstrcpy ( & operator[](0), p ) ;
			}
		}

		String & operator = ( const String & r )
		{
			__super::operator = ( r ) ;

			return * this ;
		}

		operator LPCTSTR () const
		{
			return size () == 0 ? NULL : & operator [] ( 0 ) ;
		}

		int Format ( LPCTSTR fmt, ... )
		{
			resize ( BUF_SIZE ) ;
			va_list args ;
			va_start ( args, fmt ) ;
			int nLen = wvsprintf ( & operator[](0), fmt, args);
			va_end ( args ) ;
			resize ( nLen + 1 ) ;
			return nLen ;
		}

		int Find ( TCHAR what, size_t nStartAt = 0 )
		{
			int nRes = -1 ;

			for ( size_t i = nStartAt ; i < size () && operator[](i) != 0 ; i ++ )
			{
				if ( what == operator[] ( i ) )
				{
					nRes = (int) i ;
					break ;
				}
			}

			return nRes ;
		}

		int ReverseFind ( TCHAR what )
		{
			int nRes = -1 ;

			for ( int i = lstrlen ( * this ) - 1 ; 0 <= i ; i -- )
			{
				if ( what == operator[] ( i ) )
				{
					nRes = (int) i ;
					break ;
				}
			}

			return nRes ;
		}

		String Left ( size_t nLength )
		{
			nLength = min ( nLength + 1, size () ) ;

			String res ( nLength ) ;

			PTCHAR pDst = & res.operator [] ( 0 ) ;

			lstrcpyn ( pDst, * this, (int) nLength ) ;

			return res ;
		}
	} ;


private:	
	HZIP				m_hz ;
	String				m_szFileName ;	
	String				m_szTempName   ;

public:
	ZipFileWriter ( LPCTSTR	szPathname ) ;

	// IZipFileWriter methods
	int AddData ( LPCTSTR			szFileName,
				  bool				bBinary,		// binary (true) or text (false)
				  unsigned long		uDataSize,
				  const PBYTE		pData
				) ;

	int Close () ;	// Makes file persistent
	int Release () ;	// Deletes the file if Close was not called
protected:
	int Commit () ;
} ;