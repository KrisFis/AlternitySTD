
#pragma once

#include "SafeInt.h"
#include "EnsureMacros.h"
#include "SafeChar.h"
#include "AllocatorInterface.h"

// Fixed allocator allocates just fixed number of elements and do not let you allocates more than set number
template<typename ElementType, uint32 NumAllocSize>
class TFixedAllocator : public IAllocator
{

public: // Constructors
	TFixedAllocator() :
		FixedMemory(nullptr)
	{
		FixedMemory = new byte[sizeof(ElementType) * NumAllocSize];
	}

	virtual ~TFixedAllocator() 
	{
		if (IsValid(FixedMemory))
		{
			delete[] FixedMemory;
		}
	}

	TFixedAllocator(const TFixedAllocator& other) = delete;

public: // Allocate methods

	template<typename... _Args>
	ElementType* Allocate(uint32 InIndex, _Args&&... InConstructArgs)
	{
		ENSURE_TRUE(InIndex+1 <= NumAllocSize, nullptr);

		ElementType* resultElement = new(FixedMemory + (sizeof(ElementType) * InIndex)) ElementType(InConstructArgs...);

		return resultElement;
	}

	void Deallocate(ElementType* InElementPtr)
	{
		ENSURE_VALID(InElementPtr);

		for (uint32 i = InElementPtr; i <= (InElementPtr + (sizeof(ElementType))); i++)
			InElementPtr[i] = NULL;
	}

public: // Getters

	/*
	typedef Iterator<ElementType> AllocatorIterator;

	FORCEINLINE Iterator<ElementType> Begin() const { return Iterator<ElementType>(FixedMemory); }

	FORCEINLINE Iterator<ElementType> End() const { return Iterator<ElementType>(FixedMemory + (sizeof(ElementType) * ConstructedElementsNum)); }
	*/

private: // Fields
	byte* FixedMemory;
};