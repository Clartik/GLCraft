#include "Block.h"

namespace GLCraft
{
	Block::Block()
		: m_Transform(Engine::Transform())
	{
		SetVerticesAndIndices();
	}

	Block::Block(const Engine::Transform& transform)
		: m_Transform(transform)
	{
		SetVerticesAndIndices();
	}

	Engine::Vertex* Block::GetFace(BlockFaceType faceType)
	{
		Engine::Vertex face[VERTEX_AMOUNT_QUAD];
		int faceIndex = 0;

		for (int i = 0; i < 3; i++)
		{
			// Accesses fourth vertex but sets to third member for index
			if (i == 0)
			{
				faceIndex = m_IndicesMap[faceType][4];
				face[3] = m_Vertices[faceIndex];
			}

			faceIndex = m_IndicesMap[faceType][i];
			face[i] = m_Vertices[faceIndex];
		}		

		return face;
	}

	void Block::SetVerticesAndIndices()
	{
		// Front
		m_Vertices[0].Position = { -BLOCK_VERTEX_SIZE, -BLOCK_VERTEX_SIZE,  BLOCK_VERTEX_SIZE };
		m_Vertices[1].Position = {  BLOCK_VERTEX_SIZE, -BLOCK_VERTEX_SIZE,  BLOCK_VERTEX_SIZE };
		m_Vertices[2].Position = {  BLOCK_VERTEX_SIZE,  BLOCK_VERTEX_SIZE,  BLOCK_VERTEX_SIZE };
		m_Vertices[3].Position = { -BLOCK_VERTEX_SIZE,  BLOCK_VERTEX_SIZE,  BLOCK_VERTEX_SIZE };

		// Back
		m_Vertices[4].Position = { -BLOCK_VERTEX_SIZE, -BLOCK_VERTEX_SIZE, -BLOCK_VERTEX_SIZE };
		m_Vertices[5].Position = {  BLOCK_VERTEX_SIZE, -BLOCK_VERTEX_SIZE, -BLOCK_VERTEX_SIZE };
		m_Vertices[6].Position = {  BLOCK_VERTEX_SIZE,  BLOCK_VERTEX_SIZE, -BLOCK_VERTEX_SIZE };
		m_Vertices[7].Position = { -BLOCK_VERTEX_SIZE,  BLOCK_VERTEX_SIZE, -BLOCK_VERTEX_SIZE };

		// Left
		m_Vertices[8].Position  = m_Vertices[4].Position;
		m_Vertices[9].Position  = m_Vertices[0].Position;
		m_Vertices[10].Position = m_Vertices[3].Position;
		m_Vertices[11].Position = m_Vertices[7].Position;

		// Right
		m_Vertices[12].Position = m_Vertices[1].Position;
		m_Vertices[13].Position = m_Vertices[5].Position;
		m_Vertices[14].Position = m_Vertices[6].Position;
		m_Vertices[15].Position = m_Vertices[2].Position;

		// Top
		m_Vertices[16].Position = m_Vertices[3].Position;
		m_Vertices[17].Position = m_Vertices[2].Position;
		m_Vertices[18].Position = m_Vertices[6].Position;
		m_Vertices[19].Position = m_Vertices[7].Position;

		// Bottom
		m_Vertices[20].Position = m_Vertices[4].Position;
		m_Vertices[21].Position = m_Vertices[5].Position;
		m_Vertices[22].Position = m_Vertices[1].Position;
		m_Vertices[23].Position = m_Vertices[0].Position;

		for (int i = 0; i < 6; i += 4)
		{
			m_Vertices[i + 1].TexCoord = { 0, 0 };
			m_Vertices[i + 1].TexCoord = { 0, 0 };
			m_Vertices[i + 1].TexCoord = { 1, 1 };
			m_Vertices[i + 1].TexCoord = { 0, 1 };
		}

		for (int i = 0; i < BLOCK_VERTEX_AMOUNT; i++)
			m_Vertices[i].Color = { 1, 0, 0, 1 };

		m_IndicesMap[BlockFaceType::FRONT] = {
			0, 1, 2,
			2, 3, 0,
		};

		m_IndicesMap[BlockFaceType::BACK] = {
			5, 4, 7,
			7, 6, 5
		};

		m_IndicesMap[BlockFaceType::LEFT] = {
			8, 9, 10,
			10, 11, 8
		};

		m_IndicesMap[BlockFaceType::RIGHT] = {
			12, 13, 14,
			14, 15, 12
		};

		m_IndicesMap[BlockFaceType::TOP] = {
			16, 17, 18,
			18, 19, 16
		};

		m_IndicesMap[BlockFaceType::BOTTOM] = {
			20, 21, 22,
			22, 23, 20
		};

		int indexCount = 0;
		for (const auto& pair : m_IndicesMap)
		{
			const auto& faceIndices = pair.second;

			for (int i = 0; i < INDEX_AMOUNT_QUAD; i++)
				m_Indices[indexCount++] = faceIndices[i];
		}
	}
}