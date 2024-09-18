#pragma once

#include <glm/vec3.hpp>
#include <GL/glew.h>

#include "ITutorial.h"
#include "GLBuffer.h"

class Tutorial2 : public ITutorial
{
public:
	Tutorial2()
	{
		std::vector<glm::ivec3> dotArray = { glm::ivec3(0, 0, 0) };
		_vbuffer.SetData(dotArray);
	}

	void Render() override
	{
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, _vbuffer.GetHandle());
		glVertexAttribPointer(0, 3, GL_INT, GL_FALSE, 0, 0);
		glDrawArrays(GL_POINTS, 0, 1);
		glDisableVertexAttribArray(0);
	}
private:
	GLVertexBuffer _vbuffer;
};