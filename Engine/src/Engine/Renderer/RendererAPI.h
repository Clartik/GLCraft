#pragma once

#include "VertexArray.h"

namespace Engine
{
	enum class CullingMode
	{
		NONE = 0, BACK, FRONT, BOTH
	};

	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1
		};
	public:
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void ShowDepth(bool enabled) = 0;
		virtual void ShowWireframe() = 0;
		virtual void SetWindingOrder(bool counterClockwise) = 0;
		virtual void SetCullingMode(CullingMode mode) = 0;
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

		inline static API GetAPI() { return s_API; }
	private:
		static API s_API;
	};
}