#include "Xpch.h"
#include "OpenGLTexture.h"
#include "stb_image.h"
#include <GLAD/glad.h>
namespace XEngine
{
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path) : texturePath(path)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		XCORE_ASSERT(data, "Failed to load image");
		textureWidth = width;
		textureHeight = height;
		glCreateTextures(GL_TEXTURE_2D, 1, &textureRendererID);
		glTextureStorage2D(textureRendererID, 1, GL_RGB8, textureWidth, textureHeight);
		glTextureParameteri(textureRendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(textureRendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureSubImage2D(textureRendererID, 0, 0, 0, textureWidth, textureHeight, GL_RGB, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
	}
	OpenGLTexture2D::~OpenGLTexture2D()
		{ glDeleteTextures(1, &textureRendererID); }
	void OpenGLTexture2D::Bind(uint32_t slot) const
		{ glBindTextureUnit(slot, textureRendererID); }
}