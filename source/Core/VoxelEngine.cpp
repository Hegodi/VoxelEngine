#include "VoxelEngine.h"

#include <iostream>

#include "Graphics.h"
#include "World.h"
#include "InputManager.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void CVoxelEngine::Run()
{
	GLFWwindow* window = CreateWindow(800,600, "Voxel Engine");
    if (window == nullptr)
    {
        return;
    }
    CGraphics* graphics = new CGraphics();
    graphics->Init();

    CWorld* world = new CWorld();
    world->AddTriangle();

    CInputManager* inputManager = new CInputManager(EInputMode::Debug);


    int fps = 0;

    float deltaTime = 0.0f;
    float tLast = 0;
    char titleBuffer[128];
    while (!glfwWindowShouldClose(window))
    {
        float t = glfwGetTime();
        deltaTime = t - tLast;
        tLast = t;
        fps = 1.0f / deltaTime;
        sprintf_s(titleBuffer, "Voxel Engine FPS: %d", fps);
        glfwSetWindowTitle(window, titleBuffer);


        graphics->Render(window, *world);

        inputManager->ProcessInput(window, *world, deltaTime);

        world->Update(deltaTime);

    }

    delete inputManager;
    delete world;
    delete graphics;

    glfwDestroyWindow(window);
    glfwTerminate();
}

GLFWwindow* CVoxelEngine::CreateWindow(unsigned int width, unsigned int height, const char* title)
{	
    glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL)
    {
        std::cout << "ERROR: Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return NULL;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return NULL;
    }

    glfwSwapInterval(0);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwSetCursorPos(window, width * 0.5, height * 0.5);
    return window;
}

