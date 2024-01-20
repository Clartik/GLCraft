#pragma once

#include <Engine.h>

#include "Block.h"

namespace GLCraft
{
	class Chunk
	{
	public:
		const static unsigned int MAX_HEIGHT = 64, MAX_ROWS = 16, MAX_COLUMNS = 16;
	public:
		Chunk(const glm::vec2& startLocation);

		inline Engine::Mesh* GetMesh() { return &m_Mesh; }
		inline Engine::Transform& GetTransform() { return m_Chunk[0][0][0].GetTransform(); }
	private:
		void AddFaceToMesh(const glm::vec3& location, Engine::Vertex* faceVertices);
		void CalculateMesh();
	private:
		std::array<std::array<std::array<Block, Chunk::MAX_HEIGHT>, Chunk::MAX_ROWS>, Chunk::MAX_COLUMNS> m_Chunk;
		Engine::Mesh m_Mesh;

		std::vector<Engine::Vertex> m_Vertices;
		std::vector<unsigned int> m_Indices;
	};
}