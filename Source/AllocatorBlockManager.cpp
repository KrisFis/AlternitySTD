
#include "AllocatorBlockManager.h"
#include "CAllocation.h"

#include "SafeInt.h"
#include "EnsuresAssertion.h"
#include "EnsureMacros.h"

#include "EssentialsMethods.h"

using namespace sal::CAlloc;

namespace sal
{
	FAllocatorBlockManager::FAllocatorBlockManager(const uint32& InLenght)
		: Length(InLenght)
	{
		Blocks = Mallocate<uint32>(InLenght, EMPTY_BLOCK);
	}

	FAllocatorBlockManager::~FAllocatorBlockManager()
	{
		if (IsValid(Blocks))
		{
			Deallocate(Blocks);
		}
	}

	void FAllocatorBlockManager::ReserveLenght(const uint32& InNewLenght)
	{
		if (Length >= InNewLenght) return; // Ignores lowering

		Blocks = Reallocate(Blocks, Length, InNewLenght, EMPTY_BLOCK);
		Length = InNewLenght;
	}

	bool FAllocatorBlockManager::IndexUsed(const uint32& InIndex) const
	{
		ENSURE_TRUE(InIndex != EMPTY_BLOCK, false);

		for (uint32 i = 0; i < Length; ++i)
		{
			if (Blocks[i] == InIndex) return true;
		}

		return false;
	}

	bool FAllocatorBlockManager::FindEmptyIndex(uint32& OutFreeIndex) const
	{
		for (uint32 i = 0; i < Length; ++i)
		{
			if (Blocks[i] == EMPTY_BLOCK)
			{
				OutFreeIndex = i;
				return true;
			}
		}

		return false;
	}

	bool FAllocatorBlockManager::AddIndex(const uint32& InIndex, bool CheckExistence /*= true*/)
	{
		ENSURE_TRUE(InIndex != EMPTY_BLOCK, false);

		if (CheckExistence)
		{
			if (IndexUsed(InIndex)) return false;
		}

		for (uint32 i = 0; i < Length; ++i)
		{
			if (Blocks[i] == EMPTY_BLOCK)
			{
				Blocks[i] = InIndex;
				return true;
			}
		}

		return false;
	}

	bool FAllocatorBlockManager::RemoveIndex(const uint32& InIndex)
	{
		for (uint32 i = 0; i < Length; ++i)
		{
			if (Blocks[i] == InIndex)
			{
				Blocks[i] = EMPTY_BLOCK;
				return true;
			}
		}

		return false;
	}
}