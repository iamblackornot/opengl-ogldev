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

	// +Z face (front)
	vertexList.push_back({ {-0.5f, -0.5f,  0.5f}, t00 });
	vertexList.push_back({ { 0.5f, -0.5f,  0.5f}, t10 });
	vertexList.push_back({ { 0.5f,  0.5f,  0.5f}, t11 });
	vertexList.push_back({ {-0.5f,  0.5f,  0.5f}, t01 });

	// -Z face (back)
	vertexList.push_back({ { 0.5f, -0.5f, -0.5f}, t00 });
	vertexList.push_back({ {-0.5f, -0.5f, -0.5f}, t10 });
	vertexList.push_back({ {-0.5f,  0.5f, -0.5f}, t11 });
	vertexList.push_back({ { 0.5f,  0.5f, -0.5f}, t01 });

	// +X face (right)
	vertexList.push_back({ { 0.5f, -0.5f,  0.5f}, t10 });
	vertexList.push_back({ { 0.5f, -0.5f, -0.5f}, t00 });
	vertexList.push_back({ { 0.5f,  0.5f, -0.5f}, t01 });
	vertexList.push_back({ { 0.5f,  0.5f,  0.5f}, t11 });

	// -X face (left)
	vertexList.push_back({ {-0.5f, -0.5f, -0.5f}, t10 });
	vertexList.push_back({ {-0.5f, -0.5f,  0.5f}, t00 });
	vertexList.push_back({ {-0.5f,  0.5f,  0.5f}, t01 });
	vertexList.push_back({ {-0.5f,  0.5f, -0.5f}, t11 });

	// +Y face (top)
	vertexList.push_back({ {-0.5f,  0.5f,  0.5f}, t00 });
	vertexList.push_back({ { 0.5f,  0.5f,  0.5f}, t10 });
	vertexList.push_back({ { 0.5f,  0.5f, -0.5f}, t11 });
	vertexList.push_back({ {-0.5f,  0.5f, -0.5f}, t01 });

	// -Y face (bottom)
	vertexList.push_back({ {-0.5f, -0.5f, -0.5f}, t00 });
	vertexList.push_back({ { 0.5f, -0.5f, -0.5f}, t10 });
	vertexList.push_back({ { 0.5f, -0.5f,  0.5f}, t11 });
	vertexList.push_back({ {-0.5f, -0.5f,  0.5f}, t01 });


	_vbuffer.SetData(vertexList);
}

void Cube::FillIndexBuffer()
{
	std::vector<GLuint> indices;

	for (GLuint face = 0; face < 6; ++face) 
	{
		GLuint base = face * 4;
		indices.push_back(base + 0); indices.push_back(base + 1); indices.push_back(base + 2);
		indices.push_back(base + 0); indices.push_back(base + 2); indices.push_back(base + 3);
	}

	_ebuffer.SetData(indices);
}
