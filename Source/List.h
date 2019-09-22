
#pragma once

#include "AllocatorInterface.h"
#include "AllocatorIterator.h"
#include "EnsureMacros.h"
#include "EssentialsMethods.h"

namespace sal
{
	// Basic array collection
	// Uses allocator as allocation standards
	// Stores data in array and manipulates with them (like manager of array allocator)	
	template<typename ElementType, typename AllocatorType = TAutoAllocator<ElementType>> 
	class TList
	{

	private: // Typedefs and aliases

		typedef TAllocatorIterator<ElementType, AllocatorType> ListIterator;

	public: // Constructors

		// Basic clean init constructor
		TList() 
			: Allocator(new AllocatorType())
			, CurrentSize(0)
		{}

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

		// Gets begin of iteration
		FORCEINLINE ListIterator begin() const { return Iteration::CreateBeginIterator<ElementType>(Allocator); }

		// Gets end of iteration
		FORCEINLINE ListIterator end() const { return Iteration::CreateEndIterator<ElementType>(Allocator); }

	public: // Control method

		// Adds new element to list
		// Copies it
		void Add(const ElementType& InElement)
		{
			ElementType* allocatedElement = Allocator->Allocate();

			ENSURE_VALID(allocatedElement);

			*allocatedElement = InElement;

			CurrentSize++;
		}

		// Adds new element to list
		// Moves it (should have defined move constructor)
		void Add(ElementType&& InElement)
		{
			ElementType* allocatedElement = Allocator->AllocateInitialized(&InElement);

			ENSURE_VALID(allocatedElement);
			
			CurrentSize++;
		}
		
#if 0

		// Removes specific element which is copy of element
		// * This method is more hungry than other methods
		// * It's better to use "RemoveAt" more often than this
		// @param - element which is copy of element we want to remove
		void Remove(const ElementType& InElement)
		{
			// This method is not implemented yet
			// This method should be the last core method to implement
			ENSURE_NO_ENTRY();
		}

#endif

		// Removes element at specific index
		void RemoveAt(const uint32& InIndex)
		{
			ENSURE_TRUE(InIndex <= CurrentSize - 1);

			Allocator->Deallocate(InIndex);
			CurrentSize--;
		}

		// Finds reference to element by its index
		// @param - Element reference as out parameter
		// @param - index of element
		// @return - has been successfully found?
		bool FindRef(ElementType& OutElementRef, const uint32& InIndex)
		{
			ElementType* foundElement = Allocator->GetElement(InIndex);

			if (IsValid(foundElement))
			{
				OutElementRef = *foundElement;
				return true;
			}

			return false;
		}

		// Finds element at list
		// @param - index of element in list
		// @return - pointer to element in list
		ElementType* Find(const uint32& InIndex)
		{
			return Allocator->GetElement(InIndex);
		}

		// Clears list and removes all elements of it
		void Clear()
		{
			Allocator->DeallocateAll();
			CurrentSize = 0;
		}

		void Reserve(const uint32& InNewSize)
		{
			Allocator->Reserve(InNewSize);
		}

	private: // Fields

		// Allocator instance
		AllocatorType* Allocator;

	private: // Primitive fields

		// Remembers current size of list
		// Its mainly used for allocator
		uint32 CurrentSize;
	};
}