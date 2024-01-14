#pragma once

#include "RenderCommand.h"
#include "Shader.h"

#include "Engine/Scene/Camera.h"
#include "Engine/Scene/Mesh.h"

namespace Engine
{
	class Renderer
	{
	public:
		static void BeginScene(Camera& camera);
		static void EndScene();

		static void Submit(Mesh* mesh, Transform* transform);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* s_SceneData;
	};
}