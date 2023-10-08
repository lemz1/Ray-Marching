#pragma once

#include <glad/glad.h>
#include <string>
#include <istream>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include <memory>

class Shader
{
public:
	~Shader();
	void StartProgram();
	void StopProgram();

	static std::shared_ptr<Shader> CreateVertexFragmentShader(const char* vertexFilePath, const char* fragmentFilePath);

	const GLuint GetID() const { return m_ID; }
private:
	GLuint m_ID;
};