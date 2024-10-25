#pragma once

#include <GL/glew.h>
#include <vector>

template<int GL_BUFFER_TYPE>
class GLBuffer
{
public:
	GLBuffer()
	{
		glGenBuffers(1, &_handle);
	}

	GLuint GetHandle() const
	{
		return _handle;
	}

	template<typename TPointType>
	void SetData(std::vector<TPointType> const& pointArray)
	{
		glBindBuffer(GL_BUFFER_TYPE, _handle);
		glBufferData(
			GL_BUFFER_TYPE,
			sizeof(TPointType) * pointArray.size(),
			pointArray.data(),
			GL_STATIC_DRAW);
	}

	~GLBuffer() noexcept
	{
		glDeleteBuffers(1, &_handle);
	}

private:
	GLuint _handle;
};

typedef GLBuffer<GL_ARRAY_BUFFER> GLVertexBuffer;
typedef GLBuffer<GL_ELEMENT_ARRAY_BUFFER> GLElementBuffer;