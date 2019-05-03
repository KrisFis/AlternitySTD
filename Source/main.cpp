#include <iostream>

#include "CoreEssentials.h"
#include "String.h"
#include "FixedAllocator.h"
#include "Iterator.h"
#include "List.h"

#define print(text) std::cout << text << std::endl
#define read(var) std::cin >> var
#define wait() system("pause")

using namespace sal;

int main(void)
{

#if 0

	TFixedAllocator<FString, 3> allocator;
	allocator.Allocate(0)->SetText("Hello");
	allocator.Allocate(1)->SetText("World");
	allocator.Allocate(2)->SetText("!");

	for (TIterator<FString> i = allocator.GetBufferPtr(0); i != allocator.GetBufferPtr(3); i++)
	{
		print((FString)i);
	}

#else

	TList<FString, TFixedAllocator<FString, 3>> CLikeList;
	CLikeList.Add(FString("Hello"));
	FString other("World");
	CLikeList.Add(other);
	other = "!";
	CLikeList.Add(other);

	wait();

	CLikeList.Remove(other);

	for (TIterator<FString> iter = CLikeList.Begin(); iter != CLikeList.End(); iter++)
	{
		print((FString)iter);
	}

	CLikeList.Clear();

	CLikeList.Add("NEW MRDKA");
	CLikeList.Add("!!");

	wait();
	
	for (auto iter = CLikeList.Begin(); iter != CLikeList.End(); iter++)
	{
		print((FString)iter);
	}
	
	CLikeList.RemoveAt(0);

	wait();

	for (auto iter = CLikeList.Begin(); iter != CLikeList.End(); iter++)
	{
		print((FString)iter);
	}

	CLikeList.Add("Hell yeah");

	wait();

	for (TIterator<FString> iter = CLikeList.Begin(); iter != CLikeList.End(); iter++)
	{
		print((FString)iter);
	}

#endif

	wait();

	return EXIT_SUCCESS;
}