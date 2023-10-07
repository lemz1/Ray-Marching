#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

const char* vertexSource = 
R"glsl(
#version 460 core
layout (location = 0) in vec3 a_Position;
void main()
{
	gl_Position = vec4(a_Position, 1.0);
}
)glsl";

const char* fragmentSource = 
R"glsl(
#version 460 core
out vec4 fragColor;
void main()
{
	fragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
)glsl";

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLfloat vertices[] =
	{
		 0,     0.5f, 0,
		-0.5f, -0.5f, 0,
		 0.5f, -0.5f, 0
	};
	

	GLFWwindow* window = glfwCreateWindow(1280, 720, "Ray Marching", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create window!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 1280, 720);

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	GLuint program = glCreateProgram();

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	GLuint vertexArray;
	glCreateVertexArrays(1, &vertexArray);

	GLuint vertexBuffer;
	glCreateBuffers(1, &vertexBuffer);

	glNamedBufferData(vertexBuffer, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexArrayVertexBuffer(vertexArray, 0, vertexBuffer, 0, 3 * sizeof(float));
	glEnableVertexArrayAttrib(vertexArray, 0);
	glVertexArrayAttribFormat(vertexArray, 0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(vertexArray, 0, 0);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(program);
		glBindVertexArray(vertexArray);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &vertexArray);
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteProgram(program);

	glfwDestroyWindow(window);
	glfwTerminate();
}
