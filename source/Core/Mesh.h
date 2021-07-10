#pragma once
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"

class CMaterial;
struct CMesh
{
	CMesh(CMaterial const* material);
	~CMesh();
	void InitCube();

	unsigned int GetNumberElements() const { return m_triangles.size(); }
	unsigned int GetNumberVertices() const { return m_vertices.size(); }
	void CreateBufferObjects();

	std::vector<float> m_vertices;
	std::vector<unsigned int> m_triangles;
	unsigned int m_vertexArrayObject = 0;
	unsigned int m_vertexBufferObject = 0;
	unsigned int m_elemetsBufferObject = 0;
	CMaterial const* m_material;
};
