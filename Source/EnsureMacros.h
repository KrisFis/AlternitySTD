
#pragma once

#include "EnsuresAssertion.h"

#ifdef _DEBUG
	
	// Ensure inside if statement
	#define ENSURE_CONDITION(expression) !(expression)) throw; if(!(expression)

	// Ensures validity with return
	#define ENSURE_TRUE(expression, ...) if(!(expression)) { throw; return __VA_ARGS__;}
	#define ENSURE_VALID(ptr, ...) if(!IsValid(ptr)) {throw; return __VA_ARGS__;}
	#define ENSURE_NO_ENTRY() {throw;}

#else

	#define ENSURE_CONDITION(expression) if(!(expression))

	// Ensures takes no effect when not in debug mode
	#define ENSURE_TRUE(expression, ...) if(!(expression)) { return __VA_ARGS__;}
	#define ENSURE_VALID(ptr, ...) if(!IsValid(ptr)) { return __VA_ARGS__; }
	#define ENSURE_NO_ENTRY()

#endif