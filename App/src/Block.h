#pragma once

#include <Engine.h>

namespace GLCraft
{
	enum class BlockFaceType
	{
		FRONT = 0, BACK, LEFT, RIGHT, TOP, BOTTOM
	};

	enum class BlockID
	{
		AIR = 0,
		DIRT, GRASS, STONE
	};

	const unsigned int BLOCK_VERTEX_AMOUNT = VERTEX_AMOUNT_CUBE * 3;

	class Block
	{
	public:
		static void SetTexturePaths(BlockID blockID, std::string* texturePaths);
	public:
		Block(BlockID blockID = BlockID::AIR);
		~Block();

		Engine::Vertex* GetFace(BlockFaceType faceType);

		inline Engine::Vertex* GetVertices() { return m_Vertices.data(); }
		inline unsigned int* GetIndices() { return m_Indices.data(); }

		inline BlockID GetBlockID() const { return m_BlockID; }
	private:
		void SetVerticesAndIndices();
		void SetTextures();
	private:
		std::array<Engine::Vertex, BLOCK_VERTEX_AMOUNT> m_Vertices;
		std::array<unsigned int, INDEX_AMOUNT_CUBE> m_Indices;

		BlockID m_BlockID;

		std::array<std::shared_ptr<Engine::Texture2D>, 6> m_Textures;
	};
}