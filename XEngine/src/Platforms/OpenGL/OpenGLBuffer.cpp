#include "Xpch.h"
#include "OpenGLBuffer.h"
#include <GLAD/glad.h>
namespace XEngine
{
	// ---VERTEX BUFFER---
	OpenGlVertexBuffer::OpenGlVertexBuffer(float* vertices, uint32_t size)
	{
		glCreateBuffers(1, &mainRenderID);
		glBindBuffer(GL_ARRAY_BUFFER, mainRenderID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}
	OpenGlVertexBuffer::~OpenGlVertexBuffer() { glDeleteBuffers(1, &mainRenderID); }
	void OpenGlVertexBuffer::Bind() const { glBindBuffer(GL_ARRAY_BUFFER, mainRenderID); }
	void OpenGlVertexBuffer::Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }
	// -------------------
	// ---INDEX BUFFER---
	OpenGlIndexBuffer::OpenGlIndexBuffer(uint32_t* indices, uint32_t count) : mainCount(count)
	{
		glCreateBuffers(1, &mainRenderID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mainRenderID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}
	OpenGlIndexBuffer::~OpenGlIndexBuffer() { glDeleteBuffers(1, &mainRenderID); }
	void OpenGlIndexBuffer::Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mainRenderID); }
	void OpenGlIndexBuffer::Unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
	// ------------------
}