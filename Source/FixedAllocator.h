
#pragma once

#include "SafeInt.h"
#include "EnsureMacros.h"
#include "SafeChar.h"
#include "AllocatorInterface.h"

namespace sal
{
	// Fixed allocator allocates just fixed number of elements and do not let you allocates more than set number
	template<typename ElementType, uint32 NumAllocSize>
	class TFixedAllocator : public IAllocator<ElementType>
	{

	public: // Constructors

		TFixedAllocator() :
			FixedMemory(nullptr)
		{
			FixedMemory = new byte[sizeof(ElementType) * NumAllocSize];
		}


		// Destructor
		virtual ~TFixedAllocator() 
		{
			if (IsValid(FixedMemory))
			{
				delete[] FixedMemory;
			}
		}

		TFixedAllocator(const TFixedAllocator& other) = delete;

	public: // Getters

		FORCEINLINE ElementType* const GetElementPtr(const uint32& InIndex) { return IAllocator<ElementType>::CastToElementPtr(FixedMemory + (sizeof(ElementType) * (InIndex))); }
		
		FORCEINLINE byte* const GetBufferPtr(const uint32& InIndex) { return FixedMemory + (sizeof(ElementType) * (InIndex)); }

	public: // Allocate methods

		ElementType* Allocate(const uint32& InIndex) override
		{
			ENSURE_TRUE(InIndex+1 <= NumAllocSize, nullptr);

			ElementType* resultElement = new(FixedMemory + (sizeof(ElementType) * InIndex)) ElementType();

			return resultElement;
		}

		void Deallocate(const uint32& InIndex) override
		{
			ENSURE_TRUE(InIndex + 1 <= NumAllocSize);

			byte* startPtr = FixedMemory + (sizeof(ElementType) * InIndex);

			for (byte i = startPtr[0]; i <= startPtr[sizeof(ElementType)]; i++)
				startPtr[i] = NULL;
		}

		void Deallocate(ElementType* InElementPtr) override
		{
			ENSURE_VALID(InElementPtr);

			byte* recastedPtr = IAllocator<ElementType>::CastToBufferPtr(InElementPtr);

			for (byte i = recastedPtr[0]; i <= recastedPtr[sizeof(ElementType)]; i++)
				recastedPtr[i] = NULL;
		}

	private: // Fields

		// Buffer storing all allocations
		byte* FixedMemory;
	};
}