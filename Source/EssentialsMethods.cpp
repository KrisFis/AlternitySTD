
#include "EssentialsMethods.h"
#include <iostream>

namespace sal
{

	void LogWait()
	{
		system("PAUSE");
	}

	void LogMsg(const char* InText, bool InEndLine /*= true*/)
	{
		if (InEndLine)
			std::cout << InText << std::endl;
		else
			std::cout << InText;
	}

	void LogInt(const int InInt, bool InEndLine /*= true*/)
	{
		if (InEndLine)
			std::cout << InInt << std::endl;
		else
			std::cout << InInt;
	}
}
