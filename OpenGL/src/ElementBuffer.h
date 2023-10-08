#pragma once

#include <glad/glad.h>

class ElementBuffer
{
public:
	ElementBuffer() = default;
	ElementBuffer(const void* indices, GLsizeiptr size);
	~ElementBuffer();

	const void Bind() const;
	const void Unbind() const;

	const GLuint GetID() const { return m_ID; }
private:
	GLuint m_ID;
};