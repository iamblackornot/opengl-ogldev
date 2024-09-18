#pragma once

#include <glm/vec3.hpp>
#include <GL/glew.h>

#include "ITutorial.h"
#include "GLBuffer.h"

class Tutorial3 : public ITutorial
{
public:
	Tutorial3()
	{
		glEnable(GL_CULL_FACE);

		std::vector<glm::ivec3> dotArray =
		{
			glm::ivec3(1, -1, 0),
			glm::ivec3(0, 1, 0),
			glm::ivec3(-1, -1, 0),
		};

		_vbuffer.SetData(dotArray);
	}

	void Render() override
	{
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, _vbuffer.GetHandle());
		glVertexAttribPointer(0, 3, GL_INT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);
	}
private:
	GLVertexBuffer _vbuffer;
};