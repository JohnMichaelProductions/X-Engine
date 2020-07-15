#include "Xpch.h"
#include "XEngine/GraphicsSystem/Buffer.h"
#include "XEngine/GraphicsSystem/Renderer/Renderer.h"
#include "Platforms/RenderingAPIs/OpenGL/OpenGLBuffer.h"
namespace XEngine
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				XCORE_ASSERT(false, "RendererAPI::None is not supported");
				return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLVertexBuffer(vertices, size);
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
			case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(indices, size);
		}
		XCORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}
}