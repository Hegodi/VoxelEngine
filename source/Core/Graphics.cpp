#include "Graphics.h"

#include <iostream>

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "World.h"



CGraphics::CGraphics()
{
}

CGraphics::~CGraphics()
{
    if (m_shader != nullptr)
    {
        delete m_shader;
    }
}

void CGraphics::Init()
{
    glEnable(GL_DEPTH_TEST);
    m_shader = new CShader(EShaderType::Default);
}

void CGraphics::Render(GLFWwindow* window, CWorld const& world)
{
    if (window == nullptr)
    {
        return;
    }
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    CCamera* camera = world.GetCamera();
    if (camera == nullptr)
    {
        return;
    }

    if (CTerrain* terrain = world.GetTerrain())
    {
        std::array<CTerrainSector*, 9> sectors = terrain->GetSectors();
        int ind = 0;
        for (CTerrainSector* sector : sectors)
        {
            if (sector != nullptr)
            {
                if (CMesh const* mesh = sector->GetMesh())
                {
                    DrawMesh(mesh, camera, ind);
                }
            }
            ind++;
        }
    }

    std::vector<CMesh*> const& meshes = world.GetMeshes();
    for (auto mesh : meshes)
    {
        DrawMesh(mesh, camera);
    }

    // -------------------------------------------------------------------------------
    glfwSwapBuffers(window);
}

void CGraphics::DrawMesh(CMesh const* mesh, CCamera const* const camera, int color)
{

    glm::mat4 trans = camera->GetCameraViewTransform();

    m_shader->Use();
    m_shader->SetMatrix4("transform", trans);

    if (m_shader->GetType() == EShaderType::Default)
    {
        m_shader->SetVec3("light.direction", glm::vec3(0.2f, 1.0f, 0.5f));
        m_shader->SetVec3("light.color", glm::vec3(1.0f, 1.0f, 1.0f));

#ifdef DEBUG_SECTORS
        switch (color)
        {
        case 0:
            m_shader->SetVec3("material.diffuse", glm::vec3(0.5f, 0.0f, 0.0f));
            break;
        case 1:
            m_shader->SetVec3("material.diffuse", glm::vec3(0.0f, 0.5f, 0.0f));
            break;
        case 2:
            m_shader->SetVec3("material.diffuse", glm::vec3(0.0f, 0.0f, 0.5f));
            break;
        case 3:
            m_shader->SetVec3("material.diffuse", glm::vec3(0.5f, 0.5f, 0.0f));
            break;
        case 4:
            m_shader->SetVec3("material.diffuse", glm::vec3(0.5f, 0.0f, 0.5f));
            break;
        case 5:
            m_shader->SetVec3("material.diffuse", glm::vec3(0.0f, 0.5f, 0.5f));
            break;
        case 6:
            m_shader->SetVec3("material.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
            break;
        case 7:
            m_shader->SetVec3("material.diffuse", glm::vec3(0.1f, 0.1f, 0.1f));
            break;
        case 8:
            m_shader->SetVec3("material.diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
            break;
        default:
            break;
        }
        m_shader->SetVec3("material.ambient", glm::vec3(0.0f, 0.0f, 0.0f));
        m_shader->SetVec3("material.specular", glm::vec3(0.0f, 0.0f, 0.0f));
#else
        m_shader->SetVec3("material.diffuse", glm::vec3(0.8f, 0.0f, 0.0f));
        m_shader->SetVec3("material.ambient", glm::vec3(0.1f, 0.1f, 0.1f));
        m_shader->SetVec3("material.specular", glm::vec3(0.3f, 0.3f, 0.3f));

#endif
        m_shader->SetFloat("material.shininess", 1.0f);
        m_shader->SetVec3("viewPos", camera->GetPosition());
    }

    glBindVertexArray(mesh->m_vertexArrayObject); 
    glDrawElements(GL_TRIANGLES, mesh->GetNumberElements(), GL_UNSIGNED_INT, 0);

}

