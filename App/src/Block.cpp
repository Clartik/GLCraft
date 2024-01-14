#include "Block.h"

namespace GLCraft
{
	Block::Block()
		: m_Transform(Engine::Transform())
	{
	}

	Block::Block(const Engine::Transform& transform)
		: m_Transform(transform)
	{
		m_Vertices[0].Position = { -0.5f, -0.5f, -0.5f };
		m_Vertices[1].Position = {  0.5f, -0.5f, -0.5f };
		m_Vertices[2].Position = {  0.5f,  0.5f, -0.5f };
		m_Vertices[3].Position = { -0.5f,  0.5f, -0.5f };

		m_Vertices[4].Position = { -0.5f, -0.5f,  0.5f };
		m_Vertices[5].Position = {  0.5f, -0.5f,  0.5f };
		m_Vertices[6].Position = {  0.5f,  0.5f,  0.5f };
		m_Vertices[7].Position = { -0.5f,  0.5f,  0.5f };

		for (int i = 0; i < 8; i++)
		{
			m_Vertices[i].Color = { 1, 0, 0, 1 };
		}

		m_IndicesMap[BlockFaceType::FRONT] = {
			0, 1, 2,
			2, 3, 0,
		};

		m_IndicesMap[BlockFaceType::BACK] = {
			4, 5, 6,
			6, 7, 4,
		};

		m_IndicesMap[BlockFaceType::LEFT] = {
			1, 5, 6,
			6, 2, 1,
		};

		m_IndicesMap[BlockFaceType::RIGHT] = {
			4, 0, 3,
			3, 7, 4,
		};

		m_IndicesMap[BlockFaceType::TOP] = {
			3, 2, 6,
			6, 7, 3,
		};

		m_IndicesMap[BlockFaceType::BOTTOM] = {
			4, 5, 1,
			1, 0, 4
		};
	}

	Engine::Vertex* Block::GetFace(BlockFaceType faceType)
	{
		Engine::Vertex face[VERTEX_AMOUNT_QUAD];
		int faceIndex = 0;

		for (int i = 0; i < 3; i++)
		{
			faceIndex = m_IndicesMap[faceType][i];
			face[i] = m_Vertices[faceIndex];
		}

		// Accesses fourth vertex but sets to third member to save memory
		faceIndex = m_IndicesMap[faceType][4];
		face[3] = m_Vertices[faceIndex];

		return face;
	}

	unsigned int* Block::GetIndices() const
	{
		unsigned int indices[INDEX_AMOUNT_CUBE];

		int indexCount = 0;
		for (const auto& pair : m_IndicesMap)
		{
			const auto& faceIndices = pair.second;

			for (int i = 0; i < INDEX_AMOUNT_QUAD; i++)
				indices[indexCount] = faceIndices[i];
		}

		return indices;
	}
}