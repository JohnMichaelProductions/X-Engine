// Source File for Vertex and Index Buffer Functions
#include "Xpch.h"
#include "OpenGLBuffer.h"
#include <GLAD/glad.h>
namespace XEngine
{
	// Vertex Buffer Functions
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
	{
		glCreateBuffers(1, &renderID);
		glBindBuffer(GL_ARRAY_BUFFER, renderID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}
	OpenGLVertexBuffer::~OpenGLVertexBuffer()
		{ glDeleteBuffers(1, &renderID); }
	void OpenGLVertexBuffer::Bind() const
		{ glBindBuffer(GL_ARRAY_BUFFER, renderID); }
	void OpenGLVertexBuffer::Unbind() const
		{ glBindBuffer(GL_ARRAY_BUFFER, 0); }
	// Index Buffer Functions
	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count) : renderID(count)
	{
		glCreateBuffers(1, &renderID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}
	OpenGLIndexBuffer::~OpenGLIndexBuffer()
		{ glDeleteBuffers(1, &renderID); }
	void OpenGLIndexBuffer::Bind() const
		{ glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderID); }
	void OpenGLIndexBuffer::Unbind() const
		{ glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
}