// Top Files
#include "Xpch.h"
#include "Win10Window.h"
// Event System Files
#include "XEngine/EventSystem/ApplicationEvent.h"
#include "XEngine/EventSystem/KeyEvent.h"
#include "XEngine/EventSystem/MouseEvent.h"
// GLAD Library Files
#include <GLAD/glad.h>
namespace XEngine
{
	// GLFW Initialized Variable
	static bool GLFWInitialized = false;
	// If GLFW doesn't work
	static void GLFWErrorCallback(int error, const char* description) { XCORE_ERROR("GLFW Error ({0}): {1}", error, description); };
	// Create Function: Creates Windows 10 window with the Constant Window Properties from WindowProps in Window.h
	Window* Window::Create(const WindowProps& props) { return new Win10Window(props); }
	// Constructor: Initializes Window Propeties on creation
	Win10Window::Win10Window(const WindowProps& props) { Init(props); }
	// Destructor: Calls Shutdown function on deletion
	Win10Window::~Win10Window() { Shutdown(); }
	// Init Function: Initializes Windows 10 Window
	void Win10Window::Init(const WindowProps& props)
	{
		// ---Basic Window Properties---
		windowData.Title = props.Title;
		windowData.Width = props.Width;
		windowData.Height = props.Height;
		// -----------------------------
		// Info Message
		XCORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);
		// If GLFW is not initialized, then initialized GLFW
		if (!GLFWInitialized)
		{
			// Local int is equal to whether GLFW was initialized or not
			int success = glfwInit();
			// If GLFW was not initialized throw an error
			XCORE_ASSERT(success, "Could not intialize GLFW");
			glfwSetErrorCallback(GLFWErrorCallback);
			// Set GLFWInitialized variable to true
			GLFWInitialized = true;
		}
		// Creates main window with the Windows 10 Window Properties
		mainWindow = glfwCreateWindow((int)props.Width, (int)props.Height, windowData.Title.c_str(), nullptr, nullptr);
		// Creates context based on the active window
		glfwMakeContextCurrent(mainWindow);
		// Local Variable status
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		// Throws error
		XCORE_ASSERT(status, "Failed to initialize GLAD");
		// Sets the active windows data to the windowData variable
		glfwSetWindowUserPointer(mainWindow, &windowData);
		// Set V Sync to true
		SetVSync(true);
		// Set Window Size Callback Function
		glfwSetWindowSizeCallback(mainWindow, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;
			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});
		// Set Window Close Callback Function
		glfwSetWindowCloseCallback(mainWindow, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});
		// Set Key Callback Function
		glfwSetKeyCallback(mainWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
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
		glfwSetCharCallback(mainWindow, [](GLFWwindow* window, unsigned int keycode)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent event(keycode);
			data.EventCallback(event);
		});
		// Set Mouse Button Callback Function
		glfwSetMouseButtonCallback(mainWindow, [](GLFWwindow* window, int button, int action, int mods)
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
		glfwSetScrollCallback(mainWindow, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});
		// Set Cursor Pos Call Back Function
		glfwSetCursorPosCallback(mainWindow, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});
	}
	// Shutdown Function: Destroys window
	void Win10Window::Shutdown() { glfwDestroyWindow(mainWindow); }
	void Win10Window::OnUpdate() 
	{
		glfwPollEvents();
		glfwSwapBuffers(mainWindow);
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
