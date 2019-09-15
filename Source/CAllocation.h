
#pragma once

#include <new>
#include <cstdlib>

#include "SafeInt.h"
#include "EssentialsMethods.h"
#include "Math.h"

namespace sal
{
	namespace CAlloc
	{
		// Deallocates previously allocated dynamic memory
		// * Does not call destructor
		// @param - pointer to dynamic memory
		template<typename ObjectType>
		void Deallocate(ObjectType*& Ptr)
		{
			free(Ptr);
			Ptr = nullptr;
		}

		// Allocate new dynamic memory with defined size
		// * Simple allocation without any init value
		// * Does not call constructor
		// @template - type of object for which memory will be
		// @param - size of newly created memory (as number of object_types)
		// @return - newly allocated memory ptr
		template<typename ObjectType>
		ObjectType* Mallocate(const uint32& Size)
		{
			return (ObjectType*) malloc(sizeof(ObjectType) * Size);
		}

		// Allocate new dynamic memory with defined size
		// * Sets all default objects to specific value
		// * Does not call constructor
		// @template - type of object for which memory will be
		// @param - size of newly created memory (as number of object_types)
		// @param - value which will be set to all newly created objects
		// @return - newly allocated memory ptr
		template<typename ObjectType>
		ObjectType* Mallocate(const uint32& Size, const ObjectType& InitValue)
		{
			ObjectType* returnValue = Mallocate<ObjectType>(Size);

			for (uint32 i = 0; i < Size; ++i)
			{
				returnValue[i] = InitValue;
			}

			return returnValue;
		}

		// Reallocates previous ptr dynamic memory to different size
		// * Simple reallocation without any init value
		// * Does not call constructor
		// @template - type of object for which memory will be
		// @param - old pointer which will be used as reference for copy
		// @param - old pointer's size of old created memory (as number of object_types)
		// @param - size of newly created memory (as number of object_types)
		// @return - newly allocated memory ptr
		template<typename ObjectType>
		ObjectType* Reallocate(ObjectType*& BasePtr, const uint32& LastSize, const uint32& NewSize)
		{
			ObjectType* resultPtr = Mallocate<ObjectType>(NewSize);

			for (uint32 i = 0; i < Math::Min(LastSize, NewSize); ++i)
			{
				resultPtr[i] = BasePtr[i];
			}

			Deallocate(BasePtr);

			return resultPtr;
		}

		// Reallocates previous ptr dynamic memory to different size
		// * Sets all new objects to specific value
		// * Does not call constructor
		// @template - type of object for which memory will be
		// @param - old pointer which will be used as reference for copy
		// @param - old pointer's size of old created memory (as number of object_types)
		// @param - size of newly created memory (as number of object_types)
		// @param - value which will be set to all newly created objects
		// @return - newly allocated memory ptr
		template<typename ObjectType>
		ObjectType* Reallocate(ObjectType*& BasePtr, const uint32& LastSize, const uint32& NewSize, const ObjectType& InitValue)
		{
			ObjectType* resultPtr = Reallocate(BasePtr, LastSize, NewSize);

			for (uint32 i = LastSize; i < NewSize; ++i)
			{
				resultPtr[i] = InitValue;
			}

			return resultPtr;
		}

		// Calls *default* constructor of object
		// @template - type of object
		// @param - Pointer to object
		// @return - Pointer to newly constructed object
		template<typename ObjectType>
		ObjectType* CallConstructor(ObjectType* ObjectPtr)
		{
			return ::new(ObjectPtr) ObjectType();
		}

		// Calls *copy* constructor of object
		// @template - type of object
		// @param - Pointer to object
		// @param - Object which will be called as parameter of copy construction
		// @return - Pointer to newly constructed object
		template<typename ObjectType>
		ObjectType* CallCopyConstructor(ObjectType* ObjectPtr, const ObjectType& ObjectToCopy)
		{
			return ::new(ObjectPtr) ObjectType(ObjectToCopy);
		}

		// Calls *move* constructor of object
		// @template - type of object
		// @param - Pointer to object
		// @param - Object which will be called as parameter of move construction
		// @return - Pointer to newly constructed object
		template<typename ObjectType>
		ObjectType* CallMoveConstructor(ObjectType* ObjectPtr, ObjectType&& ObjectToMove)
		{
			return ::new(ObjectPtr) ObjectType(MoveElement(ObjectToMove));
		}

		// Calls *specific* constructor of object
		// @template - type of object
		// @template - arguments which will be passed to constructor
		// @param - Pointer to object
		// @param - arguments which will be passed to constructor
		// @return - Pointer to newly constructed object
		template<typename ObjectType, typename ...Args>
		ObjectType* CallConstructor(ObjectType* ObjectPtr, Args... Arguments)
		{
			return ::new(ObjectPtr) ObjectType(Arguments);
		}

		// Calls destructor of object
		// @template - type of object
		// @param - Pointer to object
		template<typename ObjectType>
		void CallDestructor(ObjectType* ObjectPtr)
		{
			ObjectPtr->~ObjectType();
		}
	}
}