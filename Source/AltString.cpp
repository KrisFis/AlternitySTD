
#include "AltString.h"
#include "CoreEssentials.h"
#include "EssentialsMethods.h"

namespace sal
{
	const FString FString::Empty = FString();

	FString::FString() : 
		TextData(nullptr), Lenght(INDEX_NONE)
	{
		Lenght = 1;
		TextData = new char[Lenght];
		TextData[Lenght - 1] = INDEX_EOF;
	}

	FString::FString(const char* InText) : 
		TextData(nullptr), Lenght(INDEX_NONE)
	{
		// Get length for allocation
		uint16 _lenght = INDEX_NONE;

		do 
		{
			_lenght++;

		} while (InText[_lenght] != INDEX_EOF);

		Lenght = _lenght;

		if (_lenght <= 0) return;

		TextData = new char[_lenght+1];
		TextData[_lenght] = INDEX_EOF;

		// Assign new text
		for (int i = 0; i < _lenght; i++)
		{
			TextData[i] = InText[i];
		}
	}

	FString::FString(FString&& other) :
		Lenght(other.Lenght)
	{
		TextData = other.TextData;
		other.TextData = nullptr;
	}

	FString::FString(const FString& other) :
		TextData(nullptr),
		Lenght(other.Lenght)
	{
		TextData = new char[Lenght + 1];
		TextData[Lenght] = INDEX_EOF;

		// Assign new text
		for (int i = 0; i < other.Lenght; i++)
		{
			TextData[i] = other.TextData[i];
		}
	}

	FString::FString(EForceInit Init) :
		TextData(nullptr), Lenght(INDEX_NONE)
	{}

	FString::~FString()
	{
		if (IsValid(TextData))
		{
			delete[] TextData;
			TextData = nullptr;
		}
	}

	char& FString::operator[](const uint16& InIndex) const
	{
		return TextData[InIndex];
	}

	FString::operator char*() const
	{
		return TextData;
	}

	FString& FString::operator=(const FString& other)
	{
		if (&other == this)
		{
			return *this;
		}

		delete[] TextData;
		Lenght = other.Lenght;

		TextData = new char[Lenght + 1];
		TextData[Lenght] = INDEX_EOF;

		// Assign new text
		for (int i = 0; i < other.Lenght; i++)
		{
			TextData[i] = other.TextData[i];
		}

		return *this;
	}

	FString& FString::operator=(FString&& other)
	{
		if (IsValid(TextData))
		{
			delete[] TextData;
		}

		TextData = other.TextData;
		Lenght = other.Lenght;

		other.TextData = nullptr;
		other.Lenght = INDEX_EMPTY;

		return *this;
	}

	FString FString::operator+(const FString& other)
	{
		uint16 resultLenght = Lenght + other.Lenght;

		FString result = FString();
	
		char*& textRef = result.TextData;
		textRef = new char[resultLenght+1];
		textRef[resultLenght] = INDEX_EOF;

		result.Lenght = resultLenght;

		for (int i = 0; i < Lenght; i++)
		{
			textRef[i] = TextData[i];
		}

		for (int i = 0; i < other.Lenght; i++)
		{
			textRef[i + Lenght] = other.TextData[i];
		}

		return result;
	}

	FString& FString::operator+=(const FString& other)
	{
		uint16 resultLenght = Lenght + other.Lenght;

		char* newArray = new char[resultLenght+1];
		newArray[resultLenght] = INDEX_EOF;

		for (int i = 0; i < Lenght; i++)
		{
			newArray[i] = TextData[i];
		}

		delete[] TextData;

		for (int i = 0; i < other.Lenght; i++)
		{
			newArray[i + Lenght] = other.TextData[i];
		}

		TextData = newArray;
		Lenght = resultLenght;

		return (*this);
	}

	bool FString::operator!=(const FString& other) const
	{
		return !((*this) == other);
	}

	bool FString::operator==(const FString& other) const
	{
		if (Lenght != other.Lenght) return false;

		for (int i = 0; i < Lenght; i++)
		{
			if (TextData[i] != other.TextData[i]) return false;
		}

		return true;
	}

	void FString::SetText(const char* InText)
	{
		if (IsValid(TextData))
		{
			delete[] TextData;

			TextData = nullptr;
		}

		Lenght = 0;

		do 
		{

			Lenght++;

		} while (InText[Lenght] != INDEX_EOF);

		TextData = new char[Lenght];

		for (uint32 i = 0; i < Lenght; i++)
		{
			TextData[i] = InText[i];
		}
	}
}
