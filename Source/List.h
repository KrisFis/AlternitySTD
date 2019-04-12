
#pragma once

template<typename ElementType, IAllocator InAllocator = TFixedAllocator<ElementType>>
class TList
{

public: // Constructors and destructor
	TList() = default;
	virtual ~TList() = default;

public: // Control method

	void Add(const ElementType& InElement)
	{

	}

	void Add(ElementType&& InElement)
	{

	}
};