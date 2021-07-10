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
}

void CGraphics::Init()
{
    glEnable(GL_DEPTH_TEST);
    Shaders::Compile();
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
        for (CTerrainSector* sector : sectors)
        {
            if (sector != nullptr)
            {
                if (CMesh const* mesh = sector->GetMesh())
                {
                    DrawMesh(mesh, camera);
                }
            }
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

void CGraphics::DrawMesh(CMesh const* mesh, CCamera const* const camera)
{

    mesh->m_material->Use(camera);

    glBindVertexArray(mesh->m_vertexArrayObject);
    glDrawElements(GL_TRIANGLES, mesh->GetNumberElements(), GL_UNSIGNED_INT, 0);

}

