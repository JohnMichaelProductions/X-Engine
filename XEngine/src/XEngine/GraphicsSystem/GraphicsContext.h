// Graphics context header file, class meant to be derived from
#pragma once
namespace XEngine
{
	class GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}