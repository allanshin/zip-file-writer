// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ZipFileWriterInterface.h"

int _tmain(int argc, _TCHAR* argv[])
{
	IZipFileWriter * pWriter = CreateZipFile ( TEXT ( "c:\\MyZipFile.zip" ) ) ;

	pWriter -> AddData ( TEXT ( "test.txt" ), 
						 false, 
						 sizeof ( argv[0][0] ) * ( 1 + lstrlen ( argv[0] ) ),
						 (const PBYTE) argv[0]
					   ) ;

					   pWriter -> AddData ( TEXT ( "subdir1\\testsub1.txt" ), 
						 false, 
						 sizeof ( argv[0][0] ) * ( 1 + lstrlen ( argv[0] ) ),
						 (const PBYTE) argv[0]
					   ) ;

					   pWriter -> AddData ( TEXT ( "subdir1\\testsub2.txt" ), 
						 false, 
						 sizeof ( argv[0][0] ) * ( 1 + lstrlen ( argv[0] ) ),
						 (const PBYTE) argv[0]
					   ) ;

						pWriter -> AddData ( TEXT ( "subdir1\\subdir2\\testsub3.txt" ), 
						 false, 
						 sizeof ( argv[0][0] ) * ( 1 + lstrlen ( argv[0] ) ),
						 (const PBYTE) argv[0]
					   ) ;


					   
	pWriter -> Close () ;
	pWriter -> Release () ;
	return 0;
}

