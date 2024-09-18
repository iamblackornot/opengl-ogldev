#pragma once

#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <cmath>
#include <random>

#include "ITutorial.h"
#include "helper.h"
#include "GLProgram.h"
#include "GLVertex.h"
#include "GLBuffer.h"
#include "Pipeline.h"
#include "Camera.h"

#define TUTORIAL_NUM 13

class TUTORIAL_CLASSNAME : public ITutorial
{
public:
	TUTORIAL_CLASSNAME() = default;

	Result Init() override
	{
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CW);
		glCullFace(GL_BACK);

		FillVertexBuffer();
		FIllIndexBuffer();

		Result res = _shaders.Init();
		if (!res.IsSuccess) return res;

		res = _shaders.AddShader(GetShaderFiles());
		if (!res.IsSuccess) return res;

		res = _shaders.CompileShaders();
		if (!res.IsSuccess) return res;

		_gTransformMatrix = _shaders.GetUniformLocation("gTransform");
		if (_gTransformMatrix == -1) return BadResult("failed to get gTransform uniform location");

		glUseProgram(_shaders.GetHandle());

		Camera camera;
		camera
			.SetPosition({ 5.0f, 0.0f, 3.0f })
			.SetDirection({ 0.0f, 0.0f, -1.0f })
			.SetTilt({ 0.0f, 1.0f, 0.0f });

		PerspectiveProjectionParams perpectiveParams
		{
			.fov = 90.f,
			.zNear = 1.f,
			.zFar = 1000.f,
		};

		_pipeline
			.Translate({ 0.0f, 1.0f, -2.f })
			.SetCamera(camera)
			.SetPerspective(perpectiveParams);


		return GoodResult();
	}
	void Render() override
	{
		static float koeff = 0.0f;
		koeff += 0.01f;

		auto transform = _pipeline
			.RotateRadians({ 0.0f, koeff, 0.0f })
			//.GetWPTransform();
			.GetWVPTransform();

		glUniformMatrix4fv(_gTransformMatrix, 1, GL_TRUE, glm::value_ptr(transform));

		glBindBuffer(GL_ARRAY_BUFFER, _vbuffer.GetHandle());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebuffer.GetHandle());

		// position
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLVertex), 0);

		// color
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLVertex), (void*)(sizeof(glm::vec3)));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(0);

	}
	ShaderList GetShaderFiles() const override
	{
		return ShaderList
		{
			{ GL_VERTEX_SHADER, std::format("..\\shaders\\tut{}\\shader.vs", TUTORIAL_NUM) },
			{ GL_FRAGMENT_SHADER, std::format("..\\shaders\\tut{}\\shader.fs", TUTORIAL_NUM) },
		};
	}
private:
	void FillVertexBuffer()
	{
		std::vector<GLVertex> vertexList;

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

	void FIllIndexBuffer()
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
	GLint _gTransformMatrix = -1;
	GLVertexBuffer _vbuffer;
	GLElementBuffer _ebuffer;
	Pipeline _pipeline;
};
