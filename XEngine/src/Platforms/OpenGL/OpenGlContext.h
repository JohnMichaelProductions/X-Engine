#pragma once
// Renderer Files
#include "XEngine/Renderer/GraphicsContext.h"
struct GLFWwindow;
namespace XEngine
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		// ---FUNCTIONS---
		OpenGLContext(GLFWwindow* windowHandle);
		virtual void Init() override;
		virtual void SwapBuffers() override;
		// ---------------
	private:
		// New GLFWwindow Variable
		GLFWwindow* mainWindowHandle;
	};
}

