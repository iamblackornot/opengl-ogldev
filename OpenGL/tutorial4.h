#pragma once

#include <glm/vec3.hpp>
#include <GL/glew.h>

#include "ITutorial.h"
#include "GLBuffer.h"
#include "helper.h"
#include "GLProgram.h"

class Tutorial4 : public ITutorial
{
public:
	Tutorial4() = default;

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

		res = _shaders.CompileShaders();
		if (!res.IsSuccess) return res;

		glUseProgram(_shaders.GetHandle());

		return GoodResult();
	}
	void Render() override
	{
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
			{ GL_VERTEX_SHADER, "..\\shaders\\tut4\\shader.vs" },
			{ GL_FRAGMENT_SHADER, "..\\shaders\\tut4\\shader.fs" },
		};
	}
private:
	GLProgram _shaders;
	GLVertexBuffer _vbuffer;
};
