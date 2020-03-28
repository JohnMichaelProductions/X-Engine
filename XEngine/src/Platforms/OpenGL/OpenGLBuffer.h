#pragma once
#include "XEngine/Renderer/Buffer.h"
namespace XEngine
{
	// ---VERTEX BUFFER---														// ---VERTEX BUFFER---
	class OpenGlVertexBuffer : public VertexBuffer
	{
	public:																		// {PUBLIC}
		OpenGlVertexBuffer(float* vertices, uint32_t size);						// Constructor: Called upon creation
		virtual ~OpenGlVertexBuffer();											// (Virtual) Destructor: Called upon deletion
		virtual void Bind() const override;										// (Virtual) (Const) (Override) Bind Function
		virtual void Unbind() const override;									// (Virtual) (Const) (Override) Unbind Function
		virtual const BufferLayout& GetLayout() const override					// (Virtual) (Const) (Override) Get Layout Function: returns memberLayout variable
			{ return memberLayout; }
		virtual void SetLayout(const BufferLayout& layout) override				// (Virtual) (Override) Set Layout: Sets memberLayout variable as the BufferLayout variable specified in the parameters
			{ memberLayout = layout; }
	private:																	// {PRIVATE}
		uint32_t renderID;														// Integer Variable, variable to store the buffer ID in
		BufferLayout memberLayout;												// Buffer Layout Variable
	};	
	// -------------------														// -------------------
	// ---INDEX BUFFER---														// ---INDEX BUFFER---
	class OpenGlIndexBuffer : public IndexBuffer
	{
	public:																		// {PUBLIC}
		OpenGlIndexBuffer(uint32_t* indices, uint32_t count);					// Constructor
		virtual ~OpenGlIndexBuffer();											// (Virtual) Destructor
		virtual uint32_t GetCount() const										// (Virtual) Get Count Function: Returns count variable
			{ return count; }
		virtual void Bind() const;												// (Virtual) (Const) Bind Function
		virtual void Unbind() const;											// (Virtual) (Const) Unbind Function
	private:																	// {PRIVATE}
		uint32_t renderID;														// Integer Variable, variable to store the buffer ID in
		uint32_t count;															// Integer Variable
	};
	// ------------------														// ------------------
}