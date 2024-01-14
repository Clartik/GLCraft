#include "pch.h"
#include "Renderer.h"

namespace Engine
{
	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(Camera& camera)
	{
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjection();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(Mesh* mesh, Transform* transform)
	{
		auto vertexArray = mesh->GetVertexArray();
		auto shader = mesh->GetShader();

		shader->Bind();
		shader->SetUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		shader->SetUniformMat4("u_Model", transform->GetMatrix());

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}