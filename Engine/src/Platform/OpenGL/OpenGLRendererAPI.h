#pragma once

#include "Engine/Renderer/RendererAPI.h"

namespace Engine
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void ShowDepth(bool enabled) override;
		virtual void ShowWireframe() override;

		virtual void SetWindingOrder(bool counterClockwise) override;
		virtual void SetCullingMode(CullingMode mode) override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};
}