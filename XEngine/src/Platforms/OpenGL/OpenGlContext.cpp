// Top Files
#include "Xpch.h"
// Open GL Files
#include "OpenGlContext.h"
// GLFW Library Files
#include <GLFW/glfw3.h>
// GLAD Library Files
#include <GLAD/glad.h>
namespace XEngine
{
	// Contructor 
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : mainWindowHandle(windowHandle) { XCORE_ASSERT(windowHandle, "Window handle doesn't exist or is equal to null!") }
	// Initilization Function: Initilization of OpenGL Context
	void OpenGLContext::Init()
	{
		// mainWindowHandle is now the current context
		glfwMakeContextCurrent(mainWindowHandle);
		// Local status variable is equal to the initilization outcome of GLAD
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		// If status is equal to false(or 0) then send error
		XCORE_ASSERT(status, "Failed to initialize Glad!");
		// Print GPU info
		XCORE_INFO("OpenGL Renderer: {0} {1} {2} ", glGetString(GL_VENDOR), glGetString(GL_RENDERER), glGetString(GL_VERSION));
	}
	// Swap Buffers Function
	void OpenGLContext::SwapBuffers() { glfwSwapBuffers(mainWindowHandle); }
}