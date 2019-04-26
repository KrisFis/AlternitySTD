#include <iostream>

#include "CoreEssentials.h"
#include "String.h"
#include "FixedAllocator.h"
#include "Iterator.h"

#define print(text) std::cout << text << std::endl
#define read(var) std::cin >> var
#define wait() system("pause")

using namespace sal;

int main(void)
{

	wait();

	TFixedAllocator<FString, 3> allocator;
	allocator.Allocate(0)->SetText("Hello");
	allocator.Allocate(1)->SetText("World");
	allocator.Allocate(2)->SetText("!");

	for (TIterator<FString> i = allocator.GetBufferPtr(0); i != allocator.GetBufferPtr(3); i++)
	{
		print((FString)i);
	}

	wait();

	return EXIT_SUCCESS;
}