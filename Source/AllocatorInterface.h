
#pragma once

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

		// Deallocates object allocated in specific buffer location (index)
		virtual void DeallocateAt(const uint32& InIndex) = 0;

		// Deallocates object allocated in this allocator
		virtual void Deallocate(const ElementType& InElementPtr) = 0;

		// Deallocates all objects of allocator (clears whole buffer)
		virtual void DeallocateAll() = 0;

	public: // Getters

		virtual ElementType* const GetElementPtr(const uint32& InIndex) const = 0;

		virtual byte* const GetBufferPtr(const uint32& InIndex) const = 0;

	protected: // Inner recasts

		// From buffer to element
		FORCEINLINE ElementType* CastToElementPtr(byte* InBufferPtr) const
		{
			return reinterpret_cast<ElementType*>(InBufferPtr);
		}

		// From element to buffer
		FORCEINLINE byte* CastToBufferPtr(ElementType* InElementPtr) const
		{
			return reinterpret_cast<byte*>(InElementPtr);
		}
	};
}