#pragma once

#include "glm/glm.hpp"

#include "Shader.h"

class CCamera;
class CMaterial
{
public:
	virtual void Use(CCamera const* camera) const = 0;
	
	CShader* m_shader = nullptr;
};

class CMaterialDefault : public CMaterial
{
public:
	CMaterialDefault(); 
	void Use(CCamera const* camera) const override final;

private:
	glm::vec3 m_colorDifuse = { 0.4f, 0.4f, 0.4f };
	glm::vec3 m_colorAmbient = { 0.2f, 0.2f, 0.2f };
	glm::vec3 m_colorSpecular = { 0.8f, 0.8f, 0.8f };
	float m_shininess = 1.0f;
};
