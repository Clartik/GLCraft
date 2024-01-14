#pragma once

#include "Engine/Renderer/VertexArray.h"
#include "Engine/Renderer/Shader.h"

namespace Engine
{
	struct Vertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
	};

	class Mesh
	{
	public:
		static void CreateQuad(std::vector<Vertex>& vertices, const glm::vec2& size, const glm::vec4& color);
		static void CreateCube(std::vector<Vertex>& vertices, const glm::vec3& size, const glm::vec4& color);
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