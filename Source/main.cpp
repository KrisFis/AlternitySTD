#include <iostream>

#include "CoreEssentials.h"
#include "String.h"
#include "FixedAllocator.h"
#include "Iterator.h"

#define print(text) std::cout << text << std::endl
#define read(var) std::cin >> var
#define wait() system("pause")

int main(void)
{

#if 0

	wait();

	TFixedAllocator<FString, 3> allocator;
	allocator.Allocate(0, FString("Hello"));
	allocator.Allocate(1, FString("World"));
	allocator.Allocate(2, FString("!"));

	for (TIterator<FString> i = allocator.GetElementPtr(0); i != allocator.GetElementPtr(3); i++)
	{
		print((FString)i);
	}

#endif

	wait();

	return EXIT_SUCCESS;
}