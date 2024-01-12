#pragma once

#include <glm/glm.hpp>

namespace Engine
{
	struct Vertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
	};

	Vertex* CreateQuad(const glm::vec2& size, const glm::vec4& color)
	{
		Vertex vertices[4];

		vertices[0].Position = { -size, -size, 0.0f };
		vertices[1].Position = {  size, -size, 0.0f };
		vertices[2].Position = {  size,  size, 0.0f };
		vertices[3].Position = { -size,  size, 0.0f };

		for (int i = 0; i < 4; i++)
			vertices[i].Color = color;

		return vertices;
	}

	Vertex* CreateCube(const glm::vec3& size, const glm::vec4& color)
	{
		Vertex vertices[8];

		vertices[0].Position = { -size, -size, -size };
		vertices[1].Position = {  size, -size, -size };
		vertices[2].Position = {  size,  size, -size };
		vertices[3].Position = { -size,  size, -size };

		vertices[4].Position = { -size, -size, size };
		vertices[5].Position = {  size, -size, size };
		vertices[6].Position = {  size,  size, size };
		vertices[7].Position = { -size,  size, size };

		for (int i = 0; i < 8; i++)
			vertices[i].Color = color;

		return vertices;
	}
}