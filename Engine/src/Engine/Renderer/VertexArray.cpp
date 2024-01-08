#include "pch.h"
#include "VertexArray.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Engine
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:
			{
				CORE_ASSERT(false, "RendererAPI::None is not supported!");
				return nullptr;
			}
			case RendererAPI::OpenGL:
				return new OpenGLVertexArray();
		default:
			break;
		}

		CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}