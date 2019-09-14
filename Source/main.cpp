
#include "CoreEssentials.h"
#include "AltString.h"
#include "FixedAllocator.h"
#include "Iterator.h"
#include "List.h"

using namespace sal;

void Test_List()
{
	TList<FString, TInlineAllocator<FString, 3>> CLikeList;
	FString one("ONE");
	CLikeList.Add(one);
	CLikeList.Add("TWO");

	for (FString str : CLikeList)
	{
		LogMsg(str);
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