#pragma once
#include "glm/glm.hpp"

namespace TerrainSettings
{

	static const float mc_voxelSize = 1.0f;
	static const int mc_sectorNuberVoxelsSide = 50;

	static const int mc_sectorTotalNumberVoxels = mc_sectorNuberVoxelsSide * mc_sectorNuberVoxelsSide * mc_sectorNuberVoxelsSide;
	static const float mc_sectorSideLength = mc_sectorNuberVoxelsSide * mc_voxelSize;
	static const float mc_sectorSideHalfLength = mc_sectorSideLength * 0.5f;

	static const glm::vec3 mc_voxelHalfSize = { mc_voxelSize * 0.5f, mc_voxelSize * 0.5f , mc_voxelSize * 0.5f };
}
