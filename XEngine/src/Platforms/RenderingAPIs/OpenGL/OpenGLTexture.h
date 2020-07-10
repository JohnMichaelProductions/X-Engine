#pragma
#include "XEngine/GraphicsSystem/Texture.h"
namespace XEngine
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();
		virtual uint32_t GetWidth() const override
			{ return textureWidth; }
		virtual uint32_t GetHeight() const override
			{ return textureHeight; }
		virtual void Bind(uint32_t slot = 0) const override;
	private:
		std::string texturePath;
		uint32_t textureWidth, textureHeight;
		uint32_t textureRendererID;
	};
}