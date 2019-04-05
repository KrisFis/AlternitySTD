
#pragma once

#define INDEX_NONE -1

#ifndef NULL
	#ifdef __cplusplus
		#define NULL 0
	#else
		#define NULL ((void *)0)
	#endif
#endif

#ifndef FORCEINLINE
	#ifdef COMPILER_MSVC
		#define FORCEINLINE __forceinline
	#elif defined(COMPILER_GCC) || defined(COMPILER_CLANG)
		#define FORCEINLINE inline __attribute__ ((always_inline))
	#else
		#define FORCEINLINE inline
	#endif
#endif

typedef char int8;
typedef unsigned char uint8;
typedef short int int16;
typedef unsigned short int uint16;
typedef long int32;
typedef unsigned long uint32;