// Header file for OpenGL Vertex Arrays
#pragma once
#include "XEngine/Renderer/VertexArray.h"
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
		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;
		// Prototype in Header File
		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const 
			{ return vertexArrayVertexBuffer; }
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const 
			{ return vertexArrayIndexBuffer; }
	private:
		uint32_t vertexArrayRendererID;
		std::vector<std::shared_ptr<VertexBuffer>> vertexArrayVertexBuffer;
		std::shared_ptr<IndexBuffer> vertexArrayIndexBuffer;
	};
}