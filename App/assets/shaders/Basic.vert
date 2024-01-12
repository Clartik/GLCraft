#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec4 color;

out vec4 v_Color;

uniform mat4 u_ViewProjection;
uniform mat4 u_Model;

void main() 
{
	v_Color = color;

	gl_Position = u_ViewProjection * u_Model * vec4(pos, 1.0f);
}