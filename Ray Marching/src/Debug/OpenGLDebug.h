#pragma once

#include <glad/glad.h>

namespace Debug
{
	enum DebugLevel
	{
		None = 0, 
		High = 1, 
		Medium = 2, 
		Low = 3, 
		Notification = 4
	};

	void EnableGLDebugging();
	void OpenGLLogMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
}