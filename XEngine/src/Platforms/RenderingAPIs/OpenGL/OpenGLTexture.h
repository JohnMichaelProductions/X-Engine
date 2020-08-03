#pragma once
#include <GLAD/glad.h>
#include "XEngine/GraphicsSystem/Texture.h"
namespace XEngine
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(uint32_t width, uint32_t height);
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();
		virtual void SetData(void* data, uint32_t size) override;
		virtual uint32_t GetWidth() const override
			{ return textureWidth; }
		virtual uint32_t GetHeight() const override
			{ return textureHeight; }
		virtual uint32_t GetRendererID() const override
			{ return textureRendererID; }
		virtual void Bind(uint32_t slot = 0) const override;
		virtual bool operator==(const Texture& other) const override
			{ return textureRendererID == ((OpenGLTexture2D&)other).textureRendererID; }
	private:
		std::string texturePath;
		uint32_t textureWidth, textureHeight;
		uint32_t textureRendererID;
		GLenum textureInternalFormat;
		GLenum textureDataFormat;
	};
}