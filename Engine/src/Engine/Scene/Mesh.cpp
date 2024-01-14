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

		indices = {
			// FRONT
			0, 1, 2,
			2, 3, 0
		};

		for (int i = 0; i < VERTEX_AMOUNT_QUAD; i++)
			vertices[i].Color = color;
	}

	void Mesh::CreateCube(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, 
		const glm::vec3& size, const glm::vec4& color)
	{
		vertices.resize(VERTEX_AMOUNT_CUBE);
		indices.resize(INDEX_AMOUNT_CUBE);

		vertices[0].Position = { -size.x, -size.y, -size.z };
		vertices[2].Position = {  size.x,  size.y, -size.z };
		vertices[1].Position = {  size.x, -size.y, -size.z };
		vertices[3].Position = { -size.x,  size.y, -size.z };

		vertices[4].Position = { -size.x, -size.y, size.z };
		vertices[5].Position = {  size.x, -size.y, size.z };
		vertices[6].Position = {  size.x,  size.y, size.z };
		vertices[7].Position = { -size.x,  size.y, size.z };

		indices = {
			// FRONT
			0, 1, 2,
			2, 3, 0,

			// RIGHT
			4, 0, 3,
			3, 7, 4,

			// BACK
			4, 5, 6,
			6, 7, 4,

			// LEFT
			1, 5, 6,
			6, 2, 1,

			// TOP
			3, 2, 6,
			6, 7, 3,

			// BOTTOM
			4, 5, 1,
			1, 0, 4
		};

		for (int i = 0; i < VERTEX_AMOUNT_CUBE; i++)
			vertices[i].Color = color;
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

			vertices[i++] = verts[vertexIndex].Color.x;
			vertices[i++] = verts[vertexIndex].Color.y;
			vertices[i++] = verts[vertexIndex].Color.z;
			vertices[i++] = verts[vertexIndex].Color.z;
		}

		std::shared_ptr<VertexBuffer> vbo = VertexBuffer::Create(vertices.data(), size);

		BufferLayout layout = {
		{ Engine::ShaderDataType::Float3, "pos" },
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