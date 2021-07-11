#include "Physics.h"
bool Physics::CheckCollision(AABB aabb, glm::vec3 point)
{
	return point.x >= aabb.pMin.x && point.y >= aabb.pMin.y && point.z >= aabb.pMin.z &&
		   point.x <= aabb.pMax.x && point.y <= aabb.pMax.y && point.z <= aabb.pMax.z;
}

bool Physics::CheckCollision(AABB aabb1, AABB aabb2)
{
	return (aabb1.pMin.x <= aabb2.pMax.x && aabb1.pMax.x >= aabb2.pMin.x) &&
		   (aabb1.pMin.y <= aabb2.pMax.y && aabb1.pMax.y >= aabb2.pMin.y) &&
		   (aabb1.pMin.z <= aabb2.pMax.z && aabb1.pMax.z >= aabb2.pMin.z);
}
