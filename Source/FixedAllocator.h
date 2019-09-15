
#pragma once

#include <new>

#include "SafeInt.h"
#include "EnsureMacros.h"
#include "SafeChar.h"
#include "AllocatorInterface.h"
#include "AllocatorNS.h"

namespace sal
{
	// Fixed allocator allocates just fixed number of elements and do not let you allocates more than set number
	template<typename ElementType, uint32 InitSize>
	class TFixedAllocator : public IAllocator<ElementType>
	{

	private: // Asserts

		static_assert(InitSize > 0,
			"Set start reserve size bigger than 0!");

	public: // Constructors

		TFixedAllocator() :	FixedMemory(nullptr), BlockManager(InitSize)
		{
			FixedMemory = ::new byte[sizeof(ElementType) * InitSize];
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

		virtual ElementType* Allocate(const uint32& InIndex) override
		{
			ENSURE_TRUE(BlockManager.AddIndex(InIndex), nullptr);

			return ::new(FixedMemory + (sizeof(ElementType) * InIndex)) ElementType();
		}

		virtual ElementType* Allocate() override
		{
			uint32 freeIndex = 0;

			ENSURE_TRUE(BlockManager.FindEmptyIndex(freeIndex), nullptr);
			ENSURE_TRUE(BlockManager.AddIndex(freeIndex, false), nullptr);

			return ::new(FixedMemory + (sizeof(ElementType) * freeIndex)) ElementType();
		}

		virtual void Deallocate(const uint32& InIndex) override
		{
			ENSURE_TRUE(BlockManager.RemoveIndex(InIndex));

			byte* startPtr = GetBufferPtr(InIndex);
			CallDestructor(GetElementPtr(InIndex));
		}

		virtual void DeallocateAll() override
		{
			for (uint32 i = 0; i < BlockManager.Length; i++)
			{
				if (BlockManager.Blocks[i] != BlockManager.EMPTY_BLOCK)
				{
					CallDestructor(GetElementPtr(BlockManager.Blocks[i]));
					BlockManager.Blocks[i] = BlockManager.EMPTY_BLOCK;
				}
			}
		}

		virtual void Reserve(const uint32& ReserveSize)
		{
			if (ReserveSize <= BlockManager.Length) return;

			byte* tmpFixedMemory = ::new byte[sizeof(ElementType) * ReserveSize];

			for (uint32 i = 0; i < BlockManager.Length; i++)
			{
				if (BlockManager.Blocks[i] != BlockManager.EMPTY_BLOCK)
				{
					ElementType* element = GetElementPtr(i);
					::new(FixedMemory + (sizeof(ElementType) * i)) ElementType(MoveElement(*element));
					CallDestructor(element);
				}
			}

			BlockManager.Length = ReserveSize;

			delete[] FixedMemory;
		}

		virtual ElementType* GetElement(const uint32& InIndex) const override
		{
			return GetElementPtr(InIndex);
		}

		virtual bool ElementExists(const uint32& InIndex) const override
		{
			return BlockManager.IndexUsed(InIndex);
		}

	protected: // Helper methods

		FORCEINLINE byte* const GetBufferPtr(const uint32 & InIndex) const { return FixedMemory + (sizeof(ElementType) * (InIndex)); }

		FORCEINLINE ElementType* GetElementPtr(const uint32& InIndex) const { return reinterpret_cast<ElementType*>(FixedMemory + (sizeof(ElementType) * InIndex)); }

		FORCEINLINE void CallDestructor(ElementType* InElement) const { InElement->~ElementType(); }

	protected: // Fields

		// Buffer storing all allocations
		byte* FixedMemory;

		// Manages allocated blocks
		FAllocatorBlockManager BlockManager;
	};
}