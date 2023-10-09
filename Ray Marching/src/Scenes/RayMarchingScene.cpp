#include "RayMarchingScene.h"

#include <glad/glad.h>

void RayMarchingScene::OnCreate()
{

	m_FullscreenQuad = new FullscreenQuad();

	std::shared_ptr<Shader> shader = Shader::CreateVertexFragmentShader(
		"assets/shaders/default.vert",
		"assets/shaders/default.frag"
	);

	m_Quad = new Quad(shader);
}

void RayMarchingScene::OnUpdate(double deltaTime)
{
	m_FullscreenQuad->GetFrameBuffer()->Bind();

	glClearColor(.1f, .1f, .1f, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	m_Quad->Draw();

	m_FullscreenQuad->GetFrameBuffer()->Unbind();

	m_FullscreenQuad->Draw();
}

void RayMarchingScene::OnDestroy()
{
	delete m_Quad;
	delete m_FullscreenQuad;
}
