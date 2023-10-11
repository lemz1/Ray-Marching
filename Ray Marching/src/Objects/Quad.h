#pragma once

#include "../BufferObjects/VertexArray.h"
#include "../BufferObjects/VertexBuffer.h"
#include "../BufferObjects/ElementBuffer.h"
#include "../Utils/Transform.h"
#include "../Utils/Mesh.h"
#include "../Utils/Shader.h"
#include "../Utils/Camera.h"

class Quad
{
public:
	Quad() = default;
	Quad(std::shared_ptr<Shader> shader, std::shared_ptr<Camera> camera);
	Quad(std::shared_ptr<Shader> shader, std::shared_ptr<Camera> camera, const Transform& transform);
	~Quad();

	const Transform& GetTransform() { return m_Transform; }
	void SetTransform(const Transform& transform) { m_Transform = transform; }

	void Draw();
private:
	void CreateBuffers();
private:
	Transform m_Transform;
	Mesh m_Mesh;
	std::shared_ptr<Shader> m_Shader;
	std::shared_ptr<Camera> m_Camera;

	VertexArray* m_VertexArray;
	VertexBuffer* m_VertexBuffer;
	VertexBuffer* m_TexCoordBuffer;
	ElementBuffer* m_ElementBuffer;
};