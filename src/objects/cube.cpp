#include "cube.h"

Cube::Cube()
{
	FillTexturedVertexBuffer();
	//FillColoredVertexBuffer();
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

void Cube::FillColoredVertexBuffer()
{
	std::vector<GLColoredVertex> vertexList;

	vertexList.emplace_back(glm::vec3{  0.5f,   0.5f,   0.5f }, GenerateRandomColor());
	vertexList.emplace_back(glm::vec3{ -0.5f,   0.5f,  -0.5f }, GenerateRandomColor());
	vertexList.emplace_back(glm::vec3{ -0.5f,   0.5f,   0.5f }, GenerateRandomColor());
	vertexList.emplace_back(glm::vec3{  0.5f,  -0.5f,  -0.5f }, GenerateRandomColor());
	vertexList.emplace_back(glm::vec3{ -0.5f,  -0.5f,  -0.5f }, GenerateRandomColor());
	vertexList.emplace_back(glm::vec3{  0.5f,   0.5f,  -0.5f }, GenerateRandomColor());
	vertexList.emplace_back(glm::vec3{  0.5f,  -0.5f,   0.5f }, GenerateRandomColor());
	vertexList.emplace_back(glm::vec3{ -0.5f,  -0.5f,   0.5f }, GenerateRandomColor());


	_vbuffer.SetData(vertexList);
}

void Cube::FillTexturedVertexBuffer()
{
	std::vector<GLTexturedVertex> vertexList;

	glm::vec2 t00 = glm::vec2(0.0f, 0.0f);
	glm::vec2 t01 = glm::vec2(0.0f, 1.0f);
	glm::vec2 t10 = glm::vec2(1.0f, 0.0f);
	glm::vec2 t11 = glm::vec2(1.0f, 1.0f);

	vertexList.emplace_back(glm::vec3{  0.5f,   0.5f,   0.5f }, t00);
	vertexList.emplace_back(glm::vec3{ -0.5f,   0.5f,  -0.5f }, t01);
	vertexList.emplace_back(glm::vec3{ -0.5f,   0.5f,   0.5f }, t10);
	vertexList.emplace_back(glm::vec3{  0.5f,  -0.5f,  -0.5f }, t11);
	vertexList.emplace_back(glm::vec3{ -0.5f,  -0.5f,  -0.5f }, t00);
	vertexList.emplace_back(glm::vec3{  0.5f,   0.5f,  -0.5f }, t10);
	vertexList.emplace_back(glm::vec3{  0.5f,  -0.5f,   0.5f }, t01);
	vertexList.emplace_back(glm::vec3{ -0.5f,  -0.5f,   0.5f }, t11);


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
