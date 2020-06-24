#include "Xpch.h"
#include "OpenGLBuffer.h"
#include <GLAD/glad.h>
namespace XEngine
{
	OpenGlVertexBuffer::OpenGlVertexBuffer(float* vertices, uint32_t size)
	{
		glCreateBuffers(1, &renderID);
		glBindBuffer(GL_ARRAY_BUFFER, renderID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}
	OpenGlVertexBuffer::~OpenGlVertexBuffer()
		{ glDeleteBuffers(1, &renderID); }
	void OpenGlVertexBuffer::Bind() const
		{ glBindBuffer(GL_ARRAY_BUFFER, renderID); }
	void OpenGlVertexBuffer::Unbind() const
		{ glBindBuffer(GL_ARRAY_BUFFER, 0); }
	OpenGlIndexBuffer::OpenGlIndexBuffer(uint32_t* indices, uint32_t count) : renderID(count)
	{
		glCreateBuffers(1, &renderID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}
	OpenGlIndexBuffer::~OpenGlIndexBuffer()
		{ glDeleteBuffers(1, &renderID); }
	void OpenGlIndexBuffer::Bind() const
		{ glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderID); }
	void OpenGlIndexBuffer::Unbind() const
		{ glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
}