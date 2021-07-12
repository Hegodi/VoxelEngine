#pragma once
#include <vector>

#include "glm/glm.hpp"
#include "Mesh.h"

class CMaterial;
enum class EVoxelType : unsigned char
{
	Air,
	Soil,
	Rock,
	Water,
	Coal,
	Cupper,
	COUNT,
	INVALID = COUNT
};

class CTerrainSector
{
public:

	CTerrainSector(int indX, int indY, CMaterial const* material);
	~CTerrainSector();

	CMesh const* GetMesh() const { return m_mesh; }
	bool IsSector(int indX, int indY) const { return indX == m_sectorIndX && indY == m_sectorIndY; }
	glm::vec3 const& GetOrigin() const { return m_origin; }
	EVoxelType GetVoxel(glm::vec3 position) const;

	static bool IsSolid(EVoxelType voxel);

private:
	void LoadSector(int indX, int indY);
	void GenerateSectorMesh(int indX, int indY);
	EVoxelType GetVoxel(int indX, int indY, int indZ) const;
	bool CheckVoxelTransparent(int indX, int indY, int indZ, EVoxelType type) const;
	void CalculateFaces(bool faces[6], int indX, int indY, int indZ) const;

private:

	glm::vec3 m_origin;
	int m_sectorIndX = -1;
	int m_sectorIndY = -1;
	std::vector<EVoxelType> m_voxelsData;
	CMesh* m_mesh = nullptr;
};
