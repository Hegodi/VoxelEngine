#pragma once
#include "glm/glm.hpp"
#include "Camera.h"
#include "Physics/Physics.h"

class CWorld;
struct SPlayerInput
{
	float movementForward = 0.0f;
	float movementRight = 0.0f;
	bool  jump = false;
	float rotation = 0.0f;
};

class CPlayer
{
public:
	CPlayer(CCamera* camera)
		: m_camera(camera)
		, m_position(0.0f)
		, m_forwardVector(0.0f, 0.0f, 1.0f)
		, m_rightVector(1.0f, 0.0f, 0.0f)
		, m_movementVelocity(0.0f)
		, m_rotationVelocity(0.0f)
	{}
	void SetInput(SPlayerInput const& inputs);
	void Update(float deltaTime, CWorld* world);

	void SetIsGrounded(bool value) { m_isGrounded = value; }

private:
	const float m_maxMovementSpeed = 10.0f;
	const float m_maxRotationSpeed = 60.0f;
	const float m_jumpSpeed = 100.0f;
	const float m_radius = 0.5f;
	const float m_height = 1.0f;
	const float m_heightHalf = m_height * 2;

	CCamera* m_camera;

	glm::vec3 m_position;
	glm::vec3 m_forwardVector;
	glm::vec3 m_rightVector;
	glm::vec3 m_upVector;

	Physics::AABB m_aabb;

	glm::vec3 m_movementVelocity;
	float m_rotationVelocity;
	
	bool m_isGrounded = true;

};
