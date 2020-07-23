// Source File for Vertex and Index Buffer Functions
#include "Xpch.h"
#include <GLAD/glad.h>
#include "Platforms/RenderingAPIs/OpenGL/OpenGLBuffer.h"
namespace XEngine
{
	// Vertex Buffer Functions
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
	{
		XPROFILE_FUNCTION();
		glCreateBuffers(1, &vertexBufferRenderID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferRenderID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}
	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		XPROFILE_FUNCTION();
		glDeleteBuffers(1, &vertexBufferRenderID);
	}
	void OpenGLVertexBuffer::Bind() const
	{
		XPROFILE_FUNCTION();
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferRenderID);
	}
	void OpenGLVertexBuffer::Unbind() const
	{
		XPROFILE_FUNCTION();
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	// Index Buffer Functions
	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count) : indexBufferCount(count)
	{
		XPROFILE_FUNCTION();
		glCreateBuffers(1, &indexBufferRenderID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferRenderID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}
	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		XPROFILE_FUNCTION();
		glDeleteBuffers(1, &indexBufferRenderID);
	}
	void OpenGLIndexBuffer::Bind() const
	{
		XPROFILE_FUNCTION();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferRenderID);
	}
	void OpenGLIndexBuffer::Unbind() const
	{
		XPROFILE_FUNCTION();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}