#include "Window.h"

#include <iostream>

GLFWwindow* Window::CreateWindow()
{
    InitializeOpenGL();

    // create window
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Ray Marching", NULL, NULL);
    if (window == NULL)
    {
        glfwTerminate();
        std::cout << "Failed to create window" << std::endl;
        return nullptr;
    }
    glfwMakeContextCurrent(window);

    if (!InitializeGlad())
    {
        std::cout << "Failed to initialize glad" << std::endl;
        return nullptr;
    }

    return window;
}

void Window::InitializeOpenGL()
{
    glfwInit();

    // set opengl version to 4.6
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    // use core profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

bool Window::InitializeGlad()
{
    return gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}
