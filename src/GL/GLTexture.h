#pragma once

#include <string>
#include <stb_image.h>
#include <GL/glew.h>
#include <utility/helper.h>

template<GLenum GL_TEX_TARGET>
class GLTexture
{
public:
	GLTexture()
	{
		glGenTextures(1, &_handle);
	}

	GLuint GetHandle() const
	{
		return _handle;
	}

	bool LoadFromFile(std::string const& filename)
	{
		stbi_set_flip_vertically_on_load(true);

		int bpp;
		stbi_uc* image = stbi_load(filename.c_str(), &_width, &_height, &bpp, 0);

		if (!image) {
			printf("failed to load texture from '%s' - %s\n", filename.c_str(), stbi_failure_reason());
			return false;
		}

		printf("loaded image: width %d, height %d, bpp %d\n", _width, _height, bpp);

		LoadFromBuffer(image, _width, _height);

		stbi_image_free(image);

		return true;
	}

	void LoadFromBuffer(stbi_uc* buffer, int width, int height)
	{
		glBindTexture(GL_TEX_TARGET, _handle);
		glTexImage2D(GL_TEX_TARGET, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer);
		glTexParameterf(GL_TEX_TARGET, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEX_TARGET, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
	}

	void Bind(GLenum textureUnit)
	{
		glActiveTexture(textureUnit);
		glBindTexture(GL_TEX_TARGET, _handle);
	}
	~GLTexture() noexcept
	{
		glDeleteTextures(1, &_handle);
	}
private:
	GLuint _handle;
	int _width = 0;
	int _height = 0;
};

typedef GLTexture<GL_TEXTURE_2D> GLTexture2D;