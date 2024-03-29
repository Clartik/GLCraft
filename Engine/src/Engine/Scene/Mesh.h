#pragma once

#include "Engine/Renderer/VertexArray.h"
#include "Engine/Renderer/Shader.h"

const unsigned int VERTEX_AMOUNT_QUAD = 4;
const unsigned int INDEX_AMOUNT_QUAD = 6;

const unsigned int VERTEX_AMOUNT_CUBE = 8;
const unsigned int INDEX_AMOUNT_CUBE = 36;

namespace Engine
{
	struct Vertex
	{
		glm::vec3 Position;
		glm::vec2 TexCoord;
		glm::vec4 Color;
	};

	class Mesh
	{
	public:
		static void CreateQuad(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, 
			const glm::vec2& size, const glm::vec4& color);
		static void CreateCube(std::vector<Vertex>& vertices, const glm::vec4& color);
		static void CreateCube(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, 
			const glm::vec4& color);
	public:
		Mesh();
		~Mesh();

		void LoadVertices(Vertex* verts, unsigned int size);
		void LoadIndices(unsigned int* indices, unsigned int count);

		inline void LoadShader(std::shared_ptr<Shader> shader) { m_Shader = shader; }

		inline const std::shared_ptr<VertexArray> GetVertexArray() { return m_VAO; }
		inline const std::shared_ptr<Shader> GetShader() { return m_Shader; }
	private:
		std::shared_ptr<VertexArray> m_VAO;
		std::shared_ptr<Shader> m_Shader;
	};
}