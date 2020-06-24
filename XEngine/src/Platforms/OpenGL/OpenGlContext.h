#pragma once
#include "XEngine/Renderer/GraphicsContext.h"
struct GLFWwindow;
namespace XEngine
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* mainwindowHandle);
		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* windowHandle;
	};
}