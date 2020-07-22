// Source file for OpenGL Vertex Arrays
#include "Xpch.h"
#include <GLAD/glad.h>
#include "Platforms/RenderingAPIs/OpenGL/OpenGLVertexArray.h"
namespace XEngine
{
	static GLenum ShaderTypeConvertToOpenGLType(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float: return GL_FLOAT;
			case ShaderDataType::Float2: return GL_FLOAT;
			case ShaderDataType::Float3: return GL_FLOAT;
			case ShaderDataType::Float4: return GL_FLOAT;
			case ShaderDataType::Mat3: return GL_FLOAT;
			case ShaderDataType::Mat4: return GL_FLOAT;
			case ShaderDataType::Int: return GL_INT;
			case ShaderDataType::Int2: return GL_INT;
			case ShaderDataType::Int3: return GL_INT;
			case ShaderDataType::Int4: return GL_INT;
			case ShaderDataType::Bool: return GL_BOOL;
		}
		XCORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}
	OpenGLVertexArray::OpenGLVertexArray()
		{ glCreateVertexArrays(1, &vertexArrayRendererID); }
	OpenGLVertexArray::~OpenGLVertexArray()
		{ glDeleteVertexArrays(1, &vertexArrayRendererID); }
	void OpenGLVertexArray::Bind() const
		{ glBindVertexArray(vertexArrayRendererID); }
	void OpenGLVertexArray::Unbind() const
		{ glBindVertexArray(0); }
	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		XCORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout");
		glBindVertexArray(vertexArrayRendererID);
		vertexBuffer->Bind();
		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponentCount(), ShaderTypeConvertToOpenGLType(element.Type), element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)element.Offset);
			index++;
		}
		vertexArrayVertexBuffer.push_back(vertexBuffer);
	}
	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(vertexArrayRendererID);
		indexBuffer->Bind();
		vertexArrayIndexBuffer = indexBuffer;
	}
}