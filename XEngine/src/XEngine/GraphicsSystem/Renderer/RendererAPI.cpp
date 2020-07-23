#include "Xpch.h"
#include "XEngine/GraphicsSystem/Renderer/RendererAPI.h"
#include "Platforms/RenderingAPIs/OpenGL/OpenGLRendererAPI.h"
namespace XEngine
{
	RendererAPI::API RendererAPI::renderAPI = RendererAPI::API::OpenGL;
	Scope<RendererAPI> RendererAPI::Create()
	{
		switch (renderAPI)
		{
		case RendererAPI::API::None:
			XCORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL: return CreateScope<OpenGLRendererAPI>();
		}

		XCORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}