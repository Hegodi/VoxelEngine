#pragma once
#include <vector>

#include "glm/glm.hpp"
#include "Camera.h"
#include "Terrain/Terrain.h"
#include "Mesh.h"
#include "Player.h"
#include "Physics/Physics.h"

class CWorld
{
public:
	CWorld(bool isGame);
	~CWorld();

	void Update(float deltaTime);

	void RemoveMesh(CMesh* mesh);

	std::vector<CMesh*> const& GetMeshes() const { return m_meshes; }
	CCamera* GetCamera() const { return m_camera; }
	CTerrain* GetTerrain() const { return m_terrain; }
	CPlayer* GetPlayer() const { return m_player; }

	bool IsColliding(Physics::AABB aabb) const;

public:
	static const glm::vec3 mc_Gravity;

private:
	CPlayer* m_player = nullptr;
	CCamera* m_camera = nullptr;
	CTerrain* m_terrain = nullptr;
	std::vector<CMesh*> m_meshes;


};
