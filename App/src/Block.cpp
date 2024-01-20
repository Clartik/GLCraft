#include "Block.h"

namespace GLCraft
{
	Block::Block()
		: m_Transform(Engine::Transform()), m_ID(BlockID::AIR)
	{
		SetVerticesAndIndices();
		SetTextures();
	}

	Block::Block(const Engine::Transform& transform, BlockID blockID)
		: m_Transform(transform), m_ID(blockID)
	{
		SetVerticesAndIndices();
		SetTextures();
	}

	void Block::Render()
	{
		auto shader = Engine::Shader::Create("assets/shaders/Texture.glsl");
		shader->SetUniformInt("u_Texture", 0);

		Engine::Vertex* faceVerts = nullptr;

		for (int i = 0; i < 6; i++)
		{
			faceVerts = GetFace((BlockFaceType)i);

			Engine::Mesh mesh;
			mesh.LoadVertices(faceVerts, 4 * sizeof(Engine::Vertex));
			mesh.LoadIndices(&m_Indices[0], 6);
			mesh.LoadShader(shader);

			m_Textures[i]->Bind();
			Engine::Renderer::Submit(&mesh, &m_Transform);
		}
	}

	Engine::Vertex* Block::GetFace(BlockFaceType faceType)
	{
		int faceIndex = m_Indices[(int)faceType * 6];
		return &m_Vertices[faceIndex];
	}

	void Block::SetVerticesAndIndices()
	{
		const float size = 1.0f;

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

		for (int i = 0; i < 6 * 4; i += 4)
		{
			m_Vertices[i + 0].TexCoord = { 0, 0 };
			m_Vertices[i + 1].TexCoord = { 1, 0 };
			m_Vertices[i + 2].TexCoord = { 1, 1 };
			m_Vertices[i + 3].TexCoord = { 0, 1 };
		}

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

	void Block::SetTextures()
	{
		auto top = Engine::Texture2D::Create("assets/textures/Grass Block/Top.png");
		auto bottom = Engine::Texture2D::Create("assets/textures/Grass Block/Dirt.png");
		auto side = Engine::Texture2D::Create("assets/textures/Grass Block/Side.png");

		m_Textures[(int)BlockFaceType::FRONT] = side;
		m_Textures[(int)BlockFaceType::BACK] = side;
		m_Textures[(int)BlockFaceType::LEFT] = side;
		m_Textures[(int)BlockFaceType::RIGHT] = side;

		m_Textures[(int)BlockFaceType::TOP] = top;
		m_Textures[(int)BlockFaceType::BOTTOM] = bottom;
	}
}