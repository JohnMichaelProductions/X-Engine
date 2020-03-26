#include "Xpch.h"
#include "Win10Window.h"
#include "XEngine/EventSystem/ApplicationEvent.h"
#include "XEngine/EventSystem/KeyEvent.h"
#include "XEngine/EventSystem/MouseEvent.h"
#include "Platforms/OpenGL/OpenGlContext.h"
namespace XEngine
{
	static bool GLFWInitialized;										// GLFW Initialized Variable
	static void GLFWErrorCallback(int error, const char* description)	// GLFW Error Callback Function: Throws error if theres a problem
		{ XCORE_ERROR("GLFW Error ({0}): {1}", error, description); };
	Window* Window::Create(const WindowProps& props)					// Create Function: Creates window with the windows properties class, returns a new Windows 10 window
		{ return new Win10Window(props); }
	Win10Window::Win10Window(const WindowProps& props)					// Constructor: Initilizes properties
		{ Init(props); }
	Win10Window::~Win10Window()											// Destructor: Calls shutdown function to shut down the window
		{ Shutdown(); }
	void Win10Window::Init(const WindowProps& props)											// initialization Function
	{
		windowData.Title = props.Title;															// Set Window Title
		windowData.Width = props.Width;															// Set Window Width
		windowData.Height = props.Height;														// Set Window Height
		XCORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);	// Log Creation with window details
		if (!GLFWInitialized)																	// If GLFW is not initilized
		{
			int success = glfwInit();															// Success integer is equal to glfwInit
			XCORE_ASSERT(success, "Could not intialize GLFW");									// If GLFW couldn't be initialized throw an error
			glfwSetErrorCallback(GLFWErrorCallback);											// Call glfwSetErrorCallback with GLFWErrorCallback as the parameter
			GLFWInitialized = true;																// Set GLFWInitialized variable to true, if successful
		}
		window = glfwCreateWindow((int)props.Width, (int)props.Height, windowData.Title.c_str(), nullptr, nullptr);		// Creates window and store it in the window variable
		windowContext = new OpenGLContext(window);																		// Creates context for OpenGL and stores it in the window Context Variable
		windowContext->Init();																							// Calls windowContext initialization function
		// Sets the active windows data to the windowData variable
		glfwSetWindowUserPointer(window, &windowData);
		// Set V Sync to true
		SetVSync(true);
		// Set Window Size Callback Function
		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;
			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});
		// Set Window Close Callback Function
		glfwSetWindowCloseCallback(window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});
		// Set Key Callback Function
		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
			}
		});
		// Set Char Callback Function
		glfwSetCharCallback(window, [](GLFWwindow* window, unsigned int keycode)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent event(keycode);
			data.EventCallback(event);
		});
		// Set Mouse Button Callback Function
		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});
		// Set Scroll Callback Function
		glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});
		// Set Cursor Pos Call Back Function
		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});
	}
	// Shutdown Function: Destroys window
	void Win10Window::Shutdown() { glfwDestroyWindow(window); }
	void Win10Window::OnUpdate() 
	{
		glfwPollEvents();
		windowContext->SwapBuffers();
	}
	// Set V Sync Function: Sets V Sync on or off
	void Win10Window::SetVSync(bool enabled)
	{
		// If enabled equals true swap GLFW interval to one
		if (enabled)
			glfwSwapInterval(1);
		// If enabled equals false swap GLFW interval to zero
		else			
			glfwSwapInterval(0);
		// Set VSync to what enabled equals
		windowData.VSync = enabled;
	}
	// Is V Sync Function: Returns V Sync Data
	bool Win10Window::IsVSync() const { return windowData.VSync; }
}
