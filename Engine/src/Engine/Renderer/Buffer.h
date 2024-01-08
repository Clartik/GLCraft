#pragma once

namespace Engine
{
	enum class ShaderDataType
	{
		None = 0,
		Float, Float2, Float3, Float4,
		Mat3, Mat4,
		Int, Int2, Int3, Int4,
		Bool
	};

	static unsigned int GetShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case Engine::ShaderDataType::None:		break;
			case Engine::ShaderDataType::Float:		return 4;
			case Engine::ShaderDataType::Float2:	return 4 * 2;
			case Engine::ShaderDataType::Float3:	return 4 * 3;
			case Engine::ShaderDataType::Float4:	return 4 * 4;
			case Engine::ShaderDataType::Mat3:		return 4 * 3 * 3;
			case Engine::ShaderDataType::Mat4:		return 4 * 4 * 4;
			case Engine::ShaderDataType::Int:		return 4;
			case Engine::ShaderDataType::Int2:		return 4 * 2;
			case Engine::ShaderDataType::Int3:		return 4 * 3;
			case Engine::ShaderDataType::Int4:		return 4 * 4;
			case Engine::ShaderDataType::Bool:		return 1;
			default:								break;
		}

		CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		unsigned int Size;
		unsigned int Offset;
		bool Normalized;

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Size(GetShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{
		}

		unsigned int GetComponentCount() const
		{
			switch (Type)
			{
				case Engine::ShaderDataType::None:		break;
				case Engine::ShaderDataType::Float:		return 1;
				case Engine::ShaderDataType::Float2:	return 2;
				case Engine::ShaderDataType::Float3:	return 3;
				case Engine::ShaderDataType::Float4:	return 4;
				case Engine::ShaderDataType::Mat3:		return 3 * 3;
				case Engine::ShaderDataType::Mat4:		return 4 * 4;
				case Engine::ShaderDataType::Int:		return 1;
				case Engine::ShaderDataType::Int2:		return 2;
				case Engine::ShaderDataType::Int3:		return 3;
				case Engine::ShaderDataType::Int4:		return 4;
				case Engine::ShaderDataType::Bool:		return 1;
				default:								break;
			}

			CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout() = default;
		BufferLayout(std::initializer_list<BufferElement> elements)
			: m_Elements(elements)
		{
			CalculateOffsetAndStride();
		}

		inline unsigned int GetStride() const { return m_Stride; }
		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		inline std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		inline std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		inline std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		inline std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
	private:
		void CalculateOffsetAndStride()
		{
			m_Stride = 0;
			unsigned int offset = 0;

			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}
	private:
		std::vector<BufferElement> m_Elements;
		unsigned int m_Stride = 0;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

		static std::shared_ptr<VertexBuffer> Create(float* vertices, unsigned int size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual unsigned int GetCount() const = 0;

		static std::shared_ptr<IndexBuffer> Create(unsigned int* indices, unsigned int count);
	};
}