#pragma once

#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

struct GLColoredVertex
{
	glm::vec3 Position;
	glm::vec3 Color;

	GLColoredVertex() = default;
	GLColoredVertex(glm::vec3 position, glm::vec3 color = {})
		: Position(position), Color(color) {}
};

struct GLTexturedVertex
{
	glm::vec3 Position;
	glm::vec2 TextureCoords;

	GLTexturedVertex() = default;
	GLTexturedVertex(glm::vec3 position, glm::vec2 textureCoords = {})
		: Position(position), TextureCoords(textureCoords) {}
};