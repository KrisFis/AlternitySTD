
#pragma once

#include "SafeInt.h"
#include "EnsureMacros.h"
#include "SafeChar.h"
#include "AllocatorInterface.h"
#include "AllocatorNS.h"

namespace sal
{
	// Fixed allocator allocates just fixed number of elements and do not let you allocates more than set number
	template<typename ElementType, uint32 NumAllocSize>
	class TFixedAllocator : public IAllocator<ElementType>
	{

	public: // Constructors

		TFixedAllocator() :	FixedMemory(nullptr), BlockManager(NumAllocSize)
		{
			FixedMemory = new byte[GetLenghtOfBuffer()];
		}

		// Destructor
		virtual ~TFixedAllocator() 
		{
			if (IsValid(FixedMemory))
			{
				DeallocateAll();
				delete[] FixedMemory;
			}
		}

		TFixedAllocator(const TFixedAllocator& other) = delete;

	public: // IAllocator overrides

		virtual ElementType* Allocate(const uint32& InIndex) override final
		{
			ENSURE_TRUE(BlockManager.AddIndex(InIndex), nullptr);

			ElementType* resultElement = new(FixedMemory + (sizeof(ElementType) * InIndex)) ElementType();

			return resultElement;
		}

		virtual ElementType* GetElement(const uint32& InIndex) const override final
		{
			return (BlockManager.IndexExists(InIndex)) ? GetElementPtr(InIndex) : nullptr;
		}

		virtual bool ElementExists(const uint32& InIndex) const override final
		{
			return BlockManager.IndexExists(InIndex);
		}

		virtual void Deallocate(const uint32& InIndex) override final
		{
			ENSURE_TRUE(BlockManager.RemoveIndex(InIndex));

			byte* startPtr = GetBufferPtr(InIndex);
			CallDestructor(GetElementPtr(InIndex));

			for (byte i = startPtr[0]; i <= startPtr[sizeof(ElementType)]; i++)
				startPtr[i] = NULL;
		}

		virtual void DeallocateAll() override final
		{
			for (uint32 i = 0; i < BlockManager.Length; i++)
			{
				if (BlockManager.Blocks[i] != BlockManager.EMPTY_BLOCK)
					CallDestructor(GetElementPtr(BlockManager.Blocks[i]));
			}
		}

	public: // IAllocator overrides

		virtual byte* const GetBufferPtr(const uint32 & InIndex) const override final { return FixedMemory + (sizeof(ElementType) * (InIndex)); }

	private: // Helper methods

		FORCEINLINE uint32 GetLenghtOfBuffer() const { return (sizeof(ElementType) * NumAllocSize); }

		FORCEINLINE ElementType* GetElementPtr(const uint32& InIndex) const { return reinterpret_cast<ElementType*>(FixedMemory + (sizeof(ElementType) * InIndex)); }

		FORCEINLINE void CallDestructor(ElementType* InElement) const { InElement->~ElementType(); }

	private: // Fields

		// Buffer storing all allocations
		byte* FixedMemory;

		// Manages allocated blocks
		FBlockManager BlockManager;
	};
}