#include "VertexArray.h"

VertexArray::VertexArray()
{
	glCreateVertexArrays(1, &m_ID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_ID);
}

void VertexArray::LinkVertexBuffer(const VertexBuffer& vertexBuffer, GLuint layout, GLuint numberOfComponents)
{
	glVertexArrayVertexBuffer(m_ID, layout, vertexBuffer.GetID(), 0, numberOfComponents * sizeof(float));
	
	glVertexArrayAttribFormat(m_ID, layout, numberOfComponents, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(m_ID, layout, layout);
	glEnableVertexArrayAttrib(m_ID, layout);
}

void VertexArray::LinkElementBuffer(const ElementBuffer& elementBuffer)
{
	glVertexArrayElementBuffer(m_ID, elementBuffer.GetID());
}

const void VertexArray::Bind() const
{
	glBindVertexArray(m_ID);
}

const void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}
