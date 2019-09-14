
#pragma once

#include <new>

#include "AllocatorInterface.h"
#include "AllocatorNS.h"
#include "SafeChar.h"
#include "EssentialsMethods.h"

namespace sal
{
	// Inline allocator allocates first *StartNumAllocSize* of size
	// * And reallocates its array when extends *StartNumAllocSize*
	template<typename ElementType, uint32 StartNumAllocSize>
	class TInlineAllocator : public IAllocator<ElementType>
	{

	public: // Constructor

		TInlineAllocator()
			: BlockManager(StartNumAllocSize)
		{
			FixedMemory = ::new byte[sizeof(ElementType) * StartNumAllocSize];
		}

	public: // Destructor

		virtual ~TInlineAllocator()
		{
			if (IsValid(FixedMemory))
			{
				DeallocateAll();
				delete[] FixedMemory;
			}
		}

	public: // External methods

		void ReserveMemory(const uint32& NewNumAllocSize)
		{
			byte* tmpFixedMemory = ::new byte[sizeof(ElementType) * NewNumAllocSize];

			for (uint32 i = 0; i < BlockManager.Length; i++)
			{
				if (BlockManager.Blocks[i] != BlockManager.EMPTY_BLOCK)
				{
					ElementType* element = GetElementPtr(i);
					::new(FixedMemory + (sizeof(ElementType) * InIndex)) ElementType(MoveElement(*element)); // we try to use move constructor
					CallDestructor(element) // but in case move constructor do not exist (just used copy) -> call destructor
				}
			}

			BlockManager.Length = NewNumAllocSize;

			delete[] FixedMemory;
		}

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

			return ::new(FixedMemory + (sizeof(ElementType) * InIndex)) ElementType();
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
					CallDestructor(GetElementPtr(BlockManager.Blocks[i]));
			}
		}

		virtual ElementType* GetElement(const uint32& InIndex) const override
		{
			return (BlockManager.IndexUsed(InIndex)) ? GetElementPtr(InIndex) : nullptr;
		}

		virtual bool ElementExists(const uint32& InIndex) const override
		{
			return BlockManager.IndexUsed(InIndex);
		}

	private: // Internal methods

		FORCEINLINE byte* const GetBufferPtr(const uint32& InIndex) const { return FixedMemory + (sizeof(ElementType) * (InIndex)); }

		FORCEINLINE ElementType* GetElementPtr(const uint32& InIndex) const { return reinterpret_cast<ElementType*>(FixedMemory + (sizeof(ElementType) * InIndex)); }

		FORCEINLINE void CallDestructor(ElementType* Element) const { Element->~ElementType(); }

	private: // Fields

		byte* FixedMemory;

		FBlockManager BlockManager;

	}
}