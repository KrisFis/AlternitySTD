
#pragma once

#include "SafeInt.h"
#include "Iterator.h"

namespace sal
{
	// Basic allocator interface
	// Because of polymerization, we cant use specific constructors
	// Allocator should JUST be used by array types collections!
	template<typename ElementType>
	class IAllocator
	{

	public: // Virtual destructor
		virtual ~IAllocator() {}

	public: // Control methods

		// Allocates new object and finds it free index
		virtual ElementType* Allocate() = 0;

		// Allocates new object and try to use move (otherwise copy) from initialized element
		virtual ElementType* AllocateInitialized(ElementType* InElement) = 0;

		// Allocates new object at specific index
		virtual ElementType* Allocate(const uint32& InIndex) = 0;

		// Allocates new object at specific index and try to use move (otherwise copy) from initialized element
		virtual ElementType* AllocateInitialized(const uint32& InIndex, ElementType* InElement) = 0;

		// Deallocates all allocated objects
		virtual void DeallocateAll() = 0;

		// Deallocates object allocated in specific buffer location (index)
		virtual void Deallocate(const uint32& InIndex) = 0;

		// Reserves size for elements at heap
		virtual void Reserve(const uint32& ReserveSize) = 0;

		// Gets existing of object
		// @return - whether object exist at allocator
		virtual bool ElementExists(const uint32& InIndex) const = 0;

		// Gets allocated object by its index
		virtual ElementType* GetElement(const uint32& InIndex) const = 0;

		// Gets first element in allocator
		virtual ElementType* GetFirstElement() const = 0;

		// Gets last element in allocator
		virtual ElementType* GetLastElement() const = 0;
	};
}