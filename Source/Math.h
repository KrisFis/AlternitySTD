
#pragma once

namespace sal
{
	struct FMath
	{
		// Get higher value of two values
		// @param - first value
		// @param - second value
		// @return - higher value of them
		template<typename ObjectType>
		static ObjectType Max(const ObjectType& Obj1, const ObjectType& Obj2) { return (Obj1 > Obj2) ? Obj1 : Obj2; }

		// Get lower value of two values
		// @param - first value
		// @param - second value
		// @return - lower value of them
		template<typename ObjectType>
		static ObjectType Min(const ObjectType& Obj1, const ObjectType& Obj2) { return (Obj1 < Obj2) ? Obj1 : Obj2; }

	};
}