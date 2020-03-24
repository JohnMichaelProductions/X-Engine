#include "Xpch.h"
#include "VertexArray.h"
#include "Renderer.h"
namespace XEngine
{
	VertexBuffer* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			XCORE_ASSERT(false, "RendererAPI::None is not supported");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLVertexArray();
		}
		XCORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}
}