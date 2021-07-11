#pragma once
#include "glm/glm.hpp"

namespace Physics
{
	struct AABB
	{
		glm::vec3 pMin;
		glm::vec3 pMax;
	};

	extern bool CheckCollision(AABB aabb, glm::vec3 point);
	extern bool CheckCollision(AABB aabb1, AABB aabb2);
};
