#include "Material.h"
#include "../Camera.h"
#include "Shader.h"

CMaterialDefault::CMaterialDefault()
{
	m_shader = Shaders::GetShader(EShaderType::Default);
    m_shader->SetTexture(m_texturePath);
}

void CMaterialDefault::Use(CCamera const* camera) const
{
    m_shader->Use();
    glm::mat4 trans = camera->GetCameraViewTransform();
    m_shader->SetMatrix4("transform", trans);
    m_shader->SetVec3("viewPos", camera->GetPosition());

    m_shader->SetVec3("material.diffuse", m_colorDifuse);
    m_shader->SetVec3("material.ambient", m_colorAmbient);
    m_shader->SetVec3("material.specular", m_colorSpecular);

    m_shader->SetFloat("material.shininess", m_shininess);

    m_shader->SetVec3("light.direction", glm::vec3(0.2f, 1.0f, 0.5f));
    m_shader->SetVec3("light.color", glm::vec3(1.0f, 1.0f, 1.0f));
}
