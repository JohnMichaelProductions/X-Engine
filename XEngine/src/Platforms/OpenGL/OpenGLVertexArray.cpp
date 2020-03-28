#include "Xpch.h"
#include "OpenGLVertexArray.h"
#include <GLAD/glad.h>
namespace XEngine
{
	static GLenum ShaderTypeConvertToOpenGLType(ShaderDataType type)			// Shader Type Convert To OpenGL Type Function: Converts shader types to OpenGL Types
	{
		// ---DATA CONVERSION---												// ---DATA CONVERSION---
		switch (type)															
		{
			case XEngine::ShaderDataType::Float:								// Float
				return GL_FLOAT;												// Float
			case XEngine::ShaderDataType::Float2:								// Float2
				return GL_FLOAT;												// Float2
			case XEngine::ShaderDataType::Float3:								// Float3
				return GL_FLOAT;												// Float3
			case XEngine::ShaderDataType::Float4:								// Float4
				return GL_FLOAT;												// Float4
			case XEngine::ShaderDataType::Mat3:									// Mat3
				return GL_FLOAT;												// Mat3
			case XEngine::ShaderDataType::Mat4:									// Mat4
				return GL_FLOAT;												// Mat4
			case XEngine::ShaderDataType::Int:									// Int
				return GL_INT;													// Int
			case XEngine::ShaderDataType::Int2:									// Int2
				return GL_INT;													// Int2
			case XEngine::ShaderDataType::Int3:									// Int3
				return GL_INT;													// Int3
			case XEngine::ShaderDataType::Int4:									// Int4
				return GL_INT;													// Int4
			case XEngine::ShaderDataType::Bool:									// Bool
				return GL_BOOL;													// Bool
		}
		// ---------------------												// ---------------------
		XCORE_ASSERT(false, "Unknown ShaderDataType!");							// If data conversion fails assert
		return 0;
	}
	OpenGLVertexArray::OpenGLVertexArray()										// Constructor: Creates vertex array
		{ glCreateVertexArrays(1, &rendererID); }
	OpenGLVertexArray::~OpenGLVertexArray()										// Destructor: Deletes vertex array
		{ glDeleteVertexArrays(1, &rendererID); }
	void OpenGLVertexArray::Bind() const										// Bind Function: Binds Vertex Array
		{ glBindVertexArray(rendererID); }
	void OpenGLVertexArray::Unbind() const										// Unbind Function: Unbinds Vertex Array
		{ glBindVertexArray(0); }
	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)			// Add Vertex Buffer Function: Add Vertex Buffer
	{
		XCORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout");	// If vertex buffer has no layout assert
		glBindVertexArray(rendererID);																	// Binds vertex to rendererID variable
		vertexBuffer->Bind();																			// Call Bind with vertexBuffer variable
		uint32_t index = 0;																				// Create index variable
		const auto& layout = vertexBuffer->GetLayout();													// Return a layout from the vertexBuffer variable and store it in new layout variable
		for (const auto& element : layout)																// For every element in layout
		{
			glEnableVertexAttribArray(index);															// Enable vertex attribute based on index variables
			glVertexAttribPointer(index, element.GetComponentCount(), ShaderTypeConvertToOpenGLType(element.Type), element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)element.Offset);
			index++;
		}
		memberVertexBuffer.push_back(vertexBuffer);
	}
	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(rendererID);
		indexBuffer->Bind();
		memberIndexBuffer = indexBuffer;
	}
}