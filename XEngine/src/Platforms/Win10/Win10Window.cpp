#include "Xpch.h"
#include "Win10Window.h"
#include "XEngine/EventSystem/ApplicationEvent.h"
#include "XEngine/EventSystem/KeyEvent.h"
#include "XEngine/EventSystem/MouseEvent.h"
#include "Platforms/OpenGL/OpenGlContext.h"
namespace XEngine
{
	static bool GLFWInitialized;
	static void GLFWErrorCallback(int error, const char* description)
		{ XCORE_ERROR("GLFW Error ({0}): {1}", error, description); };
	Window* Window::Create(const WindowProps& props)
		{ return new Win10Window(props); }
	Win10Window::Win10Window(const WindowProps& props)
		{ Init(props); }
	Win10Window::~Win10Window()
		{ Shutdown(); }
	void Win10Window::Init(const WindowProps& props)
	{
		windowData.Title = props.Title;
		windowData.Width = props.Width;
		windowData.Height = props.Height;
		XCORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);
		if (!GLFWInitialized)
		{
			int success = glfwInit();
			XCORE_ASSERT(success, "Could not intialize GLFW");
			glfwSetErrorCallback(GLFWErrorCallback);
			GLFWInitialized = true;
		}
		window = glfwCreateWindow((int)props.Width, (int)props.Height, windowData.Title.c_str(), nullptr, nullptr);
		windowContext = new OpenGLContext(window);
		windowContext->Init();
		glfwSetWindowUserPointer(window, &windowData);
		SetVSync(true);
		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;
			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});
		glfwSetWindowCloseCallback(window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});
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
		glfwSetCharCallback(window, [](GLFWwindow* window, unsigned int keycode)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent event(keycode);
			data.EventCallback(event);
		});
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
		glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});
		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});
	}
	void Win10Window::Shutdown() { glfwDestroyWindow(window); }
	void Win10Window::OnUpdate() 
	{
		glfwPollEvents();
		windowContext->SwapBuffers();
	}
	void Win10Window::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
		windowData.VSync = enabled;
	}
	bool Win10Window::IsVSync() const 
		{ return windowData.VSync; }
}