
#include "HelpersVoxels.h"
#include <array>


namespace HelpersVoxels
{
    // Faces with normals
    static const float FrontFace[] =
    { 
      0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
      0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
     -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
     -0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    };

    static const float BackFace[] =
    { 
      0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
      0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
     -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
     -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    };

    static const float RightFace[] =
    { 
      0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
      0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
      0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
      0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
    };

    static const float LeftFace[] =
    { 
      -0.5f,  0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
      -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
      -0.5f, -0.5f,  0.5f, -1.0f, 0.0f, 0.0f,
      -0.5f,  0.5f,  0.5f, -1.0f, 0.0f, 0.0f,
    };

    static const float TopFace[] =
    { 
      0.5f, 0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
      0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
     -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
     -0.5f, 0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
    };

    static const float BottomFace[] =
    { 
      0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f,
      0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
     -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
     -0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f,
    };

    void CalculateUV(int indexX, int indexY, int countX, int countY, std::array<float, 8>& UV)
    {
        float dx = 1.0f / countX;
        float dy = 1.0f / countY;
        float x0 = indexX * dx;
        float y0 = indexY * dy;

        UV[0] = x0;
        UV[1] = y0;

        UV[2] = x0;
        UV[3] = y0 + dy;

        UV[4] = x0 + dx;
        UV[5] = y0 + dy;

        UV[6] = x0 + dx;
        UV[7] = y0;
    }

    void AddFace(std::vector<float>& vertices, std::vector<unsigned int>&triangles, std::array<float, 8> const& UV, float const face[24], glm::vec3 position, float size)
    {
        int ind0 = vertices.size()/8;
        int indUV = 0;
        for (int i=0; i<24; i+=6, indUV+=2)
        {
            // Vertices
            vertices.push_back(position.x + face[i]*size);
            vertices.push_back(position.y + face[i+1]*size);
            vertices.push_back(position.z + face[i+2]*size);

            // Normals
            vertices.push_back(face[i+3]);
            vertices.push_back(face[i+4]);
            vertices.push_back(face[i+5]);

            // UV
            vertices.push_back(UV[indUV]);
            vertices.push_back(UV[indUV + 1]);
        }

        triangles.push_back(ind0);
        triangles.push_back(ind0+1);
        triangles.push_back(ind0+3);

        triangles.push_back(ind0+1);
        triangles.push_back(ind0+2);
        triangles.push_back(ind0+3);
    }

    enum class EFaceSide
    {
        Side,
        Top,
        Bottom
    };

    void CalculateUVMaterial(EVoxelMaterial material, EFaceSide side, std::array<float, 8>& UV)
    {
        if (material == EVoxelMaterial::Soil)
        {
            switch (side)
            {
            case HelpersVoxels::EFaceSide::Side:
                CalculateUV(2, 0, 4, 4, UV);
                break;
            case HelpersVoxels::EFaceSide::Top:
                CalculateUV(0, 0, 4, 4, UV);
                break;
            case HelpersVoxels::EFaceSide::Bottom:
                CalculateUV(1, 0, 4, 4, UV);
                break;
            default:
                break;
            }
        }
        else 
        {
            switch (material)
            {
            case HelpersVoxels::EVoxelMaterial::Rock:
                CalculateUV(3, 0, 4, 4, UV);
                break;
            case HelpersVoxels::EVoxelMaterial::Coal:
                CalculateUV(0, 1, 4, 4, UV);
                break;
            case HelpersVoxels::EVoxelMaterial::Cupper:
                CalculateUV(1, 1, 4, 4, UV);
                break;
            }
        }
    }

    void SetFaces(std::vector<float>& vertices, std::vector<unsigned int>& triangles, bool faces[6], glm::vec3 position, float size, EVoxelMaterial material)
    {
        std::array<float, 8> UV;
        if (faces[0])
        {
            CalculateUVMaterial(material, EFaceSide::Side, UV);
            AddFace(vertices, triangles, UV, FrontFace, position, size);
        }
        if (faces[1])
        {
            CalculateUVMaterial(material, EFaceSide::Side, UV);
            AddFace(vertices, triangles, UV, BackFace, position, size);
        }
        if (faces[2])
        {
            CalculateUVMaterial(material, EFaceSide::Side, UV);
            AddFace(vertices, triangles, UV, RightFace, position, size);
        }
        if (faces[3])
        {
            CalculateUVMaterial(material, EFaceSide::Side, UV);
            AddFace(vertices, triangles, UV, LeftFace, position, size);
        }
        if (faces[4])
        {
            CalculateUVMaterial(material, EFaceSide::Top, UV);
            AddFace(vertices, triangles, UV, TopFace, position, size);
        }
        if (faces[5])
        {
            CalculateUVMaterial(material, EFaceSide::Bottom, UV);
            AddFace(vertices, triangles, UV, BottomFace, position, size);
        }
    }
}
