#pragma once

#include <Engine.h>

namespace GLCraft
{
	enum class BlockFaceType
	{
		FRONT = 0, BACK, LEFT, RIGHT, TOP, BOTTOM
	};

	class Block
	{
	public:
		Block();
		Block(const Engine::Transform& transform);

		Engine::Vertex* GetFace(BlockFaceType faceType);

		inline Engine::Vertex* GetVertices() { return m_Vertices.data(); }
		unsigned int* GetIndices() const;
	private:
		Engine::Transform m_Transform;

		std::array<Engine::Vertex, VERTEX_AMOUNT_CUBE> m_Vertices;
		std::unordered_map<BlockFaceType, std::array<unsigned int, INDEX_AMOUNT_QUAD>> m_IndicesMap;
	};
}