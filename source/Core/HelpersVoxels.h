#pragma once

#include <vector>
#include "glm/glm.hpp"

namespace HelpersVoxels
{
	enum class EVoxelMaterial
	{
		Soil,
		Rock,
		Coal,
		Cupper
	};
	extern void SetFaces(std::vector<float>& vertices, std::vector<unsigned int>& triangles, bool faces[6], glm::vec3 position, float size = 1.0f, EVoxelMaterial voxelMaterial = EVoxelMaterial::Soil);

};
