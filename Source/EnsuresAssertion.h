
#pragma once

#include "BaseMacros.h"

FORCEINLINE bool IsValid(void* InPtr) { return (InPtr != nullptr && InPtr != NULL); }