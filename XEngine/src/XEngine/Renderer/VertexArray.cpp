#include "Xpch.h"
#include "VertexArray.h"
#include "RendererAPI/Renderer.h"
#include "Platforms/RenderingAPIs/OpenGL/OpenGLVertexArray.h"
namespace XEngine
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: 
				XCORE_ASSERT(false, "RendererAPI::None is currently not supported!"); 
				return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
		}
		XCORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}