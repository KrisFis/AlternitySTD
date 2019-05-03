
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
			FixedMemory = new byte[GetLenghtOfBuffer()];
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

		ElementType* const GetElementPtr(const uint32& InIndex) const override { return IAllocator<ElementType>::CastToElementPtr(FixedMemory + (sizeof(ElementType) * (InIndex))); }

		byte* const GetBufferPtr(const uint32 & InIndex) const override { return FixedMemory + (sizeof(ElementType) * (InIndex)); }

	public: // Allocate methods

		ElementType* Allocate(const uint32& InIndex) override
		{
			ENSURE_TRUE(InIndex+1 <= NumAllocSize, nullptr);

			ElementType* resultElement = new(FixedMemory + (sizeof(ElementType) * InIndex)) ElementType();

			return resultElement;
		}

		void DeallocateAt(const uint32& InIndex) override
		{
			ENSURE_TRUE(InIndex + 1 <= NumAllocSize);

			byte* startPtr = FixedMemory + (sizeof(ElementType) * InIndex);

			for (byte i = startPtr[0]; i <= startPtr[sizeof(ElementType)]; i++)
				startPtr[i] = NULL;
		}

		void Deallocate(const ElementType& InElementPtr) override
		{
			byte* recastedPtr = IAllocator<ElementType>::CastToBufferPtr(&const_cast<ElementType&>(InElementPtr));

			for (byte i = recastedPtr[0]; i <= recastedPtr[sizeof(ElementType)]; i++)
				recastedPtr[i] = NULL;
		}

		void DeallocateAll() override
		{
			for (uint32 i = 0; i < GetLenghtOfBuffer(); i++)
			{
				FixedMemory[i] = NULL;
			}
		}

	private: // Helper methods

		FORCEINLINE uint32 GetLenghtOfBuffer() const { return (sizeof(ElementType) * NumAllocSize); }

	private: // Fields

		// Buffer storing all allocations
		byte* FixedMemory;
	};
}