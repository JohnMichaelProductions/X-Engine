#include "Xpch.h"
#include "OpenGLVertexArray.h"
#include <GLAD/glad.h>
namespace XEngine
{
	static GLenum ShaderDataTypeConvertToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case XEngine::ShaderDataType::Float:	return GL_FLOAT;
			case XEngine::ShaderDataType::Float2:	return GL_FLOAT;
			case XEngine::ShaderDataType::Float3:	return GL_FLOAT;
			case XEngine::ShaderDataType::Float4:	return GL_FLOAT;
			case XEngine::ShaderDataType::Mat3:		return GL_FLOAT;
			case XEngine::ShaderDataType::Mat4:		return GL_FLOAT;
			case XEngine::ShaderDataType::Int:		return GL_INT;
			case XEngine::ShaderDataType::Int2:		return GL_INT;
			case XEngine::ShaderDataType::Int3:		return GL_INT;
			case XEngine::ShaderDataType::Int4:		return GL_INT;
			case XEngine::ShaderDataType::Bool:		return GL_BOOL;
		}
		XCORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}
	OpenGLVertexArray::OpenGLVertexArray() 
		{ glCreateVertexArrays(1, &memberRendererID); }
	void OpenGLVertexArray::Bind() const
		{ glBindVertexArray(memberRendererID); }
	void OpenGLVertexArray::Unbind() const
		{ glBindVertexArray(0); }
	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		glBindVertexArray(memberRendererID);
		vertexBuffer->Bind();
		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeConvertToOpenGLBaseType(element.Type), element.Normalized ? GL_TRUE : GL_FALSE, memberVertexBuffer->GetLayout().GetStride(), (const void*)element.Offset);
			index++;
		}
		memberVertexBuffer.push_back(vertexBuffer);
	}
	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(memberRendererID);
		indexBuffer->Bind();
		memberIndexBuffer = indexBuffer;
	}
}