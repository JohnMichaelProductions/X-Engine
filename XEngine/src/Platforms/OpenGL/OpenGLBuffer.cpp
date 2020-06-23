#include "Xpch.h"
#include "OpenGLBuffer.h"
#include <GLAD/glad.h>
namespace XEngine
{																		// ---VERTEX BUFFER---
	OpenGlVertexBuffer::OpenGlVertexBuffer(float* vertices, uint32_t size)							// Constructor
	{
		glCreateBuffers(1, &renderID);																// Create one buffer and assign it to the renderID variable
		glBindBuffer(GL_ARRAY_BUFFER, renderID);													// Binds renderID
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);								// Creates and initializes a buffer object's data store
	}
	OpenGlVertexBuffer::~OpenGlVertexBuffer()														// Destructor: Destroys buffers on deletion
		{ glDeleteBuffers(1, &renderID); }
	void OpenGlVertexBuffer::Bind() const															// Bind Function: Binds the renderID
		{ glBindBuffer(GL_ARRAY_BUFFER, renderID); }
	void OpenGlVertexBuffer::Unbind() const															// Unbind Function: Unbinds the renderID
		{ glBindBuffer(GL_ARRAY_BUFFER, 0); }
	// -------------------																			// -------------------
	// ---INDEX BUFFER---																			// ---INDEX BUFFER---
	OpenGlIndexBuffer::OpenGlIndexBuffer(uint32_t* indices, uint32_t count) : renderID(count)		// Constructor
	{
		glCreateBuffers(1, &renderID);																// Create one buffer and assign it to the renderID variable
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderID);											// Binds renderID
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);	// Creates and initializes a buffer object's data store
	}
	OpenGlIndexBuffer::~OpenGlIndexBuffer()															// Destructor: Destroys buffers on deletion
		{ glDeleteBuffers(1, &renderID); }
	void OpenGlIndexBuffer::Bind() const															// Bind Function: Binds the renderID
		{ glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderID); }
	void OpenGlIndexBuffer::Unbind() const															// Unbind Function: Unbinds the renderID
		{ glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
	// ------------------																			// ------------------
}
