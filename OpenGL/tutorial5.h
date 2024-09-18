#pragma once

#include <glm/vec3.hpp>
#include <GL/glew.h>

#include "ITutorial.h"
#include "GLBuffer.h"
#include "helper.h"
#include "GLProgram.h"

class Tutorial5 : public ITutorial
{
public:
	Tutorial5() = default;

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

		gScaleVar = _shaders.GetUniformLocation("gScale");
		if (gScaleVar == -1) return BadResult("failed to get gScale uniform location");

		glUseProgram(_shaders.GetHandle());

		return GoodResult();
	}
	void Render() override
	{
		static float scale = 0.0f;
		static float delta = 0.001f;

		scale += delta;
		if ((scale >= 1.0f) || (scale <= -1.0f)) {
			delta *= -1.0f;
		}

		glUniform1f(gScaleVar, scale);

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
			{ GL_VERTEX_SHADER, "..\\shaders\\tut5\\shader.vs" },
			{ GL_FRAGMENT_SHADER, "..\\shaders\\tut5\\shader.fs" },
		};
	}
private:
	GLint gScaleVar = -1;
	GLProgram _shaders;
	GLVertexBuffer _vbuffer;
};

