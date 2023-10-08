#pragma once

#include <glad/glad.h>

class VertexBuffer
{
public:
	VertexBuffer() = default;
	VertexBuffer(const void* vertices, GLsizeiptr size);
	~VertexBuffer();

	const void Bind() const;
	const void Unbind() const;

	const GLuint GetID() const { return m_ID; }
private:
	GLuint m_ID;
};