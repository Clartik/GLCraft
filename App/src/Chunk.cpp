#include "Chunk.h"

namespace GLCraft
{
	Chunk::Chunk(const glm::vec2& startLocation)
	{
		for (int height = 0; height < MAX_HEIGHT; height++)
		{
			for (int row = 0; row < MAX_ROWS; row++)
			{
				for (int column = 0; column < MAX_COLUMNS; column++)
				{
					Block block(Engine::Transform({ 
						startLocation.x + row, 
						height, 
						startLocation.y + column 
					}), BlockID::GRASS);

					m_Chunk[height][row][column] = block;
				}
			}
		}

		CalculateMesh();
	}

	void Chunk::AddFaceToMesh(const glm::vec3& location, Engine::Vertex* faceVertices)
	{
		for (int i = 0; i < VERTEX_AMOUNT_QUAD; i++)
		{
			faceVertices[i].Position += location;
			m_Vertices.push_back(faceVertices[i]);
		}

		// Needs to subtract because it needs to access the acccessed vertices, not future ones
		const unsigned int vertexIndex = m_Vertices.size() - VERTEX_AMOUNT_QUAD;

		m_Indices.insert(m_Indices.end(), {
			vertexIndex,
			vertexIndex + 1,
			vertexIndex + 2,
			vertexIndex + 2,
			vertexIndex + 3,
			vertexIndex 
		});
	}

	void Chunk::CalculateMesh()
	{
	#if 0
		for (int height = 0; height < CHUNK_HEIGHT; height++)
		{
			for (int row = 0; row < CHUNK_ROWS; row++)
			{
				for (int column = 0; column < CHUNK_COLUMNS; column++)
				{
					Block& block = m_Chunk[height][row][column];

					if (row - 1 < 0)
					{
						Engine::Vertex* faceVertices = block.GetFace(BlockFaceType::LEFT);
						glm::vec3 location = { row, height, column };
						AddFaceToMesh(location, faceVertices);
					}

					if (row + 1 > CHUNK_ROWS - 1)
					{
						Engine::Vertex* faceVertices = block.GetFace(BlockFaceType::RIGHT);
						glm::vec3 location = { row, height, column };
						AddFaceToMesh(location, faceVertices);
					}

					if (column - 1 < 0)
					{
						Engine::Vertex* faceVertices = block.GetFace(BlockFaceType::BACK);
						glm::vec3 location = { row, height, column };
						AddFaceToMesh(location, faceVertices);
					}

					if (column + 1 > CHUNK_COLUMNS - 1)
					{
						Engine::Vertex* faceVertices = block.GetFace(BlockFaceType::FRONT);
						glm::vec3 location = { row, height, column };
						AddFaceToMesh(location, faceVertices);
					}

					if (height - 1 < 0)
					{
						Engine::Vertex* faceVertices = block.GetFace(BlockFaceType::BOTTOM);
						glm::vec3 location = { row, height, column };
						AddFaceToMesh(location, faceVertices);
					}

					if (height + 1 > CHUNK_HEIGHT - 1)
					{
						Engine::Vertex* faceVertices = block.GetFace(BlockFaceType::TOP);
						glm::vec3 location = { row, height, column };
						AddFaceToMesh(location, faceVertices);
					}
				}
			}
		}

		m_Mesh.LoadVertices(m_Vertices.data(), m_Vertices.size() * sizeof(Engine::Vertex));
		m_Mesh.LoadIndices(m_Indices.data(), m_Indices.size());
	#else

	#endif
	}
}