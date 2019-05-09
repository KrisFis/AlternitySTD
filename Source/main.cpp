
#include "CoreEssentials.h"
#include "String.h"
#include "FixedAllocator.h"
#include "Iterator.h"
#include "List.h"

using namespace sal;

void Test_List()
{
	TList<FString, TFixedAllocator<FString, 3>> CLikeList;
	FString one("ONE");
	CLikeList.Add(one);
	CLikeList.Add("TWO");

	for (auto iter = CLikeList.Begin(); iter != CLikeList.End(); iter++)
	{
		LogMsg((FString)iter);
	}
}

int main(void)
{
	while (true)
	{
		// DEBUG!
		Test_List();
	}

	return 0;
}