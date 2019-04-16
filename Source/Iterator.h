
#pragma once

template<typename TargetType>
class TIterator
{

public: // Constructors and destructor
	TIterator() = delete;
	virtual ~TIterator() = default;

	FORCEINLINE TIterator(byte* InAdress) : CurrentAdress(InAdress) { ENSURE_VALID(InAdress); }

public: // operators

	byte*& operator++()
	{
		CurrentAdress += sizeof(TargetType);
		return CurrentAdress;
	}

	byte* operator++(int)
	{
		byte* oldAdress = CurrentAdress;
		CurrentAdress += sizeof(TargetType);
		return oldAdress;
	}

	bool operator!=(const TIterator& other) const
	{
		return (CurrentAdress != other.CurrentAdress);
	}

	operator TargetType() const
	{
		return *reinterpret_cast<TargetType*>(CurrentAdress);
	}

	TargetType* operator->() const
	{
		return reinterpret_cast<TargetType*>(CurrentAdress);
	}

private: // Fields
	byte* CurrentAdress;

};