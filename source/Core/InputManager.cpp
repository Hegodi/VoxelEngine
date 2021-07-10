#include "InputManager.h"
#include "MathUtils.h"

CInputManager::CInputManager(EInputMode mode)
    : m_mode(mode)
    , m_mouseDeltaPosX(0.0f)
    , m_mouseDeltaPosY(0.0f)
{
}

void CInputManager::ProcessInput(GLFWwindow* window, CWorld& world, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    PreprocesMouse(window);

	switch (m_mode)
	{
	case Debug:
		ProcessInputDebug(window, world, deltaTime);
		break;
	case Game:
		ProcessInputGame(window, world, deltaTime);
		break;
	default:
		break;
	}
    glfwPollEvents();
}

void CInputManager::PreprocesMouse(GLFWwindow* window)
{
    m_mouseBtnPressed[0] = (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS);
    m_mouseBtnPressed[1] = (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS);
    m_mouseBtnPressed[2] = (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_3) == GLFW_PRESS);

    int width, height;
    glfwGetWindowSize(window, &width, &height);

    float centerX = width * 0.5f;
    float centerY = height * 0.5f;

    double posX, posY;
    glfwGetCursorPos(window, &posX, &posY);
    m_mouseDeltaPosX = posX - centerX;
    m_mouseDeltaPosY = posY - centerY;

    glfwSetCursorPos(window, width * 0.5, height * 0.5);
}

void CInputManager::ProcessInputDebug(GLFWwindow* window, CWorld& world, float deltaTime)
{
    float rotationPitch = -m_mouseSensibility * m_mouseDeltaPosY;
    if (m_invertYaxis)
    {
        rotationPitch *= -1;
    }
    float rotationYaw = -m_mouseSensibility * m_mouseDeltaPosX;


    float movementForward = 0.0f;
    float movementRight = 0.0f;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        movementForward = 1.0f;
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        movementForward = -1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        movementRight = -1.0f;
    }
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        movementRight = 1.0f;
    }

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        m_cameraSpeed = MathUtils::Clamp(m_cameraSpeed + 1.0f, 1.0f, 100.0f);
    }
    else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        m_cameraSpeed = MathUtils::Clamp(m_cameraSpeed - 1.0f, 1.0f, 100.0f);
    }

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        world.GetCamera()->SetPosition(glm::vec3(0.0f, 50.0f, 0.0f));
        world.GetCamera()->SetRotation(-10.0f, 0.0f);
    }
    world.GetCamera()->Move(deltaTime * movementForward * m_cameraSpeed, deltaTime * movementRight * m_cameraSpeed);
    world.GetCamera()->Rotate(deltaTime * rotationPitch * m_cameraRotationSpeed, deltaTime * rotationYaw * m_cameraRotationSpeed);
}

void CInputManager::ProcessInputGame(GLFWwindow* window, CWorld& world, float deltaTime)
{
}
