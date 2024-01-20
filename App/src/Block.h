#pragma once

#include <Engine.h>

namespace GLCraft
{
	enum class BlockFaceType : int
	{
		FRONT = 0, BACK, LEFT, RIGHT, TOP, BOTTOM
	};

	enum class BlockID : unsigned int
	{
		AIR = 0,
		DIRT, GRASS, STONE
	};

	const unsigned int BLOCK_VERTEX_AMOUNT = VERTEX_AMOUNT_CUBE * 3;

	class Block
	{
	public:
		Block();
		Block(const Engine::Transform& transform, BlockID blockID);

		void Render();

		Engine::Vertex* GetFace(BlockFaceType faceType);

		inline Engine::Vertex* GetVertices() { return m_Vertices.data(); }
		inline unsigned int* GetIndices() { return m_Indices.data(); }

		inline Engine::Transform& GetTransform() { return m_Transform; }
		inline BlockID GetBlockID() { return m_ID; }
	private:
		void SetVerticesAndIndices();
		void SetTextures();
	private:
		std::array<Engine::Vertex, BLOCK_VERTEX_AMOUNT> m_Vertices;
		std::array<unsigned int, INDEX_AMOUNT_CUBE> m_Indices;

		Engine::Transform m_Transform;
		BlockID m_ID;

		std::array<std::shared_ptr<Engine::Texture2D>, 6> m_Textures;
	};
}