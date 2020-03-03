#pragma region INCLUDE / NAMESPACE
#include "Xpch.h"
#include "Win10Window.h"
#pragma endregion
namespace XEngine
{
	static bool s_GLFWInitialized = false;
	Window* Window::Create(const WindowProps& props) { return new Win10Window(props); }
	Win10Window::Win10Window(const WindowProps& props) { Init(props); }
	Win10Window::~Win10Window() { Shutdown(); }
	void Win10Window::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;
		// Info Message
		X_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);
		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			X_CORE_ASSERT(success, "Could not intialize GLFW");
			s_GLFWInitialized = true;
		}
		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
	}
	void Win10Window::Shutdown() { glfwDestroyWindow(m_Window); }
	void Win10Window::OnUpdate() 
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}
	void Win10Window::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else			
			glfwSwapInterval(0);
		m_Data.VSync = enabled;
	}
	bool Win10Window::IsVSync() const { return m_Data.VSync; }
}