#pragma once

#include <Engine.h>

namespace GLCraft
{
	enum class BlockFaceType
	{
		FRONT = 0, BACK, LEFT, RIGHT, TOP, BOTTOM
	};

	const float BLOCK_VERTEX_SIZE = 1.0f;
	const unsigned int BLOCK_VERTEX_AMOUNT = VERTEX_AMOUNT_CUBE * 3;

	class Block
	{
	public:
		Block();
		Block(const Engine::Transform& transform);

		Engine::Vertex* GetFace(BlockFaceType faceType);

		inline Engine::Vertex* GetVertices() { return m_Vertices.data(); }
		inline unsigned int* GetIndices() { return m_Indices.data(); }
		inline Engine::Transform& GetTransform() { return m_Transform; }
	private:
		void SetVerticesAndIndices();
	private:
		Engine::Transform m_Transform;

		std::array<Engine::Vertex, BLOCK_VERTEX_AMOUNT> m_Vertices;
		std::array<unsigned int, INDEX_AMOUNT_CUBE> m_Indices;

		std::unordered_map<BlockFaceType, std::array<unsigned int, INDEX_AMOUNT_QUAD>> m_IndicesMap;
	};
}