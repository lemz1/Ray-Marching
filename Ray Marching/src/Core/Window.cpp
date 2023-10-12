#include "Window.h"

#include <iostream>

GLFWwindow* Window::Create(const char* title, uint32_t width, uint32_t height)
{
    // create window
    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);

    if (window == NULL)
    {
        glfwTerminate();
        std::cout << "Failed to create window" << std::endl;
        return nullptr;
    }
    glfwMakeContextCurrent(window);

    return window;
}
