#include "World.h"

glm::vec3 const CWorld::mc_Gravity = { 0.0f, -9.8f, 0.0f };

CWorld::CWorld()
{
	m_terrain = new CTerrain();
	m_camera = new CCamera();
}

CWorld::~CWorld()
{
	if (m_terrain != nullptr)
	{
		delete m_terrain;
	}

	if (m_camera != nullptr)
	{
		delete m_camera;
	}
}
void CWorld::Update(float deltaTime)
{
	m_terrain->SetPlayerPosition(m_camera->GetPosition());
}


void CWorld::RemoveMesh(CMesh* mesh)
{
	auto it = std::find(m_meshes.begin(), m_meshes.end(), mesh);
	if (it != m_meshes.end())
	{
		m_meshes.erase(it);
	}

	delete mesh;
}
