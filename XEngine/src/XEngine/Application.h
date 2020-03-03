#pragma once
#pragma region INCLUDE / NAMESPACES
#include "XCore.h"
#include "EventSystem/Event.h"
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
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};
	#pragma endregion
	Application* CreateApplication();
}

