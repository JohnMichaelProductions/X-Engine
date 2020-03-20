#pragma once
#include "XEngine/Renderer/Buffer.h"
namespace XEngine
{
	class OpenGlVertexBuffer : public VertexBuffer
	{
	public:
		OpenGlVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGlVertexBuffer();
		virtual void Bind() const;
		virtual void Unbind() const;
	private:
		uint32_t mainRenderID;
	};	
	class OpenGlIndexBuffer : public IndexBuffer
	{
	public:
		OpenGlIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGlIndexBuffer();
		virtual uint32_t GetCount() const { return mainCount; }
		virtual void Bind() const;
		virtual void Unbind() const;
	private:
		uint32_t mainRenderID;
		uint32_t mainCount;
	};
}