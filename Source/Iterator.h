
#pragma once

namespace sal
{
	// Basic "non-const" iterator class
	// Iterates thought allocator or any type of buffer
	template<typename ElementType>
	struct TIterator
	{

	public: // Constructors
		
		// Constructor
		TIterator() = delete;
		TIterator(byte* InAdress) 
			: CurrentAddress(InAdress)
		{ }

	public: // Destructor

		// Destructor
		virtual ~TIterator() { CurrentAddress = nullptr; }

	public: // operators

		TIterator& operator++()
		{
			FindNext();
			return *(this);
		}

		TIterator operator++(int)
		{
			byte* oldAdress = CurrentAddress;
			FindNext();
			return TIterator(oldAdress);
		}

		bool operator!=(const TIterator& other) const
		{
			return !(operator==(other));
		}

		bool operator==(const TIterator& other) const
		{
			return (CurrentAddress == other.CurrentAddress);
		}

		explicit operator byte*() const 
		{
			return CurrentAddress;
		}

		operator ElementType() const
		{
			return *reinterpret_cast<ElementType*>(CurrentAddress);
		}

		ElementType operator*() const
		{
			return *reinterpret_cast<ElementType*>(CurrentAddress);
		}

		ElementType* operator->() const
		{
			return reinterpret_cast<ElementType*>(CurrentAddress);
		}

	protected: // Virtual methods

		virtual void FindNext()
		{
			CurrentAddress += sizeof(ElementType);
		}

	protected: // Fields

		byte* CurrentAddress;
	};
}