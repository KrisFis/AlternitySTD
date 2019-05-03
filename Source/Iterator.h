
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
		
		// Destructor
		virtual ~TIterator()
		{
			// address is not created here so do not remove it here!
			CurrentAdress = nullptr;
		}

		FORCEINLINE TIterator(byte* InAdress) : CurrentAdress(InAdress) { ENSURE_VALID(InAdress); }

	public: // operators

		byte*& operator++()
		{
			CurrentAdress += sizeof(ElementType);
			return CurrentAdress;
		}

		byte* operator++(int)
		{
			byte* oldAdress = CurrentAdress;
			CurrentAdress += sizeof(ElementType);
			return oldAdress;
		}

		bool operator!=(const TIterator& other) const
		{
			return (CurrentAdress != other.CurrentAdress);
		}

		operator ElementType() const
		{
			return *reinterpret_cast<ElementType*>(CurrentAdress);
		}

		ElementType* operator->() const
		{
			return reinterpret_cast<ElementType*>(CurrentAdress);
		}

	private: // Fields
		byte* CurrentAdress;

	};
}