#include <iostream>

#include "CoreEssentials.h"
#include "String.h"

#define print(text) std::cout << text << std::endl
#define read(var) std::cin >> var
#define wait() system("pause")

int main(void)
{
	FString first("Hello World");

	print(first.GetRawText());
	print(first.GetLenght());

	wait();

	first += "_2";

	print(first.GetRawText());
	print(first.GetLenght());

	wait();

	FString second(first);

	print("==");
	print(second.GetRawText());
	print(second.GetLenght());

	if (first == second)
	{
		print("YES!!");

		second += " mrdat";

		if (first != second)
		{
			print("VOLE_JO!!");
		}
	}

	wait();

	return EXIT_SUCCESS;
}