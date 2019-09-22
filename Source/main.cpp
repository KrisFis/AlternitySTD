
#include "CoreEssentials.h"
#include "AltString.h"
#include "AutoAllocator.h"
#include "Iterator.h"
#include "List.h"

using namespace sal;

void PrintAll(const TList<FString>& ListToPrint)
{
	int i = 0;
	for (FString str : ListToPrint)
	{
		LogInt(i, false);
		LogMsg(": ", false);
		LogMsg(str);
		++i;
	}

	LogMsg("");
}

void Test_List()
{
	TList<FString> CLikeList;

	FString one("Hello");
	CLikeList.Add(one);
	CLikeList.Add("World");
	CLikeList.Add("!");

	PrintAll(CLikeList);
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