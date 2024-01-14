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

	void Renderer::Submit(GameObject* gameobject)
	{
		auto shader = gameobject->GetMesh().GetShader();
		auto vertexArray = gameobject->GetMesh().GetVertexArray();

		shader->Bind();
		shader->SetUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		shader->SetUniformMat4("u_Model", gameobject->GetTransform().GetMatrix());

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}