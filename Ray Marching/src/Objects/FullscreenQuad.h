#pragma once

#include "../BufferObjects/VertexArray.h"
#include "../BufferObjects/VertexBuffer.h"
#include "../BufferObjects/ElementBuffer.h"
#include "../BufferObjects/FrameBuffer.h"
#include "../Utils/Mesh.h"
#include "../Utils/Shader.h"


class FullscreenQuad
{
public:
	FullscreenQuad();
	~FullscreenQuad();

	void Draw();

	const std::shared_ptr<FrameBuffer> GetFrameBuffer() const { return m_FrameBuffer; }
private:
	Mesh m_Mesh;
	std::shared_ptr<Shader> m_Shader;
	std::shared_ptr<FrameBuffer> m_FrameBuffer;

	VertexArray* m_VertexArray;
	VertexBuffer* m_VertexBuffer;
	VertexBuffer* m_TexCoordBuffer;
	ElementBuffer* m_ElementBuffer;
};