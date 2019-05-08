
#include "AllocatorNS.h"
#include "SafeInt.h"
#include "EnsuresAssertion.h"
#include "EnsureMacros.h"

namespace sal
{
	FBlockManager::FBlockManager(const uint32& InLenght)
		: Blocks(nullptr)
		, Length(InLenght)
	{
		Blocks = new uint32[InLenght];

		for (uint32 i = 0; i < InLenght; i++)
		{
			Blocks[i] = EMPTY_BLOCK;
		}
	}

	FBlockManager::~FBlockManager()
	{
		Length = 0;

		if (IsValid(Blocks))
		{
			delete[] Blocks;
		}
	}

	bool FBlockManager::IndexExists(const uint32& InIndex) const
	{
		ENSURE_TRUE(InIndex != EMPTY_BLOCK, false);

		for (uint32 i = 0; i < Length; i++)
		{
			if (Blocks[i] == InIndex) return true;
		}

		return false;
	}

	bool FBlockManager::AddIndex(const uint32& InIndex, bool CheckExistence /*= true*/)
	{
		ENSURE_TRUE(InIndex != EMPTY_BLOCK, false);

		if (CheckExistence)
		{
			if (IndexExists(InIndex)) return false;
		}

		for (uint32 i = 0; i < Length; i++)
		{
			if (Blocks[i] == EMPTY_BLOCK)
			{
				Blocks[i] = InIndex;
				return true;
			}
		}

		return false;
	}

	bool FBlockManager::RemoveIndex(const uint32& InIndex)
	{
		for (uint32 i = 0; i < Length; i++)
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