#include "TerrainSector.h"

#include "../Procedural/PerlinNoise.h"
#include "HelpersVoxels.h"
#include "MathUtils.h"
#include "TerrainSettings.h"
#include "../Materials/Material.h"
#include "Physics/Physics.h"

#include <iostream>

CTerrainSector::CTerrainSector(int indX, int indY, CMaterial const* material)
{
	m_origin = glm::vec3(indX * TerrainSettings::mc_sectorSideLength, 0.0f, indY * TerrainSettings::mc_sectorSideLength);
	m_mesh = new CMesh(material);
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

EVoxelType CTerrainSector::GetVoxel(glm::vec3 position) const
{
	glm::vec3 localPosition = position - m_origin;
	int indX = localPosition.x / TerrainSettings::mc_sectorNuberVoxelsSide;
	int indY = localPosition.y / TerrainSettings::mc_sectorNuberVoxelsSide;
	int indZ = localPosition.z / TerrainSettings::mc_sectorNuberVoxelsSide;
	return GetVoxel(indX, indY, indZ);
}

bool CTerrainSector::GetVoxelAABB(Physics::AABB& aabb, glm::vec3 position) const
{
	EVoxelType voxel = GetVoxel(position);
	if (!IsSolid(voxel))
	{
		return false;
	}
	
	aabb.pMin = position - TerrainSettings::mc_voxelHalfSize;
	aabb.pMax = position + TerrainSettings::mc_voxelHalfSize;

	return true;
}

bool CTerrainSector::IsSolid(EVoxelType voxel)
{
	switch (voxel)
	{
		break;
	case EVoxelType::Soil:
	case EVoxelType::Rock:
	case EVoxelType::Water:
	case EVoxelType::Snow:
		return true;
		break;
	case EVoxelType::Air:
	case EVoxelType::INVALID:
		return false;
		break;
	default:
		break;
	}
	return false;
}

void CTerrainSector::LoadSector(int indX, int indY)
{
	m_sectorIndX = indX;
	m_sectorIndY = indY;
	float x = m_origin.x;

	std::vector<float> perlinScales = { 0.01f, 0.1f };
	std::vector<float> perlinWeights = { 0.1f, 0.1f };

	for (int i=0; i<TerrainSettings::mc_sectorNuberVoxelsSide; i++, x += TerrainSettings::mc_voxelSize)
	{
		float z = m_origin.z;
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
    bool faces[6] = { true, true, true, true, true, true };

	int index = 0;
	float x = m_origin.x;
	for (int i=0; i<TerrainSettings::mc_sectorNuberVoxelsSide; i++, x += TerrainSettings::mc_voxelSize)
	{
		float z = m_origin.z;
		for (int j=0; j<TerrainSettings::mc_sectorNuberVoxelsSide; j++, z += TerrainSettings::mc_voxelSize)
		{
			float y = m_origin.y;
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

EVoxelType CTerrainSector::GetVoxel(int indX, int indY, int indZ) const
{
	if ((indX < 0 || indX >= TerrainSettings::mc_sectorNuberVoxelsSide) ||
		(indY < 0 || indY >= TerrainSettings::mc_sectorNuberVoxelsSide) || 
		(indZ < 0 || indZ >= TerrainSettings::mc_sectorNuberVoxelsSide))
	{
		return EVoxelType::INVALID;
	}
	int index = TerrainSettings::mc_sectorNuberVoxelsSide * (indX * TerrainSettings::mc_sectorNuberVoxelsSide + indY)  + indZ;
	return m_voxelsData[index];
}

bool CTerrainSector::CheckVoxelTransparent(int indX, int indY, int indZ, EVoxelType type) const
{
	EVoxelType voxel = GetVoxel(indX, indY, indZ);

	return voxel == EVoxelType::Air || voxel == EVoxelType::INVALID;
}

void CTerrainSector::CalculateFaces(bool faces[6], int indX, int indY, int indZ) const
{
	faces[0] = CheckVoxelTransparent(indX, indY+1, indZ, EVoxelType::Air);
	faces[1] = CheckVoxelTransparent(indX, indY-1, indZ, EVoxelType::Air);
	faces[2] = CheckVoxelTransparent(indX + 1, indY, indZ, EVoxelType::Air);
	faces[3] = CheckVoxelTransparent(indX - 1, indY, indZ, EVoxelType::Air);
	faces[4] = CheckVoxelTransparent(indX, indY, indZ + 1, EVoxelType::Air);
	faces[5] = CheckVoxelTransparent(indX, indY, indZ - 1, EVoxelType::Air);
}

