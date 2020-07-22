// Window class and window properties struct
#pragma once
#include "Xpch.h"
#include "XEngine/Core/XCore.h"
#include "XEngine/EventSystem/Event.h"
namespace XEngine
{
	struct WindowProps
	{
		WindowProps(const std::string& title = "X-Engine", unsigned int width = 1280, unsigned int height = 720) : Title(title), Width(width), Height(height) 
		{
			// Windows 10 Implementation
			//RECT desktop;
			//const HWND hDesktop = GetDesktopWindow();
			//GetWindowRect(hDesktop, &desktop);
			//Width = desktop.right /1.5f;
			//Height = desktop.bottom / 1.5f;
		}
		std::string Title;
		unsigned int Width;
		unsigned int Height;
	};
	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;
		virtual ~Window() {}
		virtual void OnUpdate() = 0;
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;
		virtual void* GetNativeWindow() const = 0;
		static Scope<Window> Create(const WindowProps& props = WindowProps());
	};
}