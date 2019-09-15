
#pragma once

#include "FixedAllocator.h"

#include <new>
#include "SafeChar.h"

namespace sal
{
	// Inline allocator allocates first *StartInitSize* of size
	// * And reallocates its array when extends *StartInitSize*
	template<typename ElementType, uint32 InitSize>
	class TAutoAllocator : public TFixedAllocator<ElementType, InitSize>
	{

	private: // Typedefs

		typedef TFixedAllocator<ElementType, InitSize> Super;

	public: // IAllocator override

		virtual ElementType* Allocate(ElementType* InElement) override
		{
			uint32 freeIndex = 0;

			if (!Super::BlockManager.FindEmptyIndex(freeIndex))
			{
				freeIndex = Super::BlockManager.Length;
				Super::BlockManager.ReserveLenght(freeIndex * 2);
			}

			ENSURE_TRUE(Super::BlockManager.AddIndex(freeIndex, false), nullptr);

			if (IsValid(InElement))
				return Super::CallConstructorWithMoveOrCopy(Super::GetElementPtr(freeIndex), InElement);
			else
				return CAlloc::CallConstructor(Super::GetElementPtr(freeIndex));
		}
	};

}