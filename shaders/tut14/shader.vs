#version 330

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 inColor;

uniform mat4 gTransform;

out vec4 Color;

void main()
{
	gl_Position = gTransform * vec4(Position, 1.0);
    Color = vec4(inColor, 1.0f);
}