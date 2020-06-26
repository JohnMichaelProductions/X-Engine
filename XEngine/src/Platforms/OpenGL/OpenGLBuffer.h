// Header File for Vertex and Index Buffer Functions
#pragma once
#include "XEngine/Renderer/Buffer.h"
namespace XEngine
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		// Defined in Source File
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();
		virtual void Bind() const override;
		virtual void Unbind() const override;
		// Prototype in Header File
		virtual const BufferLayout& GetLayout() const override
			{ return vertexBufferLayout; }
		virtual void SetLayout(const BufferLayout& layout) override
			{ vertexBufferLayout = layout; }
	private:
		uint32_t renderID;
		BufferLayout vertexBufferLayout;
	};
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		// Defined in Source File
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();
		virtual void Bind() const;
		virtual void Unbind() const;
		// Prototype in Header File
		virtual uint32_t GetCount() const
			{ return count; }
	private:
		uint32_t renderID;
		uint32_t count;
	};
}