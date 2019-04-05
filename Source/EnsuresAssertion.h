
#pragma once
#include "IntTypes.h"

FORCEINLINE bool EnsureAssert(bool InException)
{
#ifdef _DEBUG
	if (!InException) throw;
#endif
	return InException;
}