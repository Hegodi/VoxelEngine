#pragma once
#include <array>

#include "glm/glm.hpp"
#include "TerrainSector.h"


class CTerrain
{
public:
	CTerrain();
	~CTerrain();

	void SetPlayerPosition(glm::vec3 position);
	std::array<CTerrainSector*, 9> const GetSectors() const { return m_sectorsLoaded; }

private:
	void OnCurrentSectorChanged(int indXnew, int indYnew);
	void CreateSector(int index, int indX, int indY);
	int FindSector(int indX, int indY);

	void SwapSectors(int ind1, int ind2);

private:
	int m_indCurrentSectorX = -1;
	int m_indCurrentSectorY = -1;
	std::array<CTerrainSector*, 9> m_sectorsLoaded;
};
