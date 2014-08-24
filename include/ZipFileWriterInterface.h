#pragma once

class IZipFileWriter
{
public:
	// Method AddData compresses provided data block and stores it in the 
	// zip file under specified name
	virtual int AddData ( LPCTSTR			szFileName,
						  bool				bBinary,		// binary (true) or text (false)
						  unsigned long		uDataSize,
						  const PBYTE		pData
						) = NULL ;

	virtual int Close () = NULL ;	// Makes file persistent
	virtual int Release () = NULL ;	// Deletes the file if Close was not called
} ;

extern "C"
IZipFileWriter * CreateZipFile ( LPCTSTR szPathname ) ;
