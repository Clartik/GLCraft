#pragma once

#include <Engine.h>

#include "Block.h"

namespace GLCraft
{
	const unsigned int CHUNK_HEIGHT = 64, CHUNK_ROWS = 16, CHUNK_COLUMNS = 16;

	class Chunk
	{
	public:
		Chunk(const glm::vec2& startLocation);

		inline Engine::Mesh* GetMesh() { return &m_Mesh; }
		inline Engine::Transform& GetTransform() { return m_Chunk[0][0][0].GetTransform(); }
	private:
		void AddFaceToMesh(const glm::vec3& location, Engine::Vertex* faceVertices);
		void CalculateMesh();
	private:
		std::array<std::array<std::array<Block, CHUNK_COLUMNS>, CHUNK_ROWS>, CHUNK_HEIGHT> m_Chunk;
		Engine::Mesh m_Mesh;

		std::vector<Engine::Vertex> m_Vertices;
		std::vector<unsigned int> m_Indices;
	};
}