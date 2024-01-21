#pragma once

#include <Engine.h>

#include "Block.h"

namespace GLCraft
{
	class Chunk
	{
	public:
		const static unsigned int MAX_HEIGHT = 5, MAX_ROWS = 16, MAX_COLUMNS = 16;
	public:
		Chunk(const glm::vec3& startLocation);

		inline Engine::Mesh* GetMesh() { return &m_Mesh; }
		inline Engine::Transform& GetTransform() { return m_Transform; }
	private:
		void AddFaceToMesh(const glm::vec3& location, Engine::Vertex* faceVertices);
		void CalculateMesh();
	private:
		Engine::Transform m_Transform;

		std::array<std::array<std::array<Block, MAX_COLUMNS>, MAX_ROWS>, MAX_HEIGHT> m_Chunk;
		Engine::Mesh m_Mesh;

		std::vector<Engine::Vertex> m_Vertices;
		std::vector<unsigned int> m_Indices;
	};
}