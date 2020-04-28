#include "Xpch.h"
#include "Buffer.h"
#include "RendererAPI/Renderer.h"
#include "Platforms/OpenGL/OpenGLBuffer.h"
namespace XEngine
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				XCORE_ASSERT(false, "RendererAPI::None is not supported");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return new OpenGlVertexBuffer(vertices, size);
		}
		XCORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}
	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				XCORE_ASSERT(false, "RendererAPI::None is not supported");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return new OpenGlIndexBuffer(indices, size);
		}
		XCORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}
}