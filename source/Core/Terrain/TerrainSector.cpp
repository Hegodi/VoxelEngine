#include "TerrainSector.h"

#include "../Procedural/PerlinNoise.h"
#include "HelpersVoxels.h"
#include "MathUtils.h"
#include "TerrainSettings.h"

#include <iostream>

CTerrainSector::CTerrainSector(int indX, int indY)
{
	m_mesh = new CMesh();
	LoadSector(indX, indY);
	GenerateSectorMesh(indX, indY);
}

CTerrainSector::~CTerrainSector()
{
	if (m_mesh != nullptr)
	{
		delete m_mesh;
	}
}

void CTerrainSector::LoadSector(int indX, int indY)
{
	m_sectorIndX = indX;
	m_sectorIndY = indY;
	int x0 = indX * TerrainSettings::mc_sectorSideLength ;
	int z0 = indY * TerrainSettings::mc_sectorSideLength;
	float x = x0;

	std::vector<float> perlinScales = { 0.01f, 0.1f };
	std::vector<float> perlinWeights = { 0.1f, 0.1f };

	for (int i=0; i<TerrainSettings::mc_sectorNuberVoxelsSide; i++, x += TerrainSettings::mc_voxelSize)
	{
		float z = z0;
		for (int j=0; j<TerrainSettings::mc_sectorNuberVoxelsSide; j++, z += TerrainSettings::mc_voxelSize)
		{
			int height = MathUtils::Clamp(0.6f +  ProceduralHelpers::MultiScalePerlinNoise(x, z, perlinScales, perlinWeights), 0.0f, 1.0f) * TerrainSettings::mc_sectorNuberVoxelsSide;
			for (int k=0; k<height; k++)
			{
				m_voxelsData.push_back(EVoxelType::Soil);
			}
			for (int k = height; k < TerrainSettings::mc_sectorNuberVoxelsSide; k++)
			{
				m_voxelsData.push_back(EVoxelType::Air);
			}
		}
	}
}

void CTerrainSector::GenerateSectorMesh(int indX, int indY)
{
	int x0 = indX * TerrainSettings::mc_sectorSideLength;
	int z0 = indY * TerrainSettings::mc_sectorSideLength;
    bool faces[6] = { true, true, true, true, true, true };

	int index = 0;
	float x = x0;
	for (int i=0; i<TerrainSettings::mc_sectorNuberVoxelsSide; i++, x += TerrainSettings::mc_voxelSize)
	{
		float z = z0;
		for (int j=0; j<TerrainSettings::mc_sectorNuberVoxelsSide; j++, z += TerrainSettings::mc_voxelSize)
		{
			float y = 0.0f;
			for (int k = 0; k < TerrainSettings::mc_sectorNuberVoxelsSide; k++, y+= TerrainSettings::mc_voxelSize, index++)
			{
				if (m_voxelsData[index] != EVoxelType::Air)
				{
					glm::vec3 position(x, y, z);
					CalculateFaces(faces, i, j, k);
					HelpersVoxels::SetFaces(m_mesh->m_vertices, m_mesh->m_triangles, faces, position, TerrainSettings::mc_voxelSize);
				}
			}
		}
	}
    m_mesh->CreateBufferObjects();
}

bool CTerrainSector::CheckVoxel(int indX, int indY, int indZ, EVoxelType type) const
{
	if ((indX < 0 || indX >= TerrainSettings::mc_sectorNuberVoxelsSide) ||
		(indY < 0 || indY >= TerrainSettings::mc_sectorNuberVoxelsSide) || 
		(indZ < 0 || indZ >= TerrainSettings::mc_sectorNuberVoxelsSide))
	{
		return true;
	}

	int index = TerrainSettings::mc_sectorNuberVoxelsSide * (indX * TerrainSettings::mc_sectorNuberVoxelsSide + indY)  + indZ;
	return m_voxelsData[index] == type;
}

void CTerrainSector::CalculateFaces(bool faces[6], int indX, int indY, int indZ) const
{
	faces[0] = CheckVoxel(indX, indY+1, indZ, EVoxelType::Air);
	faces[1] = CheckVoxel(indX, indY-1, indZ, EVoxelType::Air);
	faces[2] = CheckVoxel(indX + 1, indY, indZ, EVoxelType::Air);
	faces[3] = CheckVoxel(indX - 1, indY, indZ, EVoxelType::Air);
	faces[4] = CheckVoxel(indX, indY, indZ + 1, EVoxelType::Air);
	faces[5] = CheckVoxel(indX, indY, indZ - 1, EVoxelType::Air);
}

