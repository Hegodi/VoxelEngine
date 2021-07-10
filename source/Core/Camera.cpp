#include "Camera.h"
#include "MathUtils.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/rotate_vector.hpp"


static const glm::vec3 World_UP = { 0.0f, 1.0f, 0.0f };
static const glm::vec3 World_FORWARD = { 0.0f, 0.0f, 1.0f };
static const glm::vec3 World_RIGHT = { 1.0f, 0.0f, 0.0f };

CCamera::CCamera()
{
	m_forwardVector = glm::vec3(0.0f, 0.0f, 1.0f);
	m_position = glm::vec3(10.0f, 10.0f, 10.0f);
	CalculateViewTransformation();

	SetScreenSize(800.0f, 600.0f);

}

void CCamera::SetPosition(glm::vec3 const& position)
{
	m_position = position;;
	CalculateViewTransformation();
}

void CCamera::SetRotation(float pitch, float yaw)
{
	m_pitch = MathUtils::Clamp(pitch, -45.0f, 45.0f);
	m_yaw = yaw;
	if (m_yaw > 360.0f) m_yaw -= 360.0f;
	else if (m_yaw < 0.0f) m_yaw += 360.0f;
	m_forwardVector = glm::rotate(World_FORWARD, glm::radians(m_yaw), World_UP);
	m_forwardVector = glm::rotate(m_forwardVector, glm::radians(m_pitch), m_rightVector);
	CalculateViewTransformation();
}

void CCamera::Move(float forward, float right)
{
	SetPosition(m_position + forward * m_forwardVector + right * m_rightVector);
}

void CCamera::Rotate(float pitch, float yaw)
{
	SetRotation(m_pitch + pitch, m_yaw + yaw);
}

glm::mat4 const& CCamera::GetCameraViewTransform() const
{
	return m_projectionTransform * m_viewTransform;
}

void CCamera::SetScreenSize(float width, float height)
{
	m_screenWidth = width;
	m_screenHeight = height;
    m_projectionTransform = glm::perspective(glm::radians(m_fov), m_screenWidth / m_screenHeight, m_zPlaneMin, m_zPlaneMax);
}

void CCamera::CalculateViewTransformation()
{
	m_rightVector = glm::cross(m_forwardVector, World_UP);
	m_upVector = glm::cross(m_rightVector, m_forwardVector);
	m_viewTransform = glm::lookAt(m_position, m_position + m_forwardVector, m_upVector);
}
