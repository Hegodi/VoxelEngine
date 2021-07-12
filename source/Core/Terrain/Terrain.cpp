#include "Terrain.h"

#include <iostream>

#include "../Procedural/PerlinNoise.h"
#include "HelpersVoxels.h"
#include "MathUtils.h"
#include "TerrainSettings.h"

const int TableDirections[9][2] = {
	{-1,-1}, {0, -1} , {1, -1},
	{-1, 0}, {0,  0} , {1,  0},
	{-1, 1}, {0,  1} , {1,  1}
};

CTerrain::CTerrain()
{
	for(int i=0; i<m_sectorsLoaded.size(); i++)
	{
		m_sectorsLoaded[i] = nullptr;
	}

	m_material = new CMaterialDefault();
}

CTerrain::~CTerrain()
{
	for (int i=0; i<m_sectorsLoaded.size(); i++)
	{
		if (m_sectorsLoaded[i] != nullptr)
		{
			delete m_sectorsLoaded[i];
			m_sectorsLoaded[i] = nullptr;
		}
	}

	delete m_material;
}

void CTerrain::SetPlayerPosition(glm::vec3 position)
{

	int indX, indY;
	GetSectorIndices(position, indX, indY);
	if (indX != m_indCurrentSectorX || indY != m_indCurrentSectorY)
	{
		OnCurrentSectorChanged(indX, indY);
	}
}

void CTerrain::OnCurrentSectorChanged(int indXnew, int indYnew)
{

	// First: move the exisitng sectors to the right place
	for (int i = 0; i < 9; i++)
	{
		int indX = indXnew + TableDirections[i][0];
		int indY = indYnew + TableDirections[i][1];
		int indFound = FindSector(indX, indY);
		if (indFound != -1)
		{
			SwapSectors(i, indFound);
		}
	}

	// Second: load new sectors 
	for (int i = 0; i < 9; i++)
	{
		int indX = indXnew + TableDirections[i][0];
		int indY = indYnew + TableDirections[i][1];
		if (m_sectorsLoaded[i] == nullptr || !m_sectorsLoaded[i]->IsSector(indX, indY))
		{
			CreateSector(i, indX, indY);
		}
	}

	m_indCurrentSectorX = indXnew;
	m_indCurrentSectorY = indYnew;
}

void CTerrain::CreateSector(int index, int indX, int indY)
{
	if (m_sectorsLoaded[index] != nullptr)
	{
		delete m_sectorsLoaded[index];
	}
	m_sectorsLoaded[index] = new CTerrainSector(indX, indY, m_material);
}

int CTerrain::FindSector(int indX, int indY)
{
	for (int i=0; i<m_sectorsLoaded.size(); i++)
	{
		if (m_sectorsLoaded[i] != nullptr)
		{
			if (m_sectorsLoaded[i]->IsSector(indX, indY))
			{
				return i;
			}
		}
	}
	return -1;
}

void CTerrain::SwapSectors(int ind1, int ind2)
{
	CTerrainSector* tmp = m_sectorsLoaded[ind1];
	m_sectorsLoaded[ind1] = m_sectorsLoaded[ind2];
	m_sectorsLoaded[ind2] = tmp;
}

void CTerrain::GetSectorIndices(glm::vec3 const& position, int& indX, int& indY) const
{
	if (position.x < 0) 
	{
		indX = -ceil(-position.x / TerrainSettings::mc_sectorSideLength);
	}
	else
	{
		indX = floor(position.x / TerrainSettings::mc_sectorSideLength);
	}

	if (position.z < 0)
	{
		indY = -ceil(-position.z / TerrainSettings::mc_sectorSideLength);
	}
	else
	{
		indY = floor(position.z / TerrainSettings::mc_sectorSideLength);
	}
}

CTerrainSector* CTerrain::GetLoadedSector(int indX, int indY) const
{
	for (CTerrainSector* sector : m_sectorsLoaded)
	{
		if (sector->IsSector(indX, indY))
		{
			return sector;
		}
	}
	return nullptr;
}

