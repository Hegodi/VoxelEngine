#include "Entity.h"
#include <glm/gtc/matrix_transform.hpp>

CEntity::CEntity()
{
	m_position = { 0.0f, 0.0f, 0.0f };
	m_rotationAngles = { 0.0f, 0.0f, 0.0f };
	m_transformation = glm::mat4(1.0f);
}

void CEntity::Move(glm::vec3 deltaPos)
{
	m_position += deltaPos;
	m_transformation = glm::translate(m_transformation, deltaPos);
}

void CEntity::Rotate(glm::vec3 axis, float angle)
{
	m_rotationAngles += axis * angle;
	m_transformation = glm::rotate(m_transformation, angle, axis);
}

void CEntity::CalculateTransformation()
{
}
