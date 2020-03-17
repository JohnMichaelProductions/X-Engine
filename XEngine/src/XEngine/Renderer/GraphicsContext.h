#pragma once
namespace XEngine
{
	class GraphicsContext
	{
	public:
		// ---FUNCTIONS---
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
		// ---------------
	};
}