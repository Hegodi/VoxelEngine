#pragma once
#include "glm/glm.hpp"

class CCamera 
{
public:
	CCamera();

	void SetPosition(glm::vec3 const& position);
	void SetRotation(float pitch, float yaw);
	void Move(float forward, float right);
	void Rotate(float pitch, float yaw);
	glm::mat4 const& GetCameraViewTransform() const;

	glm::vec3 const GetPosition() const { return m_position; }
	glm::vec3 const GetForwardVector() const { return m_forwardVector; }
	glm::vec3 const GetRight() const { return m_forwardVector; }

	void SetScreenSize(float width, float height);

private:
	void CalculateViewTransformation();

private:
	const float m_fov = 45.0f;
	const float m_zPlaneMin = 0.1f;
	const float m_zPlaneMax = 100.0f;
	float m_screenWidth = 800.0f;
	float m_screenHeight = 600.0f;

	float m_pitch = 0;
	float m_yaw = 0;
	glm::vec3 m_position;
	glm::vec3 m_forwardVector;
	glm::vec3 m_rightVector;
	glm::vec3 m_upVector;

	glm::mat4 m_viewTransform;
	glm::mat4 m_projectionTransform;


};
