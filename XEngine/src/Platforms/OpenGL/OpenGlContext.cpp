#include "Xpch.h"
#include "OpenGlContext.h"
#include <GLFW/glfw3.h>
#include <GLAD/glad.h>
namespace XEngine
{
	OpenGLContext::OpenGLContext(GLFWwindow* mainwindowHandle) : windowHandle(mainwindowHandle)										// Constructor: Asserts if window handle doesn't exist
		{ XCORE_ASSERT(mainwindowHandle, "Window handle doesn't exist or is equal to null!") }
	void OpenGLContext::Init()																										// Initilization Function: Initilization of OpenGL
	{
		glfwMakeContextCurrent(windowHandle);																						// Makes mainWindowHandle the glfwContext
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);															// Status Varaible
		XCORE_ASSERT(status, "Failed to initialize Glad!");																			// If GLAD failed then assert
		XCORE_INFO("OpenGL Renderer: {0} {1} {2} ", glGetString(GL_VENDOR), glGetString(GL_RENDERER), glGetString(GL_VERSION));		// Log Open GL Render Info
	}
	void OpenGLContext::SwapBuffers()																								// Swap Buffers Function: Swaps mainWindowHanlde Buffers
		{ glfwSwapBuffers(windowHandle); }
}