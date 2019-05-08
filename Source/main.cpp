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

void Test_List()
{
	TList<FString, TFixedAllocator<FString, 3>> CLikeList;
	CLikeList.Add("LOL");
	CLikeList.Add("NO_LOL");
	CLikeList.Add("HELL_YEAH");
}

void Test()
{
	print("Testing 'list'");

	wait();
	Test_List();

}

int main(void)
{
	while (true)
	{
		// DEBUG!
		Test_List();
	}

	wait();

	Test();
	return 0;
}