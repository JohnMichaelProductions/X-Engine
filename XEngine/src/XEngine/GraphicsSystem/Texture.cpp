#include "Xpch.h"
#include "XEngine/GraphicsSystem/Texture.h"
#include "XEngine/GraphicsSystem/Renderer/Renderer.h"
#include "Platforms/RenderingAPIs/OpenGL/OpenGLTexture.h"
namespace XEngine
{
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				XCORE_ASSERT(false, "RendererAPI::None is currently not supported!");
				return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(path);
		}
		XCORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}