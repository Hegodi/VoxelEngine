#pragma once
#include "Mesh.h"
#include "glm/glm.hpp"

class CEntity
{
public:
	CEntity();
	~CEntity() {};

	glm::mat4 const& GetTransformation() const { return m_transformation; }

	void Move(glm::vec3 deltaPos);
	void Rotate(glm::vec3 axis, float angle);

protected:
	virtual void CalculateTransformation();

protected:
	glm::mat4 m_transformation;
	glm::vec3 m_position;
	glm::vec3 m_rotationAngles;

};
