#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec4 color;

out vec4 v_Color;
out vec2 v_TexCoord;

uniform mat4 u_ViewProjection;
uniform mat4 u_Model;

void main() 
{
	v_Color = color;
	v_TexCoord = texCoord;

	gl_Position = u_ViewProjection * u_Model * vec4(position, 1.0f);
}