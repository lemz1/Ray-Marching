#include "ElementBuffer.h"

ElementBuffer::ElementBuffer(const void* indices, GLsizeiptr size)
{
	glCreateBuffers(1, &m_ID);
	glNamedBufferData(m_ID, size, indices, GL_STATIC_DRAW);
}

ElementBuffer::~ElementBuffer()
{
	glDeleteBuffers(1, &m_ID);
}

const void ElementBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

const void ElementBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}