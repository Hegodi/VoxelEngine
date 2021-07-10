#pragma once
#include <vector>

#include "glm/glm.hpp"
#include "Mesh.h"

enum class EVoxelType : unsigned char
{
	Air,
	Soil,
	Rock,
	Water,
	Snow,
	COUNT	
};

class CTerrainSector
{
public:

	CTerrainSector(int indX, int indY);
	~CTerrainSector();

	CMesh const* GetMesh() const { return m_mesh; }
	bool IsSector(int indX, int indY) const { return indX == m_sectorIndX && indY == m_sectorIndY; }

private:
	void LoadSector(int indX, int indY);
	void GenerateSectorMesh(int indX, int indY);
	bool CheckVoxel(int indX, int indY, int indZ, EVoxelType type) const;
	void CalculateFaces(bool faces[6], int indX, int indY, int indZ) const;

private:

	int m_sectorIndX = -1;
	int m_sectorIndY = -1;
	std::vector<EVoxelType> m_voxelsData;
	CMesh* m_mesh = nullptr;
	
};
