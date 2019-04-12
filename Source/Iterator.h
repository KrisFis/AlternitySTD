
#pragma once

template<typename IterTargetType>
class TIterator
{

public: // Constructors and destructor
	TIterator() = delete;
	virtual ~TIterator() = default;

	FORCEINLINE TIterator(byte* InAdress) : CurrentAdress(InAdress) { ENSURE_VALID(InAdress); }

public: // operators

	byte*& operator++()
	{
		CurrentAdress += sizeof(IterTargetType);
		return CurrentAdress;
	}

	byte* operator++(int)
	{
		byte* oldAdress = CurrentAdress;
		CurrentAdress += sizeof(IterTargetType);
		return oldAdress;
	}

	bool operator!=(const TIterator& other) const
	{
		return (CurrentAdress != other.CurrentAdress);
	}

	operator IterTargetType() const
	{
		return *reinterpret_cast<IterTargetType*>(CurrentAdress);
	}

	IterTargetType* operator->() const
	{
		return reinterpret_cast<IterTargetType*>(CurrentAdress);
	}

private: // Fields
	byte* CurrentAdress;

};