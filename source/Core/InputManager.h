#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "World.h"

enum EInputMode
{
	Debug,
	Game
};

class CInputManager
{
public:
	CInputManager(EInputMode mode);

	void ProcessInput(GLFWwindow* window, CWorld& world, float deltaTime);

private:
	void PreprocesMouse(GLFWwindow* window);
	void ProcessInputDebug(GLFWwindow* window, CWorld& world, float deltaTime);
	void ProcessInputGame(GLFWwindow* window, CWorld& world, float deltaTime);

public:
	float m_mouseSensibility = 0.6f;
	bool m_invertYaxis = false;

private:
	EInputMode m_mode;
	bool m_mouseBtnPressed[3];
	float m_mouseDeltaPosX;
	float m_mouseDeltaPosY;

	float m_cameraSpeed = 2.0f;
	float m_cameraRotationSpeed = 90.0f;
};
