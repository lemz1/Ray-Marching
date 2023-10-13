#include "Shader.h"

std::string GetFileContents(const char* filePath)
{
	std::ifstream in(filePath, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return contents;
	}
	throw(errno);
}

void CompileErrors(GLuint id, GLenum type)
{
	GLint hasCompiled;
	char infoLog[1024];
	switch (type)
	{
		case GL_PROGRAM:
			glGetProgramiv(id, GL_LINK_STATUS, &hasCompiled);
			if (hasCompiled == GL_FALSE)
			{
				glGetProgramInfoLog(id, 1024, NULL, infoLog);
				std::cout << "SHADER LINKING ERROR: " << "\n" << infoLog << std::endl;
			}
			break;
		case GL_VERTEX_SHADER | GL_FRAGMENT_SHADER | GL_COMPUTE_SHADER:
			glGetShaderiv(id, GL_COMPILE_STATUS, &hasCompiled);
			if (hasCompiled == GL_FALSE)
			{
				glGetShaderInfoLog(id, 1024, NULL, infoLog);
				std::cout << "SHADER COMPILATION ERROR: " << "\n" << infoLog << std::endl;
			}
	}
}

GLuint CompileShader(const char* filePath, GLenum type)
{
	std::string shaderString = GetFileContents(filePath);
	const char* shaderSource = shaderString.c_str();

	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &shaderSource, NULL);

	glCompileShader(shader);
	CompileErrors(shader, type);

	return shader;
}

Shader::Shader(GLuint ID)
	: m_ID(ID)
{}

Shader::~Shader()
{
	glDeleteProgram(m_ID);
}

void Shader::StartProgram()
{
	glUseProgram(m_ID);
}

void Shader::StopProgram()
{
	glUseProgram(0);
}

std::shared_ptr<Shader> Shader::CreateVertexFragmentShader(const char* vertexFilePath, const char* fragmentFilePath)
{
	GLuint vertexShader = CompileShader(vertexFilePath, GL_VERTEX_SHADER);
	GLuint fragmentShader = CompileShader(fragmentFilePath, GL_FRAGMENT_SHADER);

	GLuint ID = glCreateProgram();

	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	glLinkProgram(ID);
	CompileErrors(ID, GL_PROGRAM);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return std::make_shared<Shader>(ID);
}

std::shared_ptr<Shader> Shader::CreateComputeShader(const char* computeFilePath)
{
	GLuint computeShader = CompileShader(computeFilePath, GL_COMPUTE_SHADER);

	GLuint ID = glCreateProgram();

	glAttachShader(ID, computeShader);

	glLinkProgram(ID);
	CompileErrors(ID, GL_PROGRAM);

	glDeleteShader(computeShader);

	return std::make_shared<Shader>(ID);
}
