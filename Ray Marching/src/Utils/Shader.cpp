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

void compileErrors(GLuint id, const char* type)
{
	GLint hasCompiled;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(id, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(id, 1024, NULL, infoLog);
			std::cout << "SHADER COMPILATION ERROR for: " << type << "\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(id, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(id, 1024, NULL, infoLog);
			std::cout << "SHADER LINKING ERROR for: " << type << "\n" << infoLog << std::endl;
		}
	}
}

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
	std::string vertexString = GetFileContents(vertexFilePath);
	const char* vertexSource = vertexString.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);

	glCompileShader(vertexShader);
	compileErrors(vertexShader, "VERTEX");


	std::string fragmentString = GetFileContents(fragmentFilePath);
	const char* fragmentSource = fragmentString.c_str();

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);

	glCompileShader(fragmentShader);
	compileErrors(fragmentShader, "FRAGMENT");


	GLuint ID = glCreateProgram();

	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	glLinkProgram(ID);
	compileErrors(ID, "PROGRAM");

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	std::shared_ptr<Shader> shader = std::make_shared<Shader>();
	shader->m_ID = ID;

	return shader;
}
