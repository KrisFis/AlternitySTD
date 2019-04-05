
#pragma once

#include "EnsuresAssertion.h"
#include "IntTypes.h"

// Ensures validity with result return (for condition)
#define ensure(expression) !EnsureAssert(expression)

// Ensures validity with return
#define ENSURE_TRUE(expression, ...) {if(!expression) return __VA_ARGS__;  }
#define ENSURE_VALID(ptr, ...) {if(!EnsureAssert(ptr != nullptr && ptr != NULL)) return __VA_ARGS__;}