
#include "CoreEssentials.h"
#include "AltString.h"
#include "AutoAllocator.h"
#include "Iterator.h"
#include "List.h"

using namespace sal;

void Test_List()
{
	TList<FString, TAutoAllocator<FString, 1>> CLikeList;
	FString one("Hello");
 	CLikeList.Add(one);
	CLikeList.Add("World");

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