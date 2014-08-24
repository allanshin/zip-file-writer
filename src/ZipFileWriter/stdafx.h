#pragma once

#ifdef _WIN32
	#include <Windows.h>
	#include <tchar.h>
	#pragma warning ( disable: 4996 )
#endif

#include <stdio.h>
#include <assert.h>
#define ASSERT(x) assert(x)

#ifndef SIZEOF
	#define SIZEOF(x) ( sizeof ( x ) / sizeof ( x[0] ) )
#endif