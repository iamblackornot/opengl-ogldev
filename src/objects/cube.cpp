#include "cube.h"

Cube::Cube()
{
	FillVertexBuffer();
	FillIndexBuffer();
}

GLuint Cube::GetVertexBuffer()
{
	return _vbuffer.GetHandle();
}

GLuint Cube::GetElementBuffer()
{
	return _ebuffer.GetHandle();
}

void Cube::FillVertexBuffer()
{
	std::vector<GLVertex> vertexList;

	vertexList.emplace_back(glm::vec3{ 0.5f,   0.5f,   0.5f }, GenerateRandomColor());
	vertexList.emplace_back(glm::vec3{ -0.5f,   0.5f,  -0.5f }, GenerateRandomColor());
	vertexList.emplace_back(glm::vec3{ -0.5f,   0.5f,   0.5f }, GenerateRandomColor());
	vertexList.emplace_back(glm::vec3{ 0.5f,  -0.5f,  -0.5f }, GenerateRandomColor());
	vertexList.emplace_back(glm::vec3{ -0.5f,  -0.5f,  -0.5f }, GenerateRandomColor());
	vertexList.emplace_back(glm::vec3{ 0.5f,   0.5f,  -0.5f }, GenerateRandomColor());
	vertexList.emplace_back(glm::vec3{ 0.5f,  -0.5f,   0.5f }, GenerateRandomColor());
	vertexList.emplace_back(glm::vec3{ -0.5f,  -0.5f,   0.5f }, GenerateRandomColor());


	_vbuffer.SetData(vertexList);
}

void Cube::FillIndexBuffer()
{
	std::vector<uint32_t> indices
	{
		0, 1, 2,
		1, 3, 4,
		5, 6, 3,
		7, 3, 6,
		2, 4, 7,
		0, 7, 6,
		0, 5, 1,
		1, 5, 3,
		5, 0, 6,
		7, 4, 3,
		2, 1, 4,
		0, 2, 7
	};

	_ebuffer.SetData(indices);
}

