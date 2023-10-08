#pragma once

#include <glad/glad.h>
#include <string>
#include <istream>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string GetFileContents(const char* filename);

class Shader
{
public:
	Shader(const char* vertexFile, const char* fragmentFile);
	~Shader();
	void StartProgram();
	void StopProgram();

	const GLuint GetID() const { return m_ID; }
private:
	void compileErrors(GLuint id, const char* type);
private:
	GLuint m_ID;
};