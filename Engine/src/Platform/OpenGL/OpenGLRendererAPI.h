#pragma once

#include "Engine/Renderer/RendererAPI.h"

namespace Engine
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		void SetClearColor(const glm::vec4& color) override;
		void Clear() override;

		void SetDepth(bool enabled) override;
		void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};
}