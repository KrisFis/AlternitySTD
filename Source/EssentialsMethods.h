
#pragma once

namespace sal
{
	template<typename ElementType>
	ElementType&& MoveElement(ElementType& Reference)
	{
		return static_cast<ElementType&&>(Reference);
	}
}