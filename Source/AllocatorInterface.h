
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

		// Allocates new object at specific index
		// There have to be an index, because of safety allocation and representation in arrays types
		virtual ElementType* Allocate(const uint32& InIndex) = 0;

		// Gets allocated object
		virtual ElementType* GetElement(const uint32& InIndex) const = 0;

		// Gets existing of object
		// @return - whether object exist at allocator
		virtual bool ElementExists(const uint32& InIndex) const = 0;

		// Deallocates object allocated in specific buffer location (index)
		virtual void Deallocate(const uint32& InIndex) = 0;

		// Deallocates all allocated objects
		virtual void DeallocateAll() = 0;

	public: // JUST FOR INNER PURPOSES, gets raw byte pointer

		virtual byte* const GetBufferPtr(const uint32& InIndex) const = 0;
	};
}