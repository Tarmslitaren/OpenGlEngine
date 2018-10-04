#pragma once

//remember to include all std and windows classes before memcheck if this is in stdafx.h  as they too overloads new

#pragma warning (disable: 4291)
#include <cstddef>

void *operator new( const std::size_t, const char*, const long );
void *operator new[]( const std::size_t, const char*, const long );
#define new new( __FILE__, __LINE__ )


//not matching the new new but works.
void operator delete( void* );
void operator delete[]( void* );

extern bool traceFlag;
#define TRACE_ON() traceFlag = true;
#define TRACE_OFF() traceFlag = false;

extern bool activeFlag;
#define MEM_ON() activeFlag = true;
#define MEM_OFF() activeFlag = false;
