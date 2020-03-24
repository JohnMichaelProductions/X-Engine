#pragma once
#include "XEngine/Renderer/VertexArray.h"
namespace XEngine
{
	class OpenGLVertexArray : VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray() {}
		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;
	private:
		uint32_t memberRendererID;
		std::vector<std::shared_ptr<VertexBuffer>> memberVertexBuffer;
		std::shared_ptr<IndexBuffer> memberIndexBuffer;
	};
}

