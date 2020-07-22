#include "Xpch.h"
#include "XEngine/Core/XCore.h"
#include "XEngine/GraphicsSystem/GraphicsContext.h"
#include "XEngine/GraphicsSystem/Renderer/RendererAPI.h"
#include "Platforms/RenderingAPIs/OpenGL/OpenGlContext.h"
#include "Platforms/RenderingAPIs/OpenGL/OpenGLRendererAPI.h"
namespace XEngine
{
	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API::None:
				XCORE_ASSERT(false, "RendererAPI::None is not supported");
				return nullptr;
			case RendererAPI::API::OpenGL: return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}
		XCORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}