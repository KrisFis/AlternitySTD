
#pragma once

#include "AllocatorInterface.h"
#include "Iterator.h"
#include "EnsureMacros.h"
#include "EssentialsMethods.h"


namespace sal
{
	// Basic array collection
	// Uses allocator as allocation standards
	// Stores data in array and manipulates with them (like manager of array allocator)	
	template<typename InElementType, typename InAllocator> 
	class TList
	{

	public: // Typedefs
		typedef InElementType ElementType;

	public: // Constructors

		// Basic clean init constructor
		TList() : Allocator(new InAllocator()) { Clear(); }

	public: // Destructor
		virtual ~TList()
		{
			if (IsValid(Allocator))
			{
				delete Allocator;
			}
		}

	public: // Getters

		// Gets current size of list
		FORCEINLINE const uint32& GetLenght() const { return CurrentSize; }

	public: // Iteration getters

		// Iterator for iteration thought list (buffer)
		typedef	TIterator<ElementType> ListIterator;

		// Gets begin of iteration
		FORCEINLINE ListIterator Begin() { return ListIterator(Allocator->GetBufferPtr(0)); }

		// Gets end of iteration
		FORCEINLINE ListIterator End() { return ListIterator(Allocator->GetBufferPtr(CurrentSize)); }

	public: // Control method

		// Adds new element to list
		// Copies it
		void Add(const ElementType& InElement)
		{
			ElementType* allocatedElement = Allocator->Allocate(CurrentSize);

			ENSURE_VALID(allocatedElement);

			(*allocatedElement) = ElementType(InElement);

			CurrentSize++;
		}

		// Adds new element to list
		// Moves it (should have defined move constructor)
		void Add(ElementType&& InElement)
		{
			ElementType* allocatedElement = Allocator->Allocate(CurrentSize);

			ENSURE_VALID(allocatedElement);
			
			(*allocatedElement) = ElementType(MoveElement<ElementType>(InElement));

			CurrentSize++;
		}

		// Removes specific element
		void Remove(const ElementType& InElement)
		{
			Allocator->Deallocate(InElement);
			CurrentSize--;
		}

		// Removes element at specific index
		void RemoveAt(const uint32& InIndex)
		{
			ENSURE_TRUE(InIndex <= CurrentSize - 1);

			Allocator->DeallocateAt(InIndex);
			CurrentSize--;
		}

		// Clears list and removes all elements
		void Clear()
		{
			Allocator->DeallocateAll();
			CurrentSize = 0;
		}

	private: // Fields

		// Allocator instance
		IAllocator<ElementType>* Allocator;

	private: // Primitive fields

		// Remembers current size of list
		// Its mainly used for allocator
		uint32 CurrentSize;
	};
}