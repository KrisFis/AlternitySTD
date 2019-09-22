
#pragma once

namespace sal
{
	template<typename ElementType, typename AllocatorType>
	struct TAllocatorIterator : public TIterator<ElementType>
	{

	private: // typedefs

		typedef TIterator<ElementType> Super;

	public: // Constructions

		TAllocatorIterator(byte* InAdress) = delete;

		TAllocatorIterator(byte* InAdress, AllocatorType* InAllocator)
			: Super(InAdress)
			, CurrentIndex(0)
			, Allocator(InAllocator)
		{}

	public: // Destructor

		virtual ~TAllocatorIterator() { }

	protected: // TIterator overrides

		virtual void FindNext() override
		{
			if (!IsValid(Allocator))
			{
				Super::FindNext();
				return;
			}

			uint32 lastElementIndex = Allocator->GetLastElementIndex();
			while (CurrentIndex != lastElementIndex)
			{
				if (Allocator->ElementExists(++CurrentIndex))
				{
					Super::CurrentAddress = reinterpret_cast<byte*>(Allocator->GetElement(CurrentIndex));
					return;
				}
			}

			Super::CurrentAddress = nullptr;
		}

	protected: // Fields

		uint32 CurrentIndex;
		AllocatorType* Allocator;
	};

	namespace Iteration
	{
		template<typename ElementType, typename AllocatorType>
		FORCEINLINE TAllocatorIterator<ElementType, AllocatorType> CreateBeginIterator(AllocatorType* AllocatorInstance)
		{
			ElementType* firstElement = AllocatorInstance->GetFirstElement();
			TAllocatorIterator<ElementType, AllocatorType> iterator(reinterpret_cast<byte*>(firstElement), AllocatorInstance);

			return iterator;
		}

		template<typename ElementType, typename AllocatorType>
		FORCEINLINE TAllocatorIterator<ElementType, AllocatorType> CreateEndIterator(AllocatorType* AllocatorInstance)
		{
			TAllocatorIterator<ElementType, AllocatorType> iterator(nullptr, nullptr);
			return iterator;
		}
	}
}