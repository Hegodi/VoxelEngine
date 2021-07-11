#include "Player.h"
#include "World.h"

void CPlayer::SetInput(SPlayerInput const& inputs)
{
	m_movementVelocity = m_maxMovementSpeed * (inputs.movementForward * m_forwardVector + inputs.movementRight * m_rightVector);
	m_rotationVelocity = m_maxRotationSpeed * inputs.rotation;
	
	if (m_isGrounded)
	{
		if (inputs.jump)
		{
			m_movementVelocity += m_upVector * m_jumpSpeed;
		}
	}
}

void CPlayer::Update(float deltaTime, CWorld* world)
{
	m_position += m_movementVelocity;

	m_aabb.pMin = m_position - glm::vec3(-m_radius, -m_heightHalf, -m_radius);
	m_aabb.pMax = m_position - glm::vec3(m_radius, m_heightHalf, m_radius);
}
