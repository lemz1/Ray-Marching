#include "VertexArray.h"

VertexArray::VertexArray()
	: m_ID(0)
{
	glCreateVertexArrays(1, &m_ID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_ID);
}

void VertexArray::LinkVertexBuffer(GLuint vertexBufferID, GLuint layout, GLuint numberOfComponents)
{
	glVertexArrayVertexBuffer(m_ID, layout, vertexBufferID, 0, numberOfComponents * sizeof(float));
	
	glVertexArrayAttribFormat(m_ID, layout, numberOfComponents, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(m_ID, layout, layout);
	glEnableVertexArrayAttrib(m_ID, layout);
}

void VertexArray::LinkElementBuffer(GLuint elementBufferID)
{
	glVertexArrayElementBuffer(m_ID, elementBufferID);
}

const void VertexArray::Bind() const
{
	glBindVertexArray(m_ID);
}

const void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}
