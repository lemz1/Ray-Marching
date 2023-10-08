#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* vertices, GLsizeiptr size)
{
	glCreateBuffers(1, &m_ID);
	glNamedBufferData(m_ID, size, vertices, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_ID);
}

const void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

const void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}