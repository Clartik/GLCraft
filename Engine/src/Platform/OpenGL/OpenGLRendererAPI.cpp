#include "pch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Engine
{
	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::ShowDepth(bool enabled)
	{
		if (enabled)
		{
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);
		}
		else
		{
			glDisable(GL_DEPTH_TEST);
		}
	}

	void OpenGLRendererAPI::ShowWireframe()
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	void OpenGLRendererAPI::SetWindingOrder(bool counterClockwise)
	{
		if (counterClockwise)
			glFrontFace(GL_CCW);
		else
			glFrontFace(GL_CW);
	}

	void OpenGLRendererAPI::SetCullingMode(CullingMode mode)
	{
		switch (mode)
		{
		case Engine::CullingMode::NONE:
			glDisable(GL_CULL_FACE);
			break;
		case Engine::CullingMode::BACK:
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
			break;
		case Engine::CullingMode::FRONT:
			glEnable(GL_CULL_FACE);
			glCullFace(GL_FRONT);
			break;
		case Engine::CullingMode::BOTH:
			glEnable(GL_CULL_FACE);
			glCullFace(GL_FRONT_AND_BACK);
			break;
		default:
			break;
		}
	}

	void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
	{
		unsigned int count = vertexArray->GetIndexBuffer()->GetCount();
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}
}
