
#include "CoreEssentials.h"
#include "AltString.h"
#include "AutoAllocator.h"
#include "Iterator.h"
#include "List.h"

using namespace sal;

void Test_List()
{
	TList<FString> CLikeList;

	FString one("Hello");
	CLikeList.Add(one);
	CLikeList.Add("World");
	CLikeList.Add("!");

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
		LogWait();
	}

	return 0;
}