#pragma once
#include "XEngine/Renderer/GraphicsContext.h"
struct GLFWwindow;
namespace XEngine
{
	class OpenGLContext : public GraphicsContext
	{
	public:											// {PUBLIC}
		OpenGLContext(GLFWwindow* mainwindowHandle);// Constructor
		virtual void Init() override;				// (Virtual) (Override) Initilization Function
		virtual void SwapBuffers() override;		// (Virtual) (Override) Swap Buffers Function
	private:										// {PRIVATE}
		GLFWwindow* windowHandle;					// GLFW Window Variable, window handle
	};
}

