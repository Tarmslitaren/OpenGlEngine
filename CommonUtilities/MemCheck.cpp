#include "stdafx.h"
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstddef>
#include <windows.h>
#include <sstream>
#include <iostream>
#include <fstream>

#undef new
 //#undef delete
 
// Global flags set by macros in MemCheck.h
bool traceFlag = true;
bool activeFlag = true;
 
namespace //Anonymous
{
 
	// Memory map entry type
	struct Info
	{
		void* ptr;
		const char* file;
		long line;
	};
	 
	// Memory map data
	const size_t MAXPTRS = 10000000u;
	Info memMap[MAXPTRS];
	size_t nptrs = 0;
	 
	// Searches the map for an address
	int findPtr( void *p )
	{
		for( size_t i = 0; i < nptrs; ++i )
		{
			if( memMap[i].ptr == p )
			{
				return i;
			}
		}

		return -1;
	}
	 

	void delPtr( void* p )
	{
		int pos = findPtr( p );
		assert( pos >= 0 );
		
		// Remove pointer from map
		for( size_t i = pos; i < nptrs - 1; ++i )
		{
			memMap[i] = memMap[i + 1];
		}

		--nptrs;
	}


	// Dummy type for static destructor
	struct Sentinel {
		~Sentinel()
		{
			std::ofstream file;
			file.open("memleaks.log");
			char buf[1024];

			if(nptrs > 0)
			{
				std::string leakText = "Leaked memory at:\n";
				OutputDebugStringA( leakText.c_str());
				file << leakText;



				
				for(size_t i = 0; i < nptrs; ++i)
				{
					sprintf_s( buf, "\t%p (file: %s, line %ld),\n", memMap[i].ptr, memMap[i].file, memMap[i].line );
					OutputDebugStringA( buf );
					std::string leakSpecs = buf;
					file << leakSpecs;
				}
			}
			else
			{
				sprintf_s( buf, "No user memory leaks!\n" );
				OutputDebugStringA( buf );
				std::string leakSpecs = buf;
				file << leakSpecs;
			}
			file.close();
		}
	};

	// Static dummy object
	Sentinel s;
} // End anonymous namespace


// Overload scalar new
void *operator new( const size_t siz, const char* file, const long line )
{
	void *p = malloc(siz);
	
	if( activeFlag )
	{
		if( nptrs == MAXPTRS )
		{
			printf( "memory map too small (increase MAXPTRS)\n" );
			exit( 1 );
		}
		
		memMap[nptrs].ptr = p;
		memMap[nptrs].file = file;
		memMap[nptrs].line = line;
		++nptrs;
	}
	
	if( traceFlag )
	{
		printf( "Allocated %u bytes at address %p ", siz, p );
		printf( "(file: %s, line: %ld)\n", file, line );
	}
	
	return p;
}


// Overload array new
void *operator new[]( const size_t siz, const char* file, const long line )
{
	return operator new(siz, file, line);
}


// Override scalar delete
void operator delete( void *p )
{
	std::ofstream file;
	file.open("memleaks.log");
	char buf[1024];

	if( findPtr( p ) >= 0 )
	{
		free( p );
		assert( nptrs > 0 );
		delPtr( p );
		
		if( traceFlag )
		{
			sprintf_s( buf, "Deleted memory at address %p\n", p );
			OutputDebugStringA( buf );
			std::string deleteText = buf;
			file << deleteText;
		}
	}
	else if( !p && activeFlag )
	{
		sprintf_s( buf, "Attempt to delete unknown pointer: %p\n", p );
		OutputDebugStringA( buf );
		std::string deleteText = buf;
		file << deleteText;
	}
}
 
// Override array delete
void operator delete[]( void *p )
{
	operator delete( p );
}
