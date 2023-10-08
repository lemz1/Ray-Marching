#pragma once

#include <glad/glad.h>

#include "VertexBuffer.h"
#include "ElementBuffer.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void LinkVertexBuffer(const VertexBuffer& vertexBuffer, GLuint layout, GLuint numberOfComponents);
	void LinkElementBuffer(const ElementBuffer& elementBuffer);
	
	const void Bind() const;
	const void Unbind() const;

	const GLuint GetID() const { return m_ID; }
private:
	GLuint m_ID;
};