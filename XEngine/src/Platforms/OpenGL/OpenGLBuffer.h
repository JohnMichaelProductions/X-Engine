#pragma once
#include "XEngine/Renderer/Buffer.h"
namespace XEngine
{
	class OpenGlVertexBuffer : public VertexBuffer
	{
	public:
		OpenGlVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGlVertexBuffer();
		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual const BufferLayout& GetLayout() const override
			{ return memberLayout; }
		virtual void SetLayout(const BufferLayout& layout) override
			{ memberLayout = layout; }
	private:
		uint32_t mainRenderID;
		BufferLayout memberLayout;
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