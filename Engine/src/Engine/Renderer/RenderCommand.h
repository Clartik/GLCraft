#pragma once

#include "RendererAPI.h"

namespace Engine
{
	class RenderCommand
	{
	public:
		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}

		inline static void Clear() 
		{
			s_RendererAPI->Clear();
		}

		inline static void ShowDepth(bool enabled)
		{
			s_RendererAPI->ShowDepth(enabled);
		}

		inline static void ShowWireframe()
		{
			s_RendererAPI->ShowWireframe();
		}

		inline static void SetWindingOrder(bool counterClockwise)
		{
			s_RendererAPI->SetWindingOrder(counterClockwise);
		}

		inline static void SetCullingMode(CullingMode mode)
		{
			s_RendererAPI->SetCullingMode(mode);
		}

		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
		{
			s_RendererAPI->DrawIndexed(vertexArray);
		}
	private:
		static RendererAPI* s_RendererAPI;
	};
}