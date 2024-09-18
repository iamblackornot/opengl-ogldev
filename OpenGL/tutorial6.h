#pragma once

#include <glm/vec3.hpp>
#include <GL/glew.h>
#include <cmath>

#include "ITutorial.h"
#include "GLBuffer.h"
#include "helper.h"
#include "GLProgram.h"

class Tutorial6 : public ITutorial
{
public:
	Tutorial6() = default;

	Result Init() override
	{
		glEnable(GL_CULL_FACE);

		std::vector<glm::ivec3> dotArray =
		{
			glm::ivec3(1, -1, 0),
			glm::ivec3(0, 1, 0),
			glm::ivec3(-1, -1, 0),
		};

		_vbuffer.SetData(dotArray);

		Result res = _shaders.Init();
		if (!res.IsSuccess) return res;

		res = _shaders.AddShader(GetShaderFiles());
		if (!res.IsSuccess) return res;

		res = _shaders.CompileShaders();
		if (!res.IsSuccess) return res;

		gTranslationMatrix = _shaders.GetUniformLocation("gTranslation");
		if (gTranslationMatrix == -1) return BadResult("failed to get gTranslation uniform location");

		glUseProgram(_shaders.GetHandle());

		return GoodResult();
	}
	void Render() override
	{
		static float scale = 0.0f;
		static float delta = 0.005f;

		scale += delta;
		if ((scale >= 1.0f) || (scale <= -1.0f)) {
			delta *= -1.0f;
		}

		float const matrix[4 * 4] =
		{
			1, 0, 0, sinf(scale),
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};

		//std::cout << std::format("scale = {}, sin = {}", scale, sinf(scale)) << std::endl;

		glUniformMatrix4fv(gTranslationMatrix, 1, GL_TRUE, matrix);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, _vbuffer.GetHandle());
		glVertexAttribPointer(0, 3, GL_INT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);
	}
	ShaderList GetShaderFiles() const override
	{
		return ShaderList
		{
			{ GL_VERTEX_SHADER, "..\\shaders\\tut6\\shader.vs" },
			{ GL_FRAGMENT_SHADER, "..\\shaders\\tut6\\shader.fs" },
		};
	}
private:
	GLint gTranslationMatrix = -1;
	GLProgram _shaders;
	GLVertexBuffer _vbuffer;
};

