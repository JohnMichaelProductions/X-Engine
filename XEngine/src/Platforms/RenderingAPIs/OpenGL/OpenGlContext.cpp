// Source file for OpenGL Context Class
#include "Xpch.h"
#include "OpenGlContext.h"
#include <GLFW/glfw3.h>
#include <GLAD/glad.h>
namespace XEngine
{
	OpenGLContext::OpenGLContext(GLFWwindow* mainwindowHandle) : windowHandle(mainwindowHandle)
	{
		XCORE_ASSERT(mainwindowHandle, "Window handle doesn't exist or is equal to null!");
		XCORE_INFO("OpenGL Context has been created");
	}
	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(windowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		XCORE_ASSERT(status, "Failed to initialize Glad!");
		XCORE_INFO("Glad has been initialized!");
		XCORE_INFO("OpenGL Renderer: {0} {1} {2} ", glGetString(GL_VENDOR), glGetString(GL_RENDERER), glGetString(GL_VERSION));
		#ifdef HZ_ENABLE_ASSERTS
		int versionMajor;
		int versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);
		XCORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Hazel requires at least OpenGL version 4.5!");
		#endif
	}
	void OpenGLContext::SwapBuffers()
		{ glfwSwapBuffers(windowHandle); }
}