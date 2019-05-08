
#pragma once

namespace sal
{
	// Basic "non-const" iterator class
	// Iterates thought allocator or any type of buffer
	template<typename ElementType>
	class TIterator
	{

	public: // Constructors and destructor
		
		// Constructor
		TIterator() = delete;

		TIterator(const TIterator<ElementType>& other)	{ CurrentAddress = other.CurrentAddress; }
		
		// Destructor
		virtual ~TIterator() { CurrentAddress = nullptr; }

		FORCEINLINE TIterator(byte* InAdress) : CurrentAddress(InAdress) { ENSURE_VALID(InAdress); }

	public: // operators

		byte*& operator++()
		{
			CurrentAddress += sizeof(ElementType);
			return CurrentAddress;
		}

		byte* operator++(int)
		{
			byte* oldAdress = CurrentAddress;
			CurrentAddress += sizeof(ElementType);
			return oldAdress;
		}

		bool operator!=(const TIterator& other) const
		{
			return (CurrentAddress != other.CurrentAddress);
		}

		bool operator==(const byte* otherAddress) const
		{
			return (CurrentAddress == otherAddress);
		}

		operator ElementType() const
		{
			return *reinterpret_cast<ElementType*>(CurrentAddress);
		}

		ElementType* operator->() const
		{
			return reinterpret_cast<ElementType*>(CurrentAddress);
		}

	public: // Methods

		// Updates current iterator address
		// and returns itself
		TIterator<ElementType>& Update(byte* otherAddress)
		{
			ENSURE_VALID(otherAddress, *this);

			if (CurrentAddress != otherAddress) CurrentAddress = otherAddress;

			return *this;
		}

	private: // Fields
		byte* CurrentAddress;
	};
}