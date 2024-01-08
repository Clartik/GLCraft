#pragma once

#include "Engine/Renderer/VertexArray.h"

namespace Engine
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		void Bind() const override;
		void Unbind() const override;

		inline const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const { return m_VBOs; };
		inline const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return m_IBO; };

		void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;
	private:
		unsigned int m_RendererID;
		std::vector<std::shared_ptr<VertexBuffer>> m_VBOs;
		std::shared_ptr<IndexBuffer> m_IBO;
	};
}