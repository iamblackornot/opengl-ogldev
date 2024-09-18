#pragma once

#include <GL/glew.h>
#include <glm/vec3.hpp>

struct GLVertex
{
	glm::vec3 Position;
	glm::vec3 Color;

	GLVertex() = default;
	GLVertex(glm::vec3 position, glm::vec3 color = {})
		: Position(position), Color(color) {}
};