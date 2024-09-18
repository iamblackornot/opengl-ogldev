#pragma once

#include <glm/vec3.hpp>
#include <GL/glew.h>
#include <cmath>
#include <random>

#include "ITutorial.h"
#include "helper.h"
#include "GLProgram.h"
#include "GLVertex.h"
#include "GLBuffer.h"

class Tutorial10 : public ITutorial
{
public:
	Tutorial10() = default;

	Result Init() override
	{
		FillVertexBuffer();
		FIllIndexBuffer();

		Result res = _shaders.Init();
		if (!res.IsSuccess) return res;

		res = _shaders.AddShader(GetShaderFiles());
		if (!res.IsSuccess) return res;

		res = _shaders.CompileShaders();
		if (!res.IsSuccess) return res;

		glUseProgram(_shaders.GetHandle());

		return GoodResult();
	}
	void Render() override
	{
		glBindBuffer(GL_ARRAY_BUFFER, _vbuffer.GetHandle());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebuffer.GetHandle());

		// position
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLVertex), 0);

		// color
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLVertex), (void*)(sizeof(glm::vec3)));

		glDrawElements(GL_TRIANGLES, 54, GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	}
	ShaderList GetShaderFiles() const override
	{
		return ShaderList
		{
			{ GL_VERTEX_SHADER, "..\\shaders\\tut10\\shader.vs" },
			{ GL_FRAGMENT_SHADER, "..\\shaders\\tut10\\shader.fs" },
		};
	}
private:
	void FillVertexBuffer()
	{
		std::vector<GLVertex> vertexList;
		
		// center
		vertexList.emplace_back(glm::vec3{  0.0f,  0.0f, 0.f }, GenerateRandomColor());

		// upper row
		vertexList.emplace_back(glm::vec3{ -1.0f,  1.0f, 0.f }, GenerateRandomColor());
		vertexList.emplace_back(glm::vec3{ -0.75f, 1.0f, 0.f }, GenerateRandomColor());
		vertexList.emplace_back(glm::vec3{ -0.50f, 1.0f, 0.f }, GenerateRandomColor());
		vertexList.emplace_back(glm::vec3{ -0.25f, 1.0f, 0.f }, GenerateRandomColor());
		vertexList.emplace_back(glm::vec3{ -0.0f,  1.0f, 0.f }, GenerateRandomColor());
		vertexList.emplace_back(glm::vec3{  0.25f, 1.0f, 0.f }, GenerateRandomColor());
		vertexList.emplace_back(glm::vec3{  0.50f, 1.0f, 0.f }, GenerateRandomColor());
		vertexList.emplace_back(glm::vec3{  0.75f, 1.0f, 0.f }, GenerateRandomColor());
		vertexList.emplace_back(glm::vec3{  1.0f,  1.0f, 0.f }, GenerateRandomColor());

		// bottom row
		vertexList.emplace_back(glm::vec3{ -1.0f,  -1.0f, 0.f }, GenerateRandomColor());
		vertexList.emplace_back(glm::vec3{ -0.75f, -1.0f, 0.f }, GenerateRandomColor());
		vertexList.emplace_back(glm::vec3{ -0.50f, -1.0f, 0.f }, GenerateRandomColor());
		vertexList.emplace_back(glm::vec3{ -0.25f, -1.0f, 0.f }, GenerateRandomColor());
		vertexList.emplace_back(glm::vec3{ -0.0f,  -1.0f, 0.f }, GenerateRandomColor());
		vertexList.emplace_back(glm::vec3{  0.25f, -1.0f, 0.f }, GenerateRandomColor());
		vertexList.emplace_back(glm::vec3{  0.50f, -1.0f, 0.f }, GenerateRandomColor());
		vertexList.emplace_back(glm::vec3{  0.75f, -1.0f, 0.f }, GenerateRandomColor());
		vertexList.emplace_back(glm::vec3{  1.0f,  -1.0f, 0.f }, GenerateRandomColor());

		_vbuffer.SetData(vertexList);
	}

	void FIllIndexBuffer()
	{
		std::vector<uint32_t> indices
		{						   
			// Top triangles
			0, 2, 1,
			0, 3, 2,
			0, 4, 3,
			0, 5, 4,
			0, 6, 5,
			0, 7, 6,
			0, 8, 7,
			0, 9, 8,

			// Bottom triangles
			0, 10, 11,
			0, 11, 12,
			0, 12, 13,
			0, 13, 14,
			0, 14, 15,
			0, 15, 16,
			0, 16, 17,
			0, 17, 18,

			// Left triangle
			0, 1, 10,

			// Right triangle
			0, 18, 9 
		};

		_ebuffer.SetData(indices);
	}

	glm::vec3 GenerateRandomColor()
	{
		std::uniform_int_distribution<std::mt19937::result_type> dist(0, 255);

		return 
		{ 
			(float)dist(_random) / (float)255,
			(float)dist(_random) / (float)255,
			(float)dist(_random) / (float)255
		};
	}

private:
	std::mt19937 _random{ std::random_device()() };
	GLProgram _shaders;
	GLVertexBuffer _vbuffer;
	GLElementBuffer _ebuffer;
};
