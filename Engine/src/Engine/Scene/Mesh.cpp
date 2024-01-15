#include "pch.h"
#include "Mesh.h"

namespace Engine
{
	void Mesh::CreateQuad(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, 
		const glm::vec2& size, const glm::vec4& color)
	{
		vertices.resize(VERTEX_AMOUNT_QUAD);
		indices.resize(INDEX_AMOUNT_QUAD);

		vertices[0].Position = { -size.x, -size.y, 0.0f };
		vertices[1].Position = {  size.x, -size.y, 0.0f };
		vertices[2].Position = {  size.x,  size.y, 0.0f };
		vertices[3].Position = { -size.x,  size.y, 0.0f };

		vertices[0].TexCoord = { 0, 0 };
		vertices[1].TexCoord = { 1, 0 };
		vertices[2].TexCoord = { 1, 1 };
		vertices[3].TexCoord = { 0, 1 };

		indices = {
			// FRONT
			0, 1, 2,
			2, 3, 0
		};

		for (int i = 0; i < VERTEX_AMOUNT_QUAD; i++)
			vertices[i].Color = color;
	}

	void Mesh::CreateCube(std::vector<Vertex>& vertices, const glm::vec4& color)
	{
		const int size = 1;

		vertices.resize(VERTEX_AMOUNT_CUBE);

		vertices[0].Position = { -size, -size,  size };
		vertices[1].Position = {  size, -size,  size };
		vertices[2].Position = {  size,  size,  size };
		vertices[3].Position = { -size,  size,  size };

		vertices[4].Position = { -size, -size, -size };
		vertices[5].Position = {  size, -size, -size };
		vertices[6].Position = {  size,  size, -size };
		vertices[7].Position = { -size,  size, -size };

		vertices[0].TexCoord = { 0, 0 };
		vertices[1].TexCoord = { 1, 0 };
		vertices[2].TexCoord = { 1, 1 };
		vertices[3].TexCoord = { 0, 1 };

		vertices[4].TexCoord = { 0, 0 };
		vertices[5].TexCoord = { 0, 0 };
		vertices[6].TexCoord = { 1, 1 };
		vertices[7].TexCoord = { 0, 1 };

		for (int i = 0; i < VERTEX_AMOUNT_CUBE; i++)
			vertices[i].Color = color;
	}

	void Mesh::CreateCube(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, 
		const glm::vec4& color)
	{
		CreateCube(vertices, color);

		indices.resize(INDEX_AMOUNT_CUBE);

		indices = {
			// FRONT
			0, 1, 2,
			2, 3, 0,

			// BACK
			5, 4, 7,
			7, 6, 5,

			// LEFT
			4, 0, 3,
			3, 7, 4,

			// RIGHT
			1, 5, 6,
			6, 2, 1,

			// TOP
			3, 2, 6,
			6, 7, 3,

			// BOTTOM
			4, 5, 1,
			1, 0, 4
		};
	}


	Mesh::Mesh()
	{
		m_VAO = VertexArray::Create();
	}

	Mesh::~Mesh()
	{
	}

	void Mesh::LoadVertices(Vertex* verts, unsigned int size)
	{
		std::vector<float> vertices;
		vertices.resize(size / sizeof(float));

		int i = 0;
		for (int vertexIndex = 0; vertexIndex < size / sizeof(Vertex); vertexIndex++)
		{
			vertices[i++] = verts[vertexIndex].Position.x;
			vertices[i++] = verts[vertexIndex].Position.y;
			vertices[i++] = verts[vertexIndex].Position.z;

			vertices[i++] = verts[vertexIndex].TexCoord.x;
			vertices[i++] = verts[vertexIndex].TexCoord.y;

			vertices[i++] = verts[vertexIndex].Color.x;
			vertices[i++] = verts[vertexIndex].Color.y;
			vertices[i++] = verts[vertexIndex].Color.z;
			vertices[i++] = verts[vertexIndex].Color.z;
		}

		std::shared_ptr<VertexBuffer> vbo = VertexBuffer::Create(vertices.data(), size);

		BufferLayout layout = {
			{ Engine::ShaderDataType::Float3, "position" },
			{ Engine::ShaderDataType::Float2, "texCoord" },
			{ Engine::ShaderDataType::Float4, "color" }
		};

		vbo->SetLayout(layout);
		m_VAO->AddVertexBuffer(vbo);
	}

	void Mesh::LoadIndices(unsigned int* indices, unsigned int count)
	{
		std::shared_ptr<IndexBuffer> ibo = IndexBuffer::Create(indices, count);
		m_VAO->SetIndexBuffer(ibo);
	}
}