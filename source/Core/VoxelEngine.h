#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class CWorld;

class CVoxelEngine
{
public:
	CVoxelEngine() {}
	void Run();

private:
	GLFWwindow* CreateWindow(unsigned int width, unsigned int height, const char* title);
};