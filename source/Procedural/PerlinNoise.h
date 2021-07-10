#pragma once
#include <vector>

namespace ProceduralHelpers
{
	extern float PerlinNoise(float x, float y);
	extern float MultiScalePerlinNoise(float x, float y, std::vector<float> scales, std::vector<float> weights);
}
