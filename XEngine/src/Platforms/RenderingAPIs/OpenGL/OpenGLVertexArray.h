// Header file for OpenGL Vertex Arrays
#pragma once
#include "XEngine/GraphicsSystem/VertexArray.h"
namespace XEngine
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		// Defined in Source File
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();
		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;
		// Prototype in Header File
		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const 
			{ return vertexArrayVertexBuffer; }
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const 
			{ return vertexArrayIndexBuffer; }
	private:
		uint32_t vertexArrayRendererID;
		std::vector<Ref<VertexBuffer>> vertexArrayVertexBuffer;
		Ref<IndexBuffer> vertexArrayIndexBuffer;
	};
}