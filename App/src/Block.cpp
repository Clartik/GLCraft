#include "Block.h"

namespace GLCraft
{
	const glm::vec2& Block::GetTexCoordsOffset(BlockID blockID, BlockFaceType faceType)
	{
		glm::vec2 offset(0.0f);

		switch (blockID)
		{
			case GLCraft::BlockID::AIR:
				return offset;
			case GLCraft::BlockID::DIRT:
			{
				offset.x = 0;
				offset.y = 15;
				return offset;
			}
			case GLCraft::BlockID::GRASS:
			{
				switch (faceType)
				{
					case GLCraft::BlockFaceType::FRONT:
					case GLCraft::BlockFaceType::BACK:
					case GLCraft::BlockFaceType::LEFT:
					case GLCraft::BlockFaceType::RIGHT:
					{
						offset.x = 1;
						offset.y = 15;
						break;
					}
					case GLCraft::BlockFaceType::TOP:
					{
						offset.x = 2;
						offset.y = 15;
						break;
					}
					case GLCraft::BlockFaceType::BOTTOM:
					{
						offset.x = 0;
						offset.y = 15;
						break;
					}
				}

				return offset;
			}
			case GLCraft::BlockID::STONE:
			{
				offset.x = 3;
				offset.y = 15;
				return offset;
			}
			default:
				break;
		}

		ASSERT(true, "Invalid Block ID!");
		return offset;
	}

	Block::Block(BlockID blockID)
		: m_BlockID(blockID)
	{
		SetVerticesAndIndices();
		SetTexCoords();
	}

	Block::~Block()
	{
	}

	Engine::Vertex* Block::GetFace(BlockFaceType faceType)
	{
		int faceIndex = m_Indices[(int)faceType * 6];
		return &m_Vertices[faceIndex];
	}

	void Block::SetVerticesAndIndices()
	{
		const float size = 0.5f;

		// Front
		m_Vertices[0].Position = { -size, -size,  size };
		m_Vertices[1].Position = {  size, -size,  size };
		m_Vertices[2].Position = {  size,  size,  size };
		m_Vertices[3].Position = { -size,  size,  size };

		// Back (Order Matters for Easy Texture Coords Adding)
		m_Vertices[5].Position = { -size, -size, -size };
		m_Vertices[4].Position = {  size, -size, -size };
		m_Vertices[7].Position = {  size,  size, -size };
		m_Vertices[6].Position = { -size,  size, -size };

		// Left
		m_Vertices[8].Position  = m_Vertices[5].Position;
		m_Vertices[9].Position  = m_Vertices[0].Position;
		m_Vertices[10].Position = m_Vertices[3].Position;
		m_Vertices[11].Position = m_Vertices[6].Position;

		// Right
		m_Vertices[12].Position = m_Vertices[1].Position;
		m_Vertices[13].Position = m_Vertices[4].Position;
		m_Vertices[14].Position = m_Vertices[7].Position;
		m_Vertices[15].Position = m_Vertices[2].Position;

		// Top
		m_Vertices[16].Position = m_Vertices[3].Position;
		m_Vertices[17].Position = m_Vertices[2].Position;
		m_Vertices[18].Position = m_Vertices[7].Position;
		m_Vertices[19].Position = m_Vertices[6].Position;

		// Bottom
		m_Vertices[20].Position = m_Vertices[5].Position;
		m_Vertices[21].Position = m_Vertices[4].Position;
		m_Vertices[22].Position = m_Vertices[1].Position;
		m_Vertices[23].Position = m_Vertices[0].Position;

		for (int i = 0; i < BLOCK_VERTEX_AMOUNT; i++)
			m_Vertices[i].Color = { 1, 0, 0, 1 };

		int vertexIndex = 0;
		for (int i = 0; i < INDEX_AMOUNT_CUBE; i += 6)
		{
			m_Indices[i + 0] = vertexIndex + 0;
			m_Indices[i + 1] = vertexIndex + 1;
			m_Indices[i + 2] = vertexIndex + 2;
			m_Indices[i + 3] = vertexIndex + 2;
			m_Indices[i + 4] = vertexIndex + 3;
			m_Indices[i + 5] = vertexIndex + 0;

			vertexIndex += 4;
		}
	}

	void Block::SetTexCoords()
	{
		const float TEXTURE_ATLAS_WIDTH = 256, TEXTURE_ATLAS_HEIGHT = 256;
		const float SPRITE_WIDTH = 16, SPRITE_HEIGHT = 16;

		for (int i = 0; i < 6 * 4; i += 4)
		{
			const glm::vec2& offset = GetTexCoordsOffset(m_BlockID, (BlockFaceType)(i / 4));

			m_Vertices[i + 0].TexCoord.x = (SPRITE_WIDTH * offset.x) / TEXTURE_ATLAS_WIDTH;
			m_Vertices[i + 0].TexCoord.y = (SPRITE_HEIGHT * offset.y) / TEXTURE_ATLAS_HEIGHT;

			m_Vertices[i + 1].TexCoord.x = (SPRITE_WIDTH * (offset.x + 1)) / TEXTURE_ATLAS_WIDTH;
			m_Vertices[i + 1].TexCoord.y = (SPRITE_HEIGHT * offset.y) / TEXTURE_ATLAS_HEIGHT;

			m_Vertices[i + 2].TexCoord.x = (SPRITE_WIDTH * (offset.x + 1)) / TEXTURE_ATLAS_WIDTH;
			m_Vertices[i + 2].TexCoord.y = (SPRITE_HEIGHT * (offset.y + 1)) / TEXTURE_ATLAS_HEIGHT;

			m_Vertices[i + 3].TexCoord.x = (SPRITE_WIDTH * offset.x) / TEXTURE_ATLAS_WIDTH;
			m_Vertices[i + 3].TexCoord.y = (SPRITE_HEIGHT * (offset.y + 1)) / TEXTURE_ATLAS_HEIGHT;
		}
	}
}