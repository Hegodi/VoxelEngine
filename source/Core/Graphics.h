#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Mesh.h"
#include "World.h"
#include "Materials/Shader.h"

class CGraphics
{

public:
	CGraphics();
	~CGraphics();
	void Init();
	void Render(GLFWwindow* window, CWorld const& world);

private:
	void DrawMesh(CMesh const* mesh, CCamera const* const camera);
};