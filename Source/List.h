
#pragma once
#include "CoreEssentials.h"

// Collection which holds elements in array
// Its like smart array which manages it self's
template<class ListType>
struct List
{
	// Clear, basic init constructor
	List() : Size(0), MaxCapacity(0) {}

	// Constructor with defining maximal capacity of list
	// @parameter1 - Specific maximal capacity
	explicit List(const uint32& InMaxCapacity) : Size(0), MaxCapacity(InMaxCapacity) {}

	// Virtual destructor
	virtual ~List()
	{
		if (Size > 0)
		{
			delete[] Elements;
		}
	}

	// Adds new element of ListType by reference
	// @parameter1 - New element which is not already included in list
	void Add(const ListType& InNewValue)
	{
		if (ensure(Size + 1 <= MaxCapacity))
		{

		}
	}

	// Adds new element of ListType by rvalue if possible
	// @parameter1 - New element which is not already included in list
	void Add(ListType&& InNewValue)
	{
		if (ensure(Size + 1 <= MaxCapacity))
		{

		}
	}

private: // fields
	ListType** Elements;
	uint32 Size;

	uint32 MaxCapacity;
};