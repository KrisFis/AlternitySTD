
#include "AllocatorNS.h"
#include "SafeInt.h"
#include "EnsuresAssertion.h"
#include "EnsureMacros.h"

namespace sal
{
	FAllocatorBlockManager::FAllocatorBlockManager(const uint32& InLenght)
		: Blocks(nullptr)
		, Length(InLenght)
	{
		Blocks = new uint32[InLenght];

		for (uint32 i = 0; i < InLenght; ++i)
		{
			Blocks[i] = EMPTY_BLOCK;
		}
	}

	FAllocatorBlockManager::~FAllocatorBlockManager()
	{
		if (IsValid(Blocks))
		{
			delete[] Blocks;
		}
	}

	void FAllocatorBlockManager::ReserveLenght(const uint32& InNewLenght)
	{
		if (Length >= InNewLenght) return; // Ignores lowering

		uint32* tempBlocks = new uint32[InNewLenght];

		for (uint32 i = 0; i < Length; ++i)
		{
			tempBlocks[i] = Blocks[i];
		}

		for (uint32 i = Length; i < InNewLenght; ++i)
		{
			tempBlocks[i] = EMPTY_BLOCK;
		}

		Length = InNewLenght;

		delete[] Blocks;

		Blocks = tempBlocks;
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