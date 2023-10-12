#include <iostream>
#include <cassert>

#include "OpenGLDebug.h"

// thanks Cherno for the opengl debug stuff (this is from the OpenGl-Core repo)
// is it going to be continued sometime?

static Debug::DebugLevel s_DebugLevel = Debug::DebugLevel::High;

void Debug::OpenGLLogMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    switch (severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:
            if ((int)s_DebugLevel > 0)
            {
                std::cout << "[HIGH] OpenGL Debug " << message << std::endl;
                if ((int)s_DebugLevel == 1)
                {
                    assert(false && "A high OpenGL error occurred.");
                }
            }
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            if ((int)s_DebugLevel > 1)
            {
                std::cout << "[MEDIUM] OpenGL Debug " << message << std::endl;
            }
            break;
        case GL_DEBUG_SEVERITY_LOW:
            if ((int)s_DebugLevel > 2)
            {
                std::cout << "[LOW] OpenGL Debug " << message << std::endl;
            }
            break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            if ((int)s_DebugLevel > 3)
            {
                std::cout << "[NOTIFICATION] OpenGL Debug " << message << std::endl;
            }
            break;
    }
}


void Debug::EnableGLDebugging()
{
	glDebugMessageCallback(OpenGLLogMessage, nullptr);
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
}