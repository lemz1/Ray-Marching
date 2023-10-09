#include "FullscreenQuad.h"

#include "../Core/Application.h"

Mesh CreateFullscreenQuad()
{
	return Mesh
	{
		std::vector<glm::vec3>
		{
			glm::vec3(-1,  1, 0),
			glm::vec3(1,  1, 0),
			glm::vec3(-1, -1, 0),
			glm::vec3(1, -1, 0),
		},
		std::vector<glm::vec2>
		{
			glm::vec2(0, 1),
			glm::vec2(1, 1),
			glm::vec2(0, 0),
			glm::vec2(1, 0),
		},
		std::vector<uint32_t>
		{
			0, 1, 2,
			1, 3, 2
		}
	};
}

FullscreenQuad::FullscreenQuad()
	: m_Mesh(CreateFullscreenQuad())
{
	m_Shader = Shader::CreateVertexFragmentShader(
		"assets/shaders/framebuffer.vert",
		"assets/shaders/framebuffer.frag"
	);

	m_FrameBuffer = std::make_shared<FrameBuffer>();
	TextureSpecification spec;
	spec.width = 1280;
	spec.height = 720;
	spec.format = TextureFormat::RGBA8;
	m_FrameBuffer->AddTexture(spec);

	m_VertexBuffer = new VertexBuffer(m_Mesh.vertices.data(), sizeof(glm::vec3) * m_Mesh.vertices.size());
	m_TexCoordBuffer = new VertexBuffer(m_Mesh.texCoords.data(), sizeof(glm::vec2) * m_Mesh.texCoords.size());
	m_ElementBuffer = new ElementBuffer(m_Mesh.indices.data(), sizeof(uint32_t) * m_Mesh.indices.size());

	m_VertexArray = new VertexArray();
	m_VertexArray->LinkVertexBuffer(*m_VertexBuffer, 0, 3);
	m_VertexArray->LinkVertexBuffer(*m_TexCoordBuffer, 1, 2);
	m_VertexArray->LinkElementBuffer(*m_ElementBuffer);
}

FullscreenQuad::~FullscreenQuad()
{
	delete m_VertexArray;
	delete m_VertexBuffer;
	delete m_TexCoordBuffer;
	delete m_ElementBuffer;
}

void FullscreenQuad::Draw()
{
	m_Shader->StartProgram();

	TextureSpecification spec;
	spec.width = Application::GetWidth();
	spec.height = Application::GetHeight();
	spec.format = TextureFormat::RGBA8;
	m_FrameBuffer->SetTextureSpecification(spec, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_FrameBuffer->GetTextureID(0));

	GLuint textureLocation = glGetUniformLocation(m_Shader->GetID(), "u_Texture");
	glUniform1i(textureLocation, 0);

	m_VertexArray->Bind();

	glDrawElements(GL_TRIANGLES, m_Mesh.indices.size(), GL_UNSIGNED_INT, 0);

	m_VertexArray->Unbind();
	m_Shader->StopProgram();
}
