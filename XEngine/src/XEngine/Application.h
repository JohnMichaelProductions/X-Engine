#pragma once
#pragma region INCLUDE / NAMESPACES
#include "XCore.h"
#include "EventSystem/Event.h"
#include "../XEngine/EventSystem/ApplicationEvent.h"
#include "Window.h"
#pragma endregion
namespace XEngine
{
	#pragma region APPLICATION CLASS
	class XENGINE_API Application
	{
	public:
		// Creates functions
		Application();
		virtual ~Application();
		void Run();
		void OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};
	#pragma endregion
	Application* CreateApplication();
}

