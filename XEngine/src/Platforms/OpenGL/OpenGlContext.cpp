#include "Xpch.h"
#include "OpenGlContext.h"
#include <GLFW/glfw3.h>
#include <GLAD/glad.h>
namespace XEngine
{
	OpenGLContext::OpenGLContext(GLFWwindow* mainwindowHandle) : windowHandle(mainwindowHandle)
		{ XCORE_ASSERT(mainwindowHandle, "Window handle doesn't exist or is equal to null!") }
	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(windowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		XCORE_ASSERT(status, "Failed to initialize Glad!");
		XCORE_INFO("OpenGL Renderer: {0} {1} {2} ", glGetString(GL_VENDOR), glGetString(GL_RENDERER), glGetString(GL_VERSION));
	}
	void OpenGLContext::SwapBuffers()
		{ glfwSwapBuffers(windowHandle); }
}