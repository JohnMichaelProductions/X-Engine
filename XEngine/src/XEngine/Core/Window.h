// Window class and window properties struct
#pragma once
#include "Xpch.h"
#include "XCore.h"
#include "../EventSystem/Event.h"
namespace XEngine
{
	struct WindowProps
	{
		WindowProps(const std::string& title = "X-Engine", unsigned int width = 1280, unsigned int height = 720) : Title(title), Width(width), Height(height)
			{ XCORE_INFO("Window Properties: Title: {0} Width: {1} Height: {2} ", Title, Height, Width); }
		std::string Title;
		unsigned int Width;
		unsigned int Height;
	};
	class XENGINE_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;
		virtual ~Window() 
			{ XCORE_INFO("Window has been destroyed"); }
		virtual void OnUpdate() = 0;
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;
		virtual void* GetNativeWindow() const = 0;
		static Window* Create(const WindowProps& props = WindowProps());
	};
}