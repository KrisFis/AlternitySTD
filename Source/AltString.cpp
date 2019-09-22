
#include "AltString.h"
#include "CoreEssentials.h"
#include "EssentialsMethods.h"

namespace sal
{
	const FString FString::Empty = FString();

	FString::FString() : 
		TextData(nullptr), Length(INDEX_NONE)
	{
		Length = 1;
		TextData = new char[Length];
		TextData[Length - 1] = INDEX_EOF;
	}

	FString::FString(const char* InText) : 
		TextData(nullptr), Length(INDEX_NONE)
	{
		// Get length for allocation
		uint16 _lenght = INDEX_NONE;

		do 
		{
			_lenght++;

		} while (InText[_lenght] != INDEX_EOF);

		Length = _lenght;

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
		Length(other.Length)
	{
		TextData = other.TextData;

		other.TextData = nullptr;
		other.Length = INDEX_EMPTY;
	}

	FString::FString(const FString& other) :
		TextData(nullptr),
		Length(other.Length)
	{
		TextData = new char[Length + 1];
		TextData[Length] = INDEX_EOF;

		// Assign new text
		for (int i = 0; i < other.Length; i++)
		{
			TextData[i] = other.TextData[i];
		}
	}

	FString::FString(EForceInit Init) :
		TextData(nullptr), Length(INDEX_NONE)
	{	}

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
		Length = other.Length;

		TextData = new char[Length + 1];
		TextData[Length] = INDEX_EOF;

		// Assign new text
		for (int i = 0; i < other.Length; i++)
		{
			TextData[i] = other.TextData[i];
		}

		return *this;
	}

	FString& FString::operator=(FString&& other)
	{		if (IsValid(TextData))
		{
			delete[] TextData;
		}

		TextData = other.TextData;
		Length = other.Length;

		other.TextData = nullptr;
		other.Length = INDEX_EMPTY;

		return *this;
	}

	FString FString::operator+(const FString& other)
	{
		uint16 resultLenght = Length + other.Length;

		FString result = FString();
	
		char*& textRef = result.TextData;
		textRef = new char[resultLenght+1];
		textRef[resultLenght] = INDEX_EOF;

		result.Length = resultLenght;

		for (int i = 0; i < Length; i++)
		{
			textRef[i] = TextData[i];
		}

		for (int i = 0; i < other.Length; i++)
		{
			textRef[i + Length] = other.TextData[i];
		}

		return result;
	}

	FString& FString::operator+=(const FString& other)
	{
		uint16 resultLenght = Length + other.Length;

		char* newArray = new char[resultLenght+1];
		newArray[resultLenght] = INDEX_EOF;

		for (int i = 0; i < Length; i++)
		{
			newArray[i] = TextData[i];
		}

		delete[] TextData;

		for (int i = 0; i < other.Length; i++)
		{
			newArray[i + Length] = other.TextData[i];
		}

		TextData = newArray;
		Length = resultLenght;

		return (*this);
	}

	bool FString::operator!=(const FString& other) const
	{
		return !((*this) == other);
	}

	bool FString::operator==(const FString& other) const
	{
		if (Length != other.Length) return false;

		for (int i = 0; i < Length; i++)
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

		Length = 0;

		do 
		{

			Length++;

		} while (InText[Length] != INDEX_EOF);

		TextData = new char[Length];

		for (uint32 i = 0; i < Length; i++)
		{
			TextData[i] = InText[i];
		}
	}
}
