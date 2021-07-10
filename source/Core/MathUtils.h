#pragma once
namespace MathUtils
{
	template<typename T> T Clamp(T value, T min, T max )
	{
		if (value < min) return min;
		else if (value > max) return max;
		return value;
	}
}
