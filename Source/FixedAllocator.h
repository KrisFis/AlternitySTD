
#pragma once

#include "SafeInt.h"
#include "EnsureMacros.h"
#include "SafeChar.h"
#include "AllocatorInterface.h"
#include "CAllocation.h"
#include "AllocatorBlockManager.h"

#include "EssentialsMethods.h"

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
		{			FixedMemory = reinterpret_cast<byte*>(CAlloc::Mallocate<ElementType>(InitSize));
		}

		// Destructor
		virtual ~TFixedAllocator() 
		{
			if (IsValid(FixedMemory))
			{
				DeallocateAll();				CAlloc::Deallocate(FixedMemory);
			}
		}

		TFixedAllocator(const TFixedAllocator& other) = delete;

	public: // IAllocator overrides

		virtual ElementType* Allocate() override
		{
			uint32 freeIndex = 0;

			ENSURE_TRUE(BlockManager.FindEmptyIndex(freeIndex), nullptr);
			ENSURE_TRUE(BlockManager.AddIndex(freeIndex, false), nullptr);

			return CAlloc::CallConstructor(GetElementPtr(freeIndex));
		}

		virtual ElementType* AllocateInitialized(ElementType* InElement) override
		{
			uint32 freeIndex = 0;

			ENSURE_TRUE(BlockManager.FindEmptyIndex(freeIndex), nullptr);
			ENSURE_TRUE(BlockManager.AddIndex(freeIndex, false), nullptr);

			return CallConstructorWithMoveOrCopy(GetElementPtr(freeIndex), InElement);
		}

		virtual ElementType* Allocate(const uint32& InIndex) override
		{
			ENSURE_TRUE(BlockManager.AddIndex(InIndex), nullptr);

			return CAlloc::CallConstructor(GetElementPtr(InIndex));
		}

		virtual ElementType* AllocateInitialized(const uint32& InIndex, ElementType* InElement) override
		{
			ENSURE_TRUE(BlockManager.AddIndex(InIndex), nullptr);

			return CallConstructorWithMoveOrCopy(GetElementPtr(InIndex), InElement);
		}

		virtual void DeallocateAll() override
		{
			for (uint32 i = 0; i < BlockManager.Length; i++)
			{
				if (BlockManager.Blocks[i] != BlockManager.EMPTY_BLOCK)
				{
					CAlloc::CallDestructor(GetElementPtr(BlockManager.Blocks[i]));
					BlockManager.Blocks[i] = BlockManager.EMPTY_BLOCK;
				}
			}
		}

		virtual void Deallocate(const uint32& InIndex) override
		{
			ENSURE_TRUE(BlockManager.RemoveIndex(InIndex));

			CAlloc::CallDestructor(GetElementPtr(InIndex));

		}

		virtual void Reserve(const uint32& ReserveSize)
		{
			if (ReserveSize <= BlockManager.Length) return;

			FixedMemory = CAlloc::Reallocate(FixedMemory, BlockManager.Length, ReserveSize);
			BlockManager.ReserveLenght(ReserveSize);
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

		ElementType* CallConstructorWithMoveOrCopy(ElementType* ElementPtr, ElementType* ToCopyOrMove)
		{
			ElementType* result = CAlloc::CallMoveConstructor(ElementPtr, MoveElement(ToCopyOrMove));
			
			CAlloc::CallDestructor(ToCopyOrMove);

			return result;
		}

	protected: // Fields

		// Buffer storing all allocations
		byte* FixedMemory;

		// Manages allocated blocks
		FAllocatorBlockManager BlockManager;
	};
}