
#include "HelpersVoxels.h"


namespace HelpersVoxels
{
    // Faces with normals
    static const float FrontFace[] =
    { 0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
      0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
     -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
     -0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    };

    static const float BackFace[] =
    { 0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
      0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
     -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
     -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    };

    static const float RightFace[] =
    { 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
      0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
      0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
      0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
    };

    static const float LeftFace[] =
    { -0.5f,  0.5f,  0.5f, -1.0f, 0.0f, 0.0f,
      -0.5f,  0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
      -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
      -0.5f, -0.5f,  0.5f, -1.0f, 0.0f, 0.0f,
    };

    static const float TopFace[] =
    { 0.5f, 0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
      0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
     -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
     -0.5f, 0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
    };

    static const float BottomFace[] =
    { 0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f,
      0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
     -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
     -0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f,
    };


    void AddFace(std::vector<float>& vertices, std::vector<unsigned int>&triangles, float const face[24], glm::vec3 position, float size)
    {
        int ind0 = vertices.size()/6;
        for (int i=0; i<24; i+=6)
        {
            vertices.push_back(position.x + face[i]*size);
            vertices.push_back(position.y + face[i+1]*size);
            vertices.push_back(position.z + face[i+2]*size);
            vertices.push_back(face[i+3]);
            vertices.push_back(face[i+4]);
            vertices.push_back(face[i+5]);
        }

        triangles.push_back(ind0);
        triangles.push_back(ind0+1);
        triangles.push_back(ind0+3);

        triangles.push_back(ind0+1);
        triangles.push_back(ind0+2);
        triangles.push_back(ind0+3);
    }

    void SetFaces(std::vector<float>& vertices, std::vector<unsigned int>& triangles, bool faces[6], glm::vec3 position, float size)
    {
        if (faces[0])
        {
            AddFace(vertices, triangles, FrontFace, position, size);
        }
        if (faces[1])
        {
            AddFace(vertices, triangles, BackFace, position, size);
        }
        if (faces[2])
        {
            AddFace(vertices, triangles, RightFace, position, size);
        }
        if (faces[3])
        {
            AddFace(vertices, triangles, LeftFace, position, size);
        }
        if (faces[4])
        {
            AddFace(vertices, triangles, TopFace, position, size);
        }
        if (faces[5])
        {
            AddFace(vertices, triangles, BottomFace, position, size);
        }
    }
}
