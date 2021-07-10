#include "Mesh.h"
#include "HelpersVoxels.h"
#include "Materials/Material.h"
#include <iostream>

CMesh::CMesh(CMaterial const* material)
    : m_material(material)
{
}

CMesh::~CMesh()
{
    glDeleteVertexArrays(1, &m_vertexArrayObject);
    glDeleteBuffers(1, &m_vertexBufferObject);
    glDeleteBuffers(1, &m_elemetsBufferObject);
}

void CMesh::InitCube()
{
    bool faces[6] = { true, true, true, true, true, true };

    float size = 0.1f;
    for (int i=0; i<20; i++)
    {
        for (int j=0; j<20; j++)
        {
            int kmax = rand() % 10;
            for (int k=0; k<kmax; k++)
            {
                glm::vec3 position = glm::vec3(i, k, j) * size;
                HelpersVoxels::SetFaces(m_vertices, m_triangles, faces, position, size);
            }
        }
    }

    CreateBufferObjects();
}

void CMesh::CreateBufferObjects()
{
    glDeleteVertexArrays(1, &m_vertexArrayObject);
    glDeleteBuffers(1, &m_vertexBufferObject);
    glDeleteBuffers(1, &m_elemetsBufferObject);


    glGenVertexArrays(1, &m_vertexArrayObject);
    glGenBuffers(1, &m_vertexBufferObject);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(m_vertexArrayObject);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), m_vertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &m_elemetsBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elemetsBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_triangles.size() * sizeof (unsigned int), m_triangles.data(), GL_STATIC_DRAW);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
}

