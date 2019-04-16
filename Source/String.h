#pragma once

#include "CoreEssentials.h"

// struct representing array of chars
struct FString
{

public: // Constructors and destructor
	explicit FString();
	virtual ~FString();

	FString(const FString& other);
	FString(FString&& other);

	FString(const char* InText);

public: // Operators
	
	// Getter operators
	char& operator[](const uint16& InIndex) const;

	// Conversion operators
	operator char*() const;

	// Arithmetic operators
	FString operator+(const FString& other);
	FString& operator+=(const FString& other);

	// Comparison operators
	bool operator==(const FString& other) const;
	bool operator!=(const FString& other) const;

public: // Getters
	FORCEINLINE bool IsEmpty() const { return (Lenght == 0); }
	FORCEINLINE uint16 GetLenght() const { return Lenght; }
	FORCEINLINE bool IsValidIndex(const uint32& InIndex) const { return (InIndex < Lenght); }

public: // Static fields
	static const FString Empty;

private: // Fields
	char* TextData;
	uint16 Lenght;
};