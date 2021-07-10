#pragma once

#include <vector>
#include "glm/glm.hpp"

namespace HelpersVoxels
{
	extern void AddFace(std::vector<float>& vertices, std::vector<unsigned int>& triangles, float const face[12], glm::vec3 position, float size);
	extern void SetFaces(std::vector<float>& vertices, std::vector<unsigned int>& triangles, bool faces[6], glm::vec3 position, float size = 1.0f);
};
