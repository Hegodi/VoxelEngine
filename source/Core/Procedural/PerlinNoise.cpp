#include "PerlinNoise.h"
#include <math.h>
#include <iostream>

// From Wikipedia: https://en.wikipedia.org/wiki/Perlin_noise

namespace ProceduralHelpers
{
	float Interpolate(float a0, float a1, float w)
	{
		//return a0 + (a1 - a0) * w;
		//return (a1 - a0) * (3.0 - w * 2.0) * w * w + a0;
		return (a1 - a0) * ((w * (w * 6.0 - 15.0) + 10.0) * w * w * w) + a0;
	}

	typedef struct
	{
		float x, y;
	} vector2;

	vector2 RandomGradient(int ix, int iy) 
	{
		float random = 2920.f * (float)sin(ix * 21942.0f + iy * 171324.0f + 8912.0f) * (float)cos(ix * 23157.0f * iy * 217832.0f + 9758.0f);
		return vector2{ (float)cos(random), (float)sin(random) };
	}

	// Computes the dot product of the distance and gradient vectors.
	float DotGridGradient(int ix, int iy, float x, float y) 
	{
		vector2 gradient = RandomGradient(ix, iy);
		float dx = x - (float)ix;
		float dy = y - (float)iy;
		return (dx * gradient.x + dy * gradient.y);
	}

	float PerlinNoise(float x, float y)
	{
		if (x < 0.0f)
		{
			x *= -1;
		}
		if (y < 0.0f)
		{
			y *= -1;
		}
		// Determine grid cell coordinates
		int x0 = (int)x;
		int x1 = x0 + 1;
		int y0 = (int)y;
		int y1 = y0 + 1;

		// Determine interpolation weights
		// Could also use higher order polynomial/s-curve here
		float sx = x - (float)x0;
		float sy = y - (float)y0;

		// Interpolate between grid point gradients
		float n0, n1, ix0, ix1, value;

		n0 = DotGridGradient(x0, y0, x, y);
		n1 = DotGridGradient(x1, y0, x, y);
		ix0 = Interpolate(n0, n1, sx);

		n0 = DotGridGradient(x0, y1, x, y);
		n1 = DotGridGradient(x1, y1, x, y);
		ix1 = Interpolate(n0, n1, sx);

		value = Interpolate(ix0, ix1, sy);
		return value;
	}

	float MultiScalePerlinNoise(float x, float y, std::vector<float> scales, std::vector<float> weights)
	{
		if (scales.size() != weights.size())
		{
			std::cout << "ERROR in MultiScalePerlinNoise: scales and weigths have different number of elements\n";
		}
		float value = 0.0f;
		for (int i=0; i<scales.size(); i++)
		{
			value += weights[i] * PerlinNoise(x * scales[i], y * scales[i]);
		}

		return value;
	}
}
