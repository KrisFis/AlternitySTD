
#pragma once

namespace sal
{
	// Basic array collection
	// Uses allocator as allocation standards
	// Stores data in array and manipulates with them (like manager of array allocator)
	template<typename ElementType, IAllocator Allocator = TFixedAllocator<ElementType>>
	class TList
	{

	public: // Constructors and destructor
		TList() = default;
		virtual ~TList() = default;

	public: // Getters

		// Gets current size of list
		FORCEINLINE const uint32& GetSize() const { return CurrentSize; }

	public: // Control method

		// Adds new element to list
		// Copies it
		void Add(const ElementType& InElement)
		{
			ElementType* allocatedElement = Allocator->Allocate(CurrentSize);

			ENSURE_VALID(allocatedElement);

			(*allocatedElement)(InElement); // Hopefully it will use copy constructor
		}

		// Adds new element to list
		// Moves it (should have defined move constructor)
		void Add(ElementType&& InElement)
		{
			ElementType* allocatedElement = Allocator->Allocate(CurrentSize);

			ENSURE_VALID(allocatedElement);

			(*allocatedElement)(InElement); // Hopefully it will use move constructor
		}

	private: // Fields

		// Remembers current size of list
		// Its mainly used for allocator
		uint32 CurrentSize;
	};
}