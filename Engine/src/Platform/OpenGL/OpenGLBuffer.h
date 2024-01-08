#pragma once

#include "Engine/Renderer/Buffer.h"

namespace Engine
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, unsigned int size);
		~OpenGLVertexBuffer();

		void Bind() const override;
		void Unbind() const override;

		inline const BufferLayout& GetLayout() const override { return m_Layout; }
		inline void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
	private:
		unsigned int m_RendererID;
		BufferLayout m_Layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(unsigned int* indices, unsigned int count);
		~OpenGLIndexBuffer();

		void Bind() const override;
		void Unbind() const override;

		inline unsigned int GetCount() const override { return m_Count; }
	private:
		unsigned int m_RendererID;
		unsigned int m_Count;
	};
}