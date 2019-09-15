
#pragma once

#include "FixedAllocator.h"

#include <new>
#include "SafeChar.h"
#include "AllocatorNS.h"

namespace sal
{
	// Inline allocator allocates first *StartInitSize* of size
	// * And reallocates its array when extends *StartInitSize*
	template<typename ElementType, uint32 InitSize>
	class TAutoAllocator : public TFixedAllocator<ElementType, InitSize>
	{

	private: // Typedefs

		typedef TFixedAllocator<ElementType, InitSize> Super;

	private: // Asserts

		static_assert(InitSize > 0, 
			"Set start reserve size bigger than 0!");

	public: // IAllocator override

		virtual ElementType* Allocate() override
		{
			uint32 freeIndex = 0;

			if (!Super::BlockManager.FindEmptyIndex(freeIndex))
			{
				freeIndex = Super::BlockManager.Length;
				Super::BlockManager.ReserveLenght(freeIndex * 2);
			}

			ENSURE_TRUE(Super::BlockManager.AddIndex(freeIndex, false), nullptr);

			return ::new(Super::FixedMemory + (sizeof(ElementType) * freeIndex)) ElementType();
		}
	};

}