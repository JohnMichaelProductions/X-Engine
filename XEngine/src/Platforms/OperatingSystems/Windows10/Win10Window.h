// Header file for Win10Window class, configured for Windows 10
#pragma once
#include <GLFW/glfw3.h>
#include "XEngine/Core/Window.h"
#include "XEngine/GraphicsSystem/GraphicsContext.h"
namespace XEngine
{
	class Win10Window : public Window
	{
	public:
		// Defined in Source File
		Win10Window(const WindowProps& props);
		virtual ~Win10Window();
		void OnUpdate() override;
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
		// Prototype in Header File
		unsigned int GetWidth() const override
			{ return windowData.Width; }
		unsigned int GetHeight() const override 
			{ return windowData.Height; }
		void SetEventCallback(const EventCallbackFn& callback) override 
			{ windowData.EventCallback = callback; }
		virtual void* GetNativeWindow() const 
			{ return window; }
	private:
		// Defined in Source File
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;
			EventCallbackFn EventCallback;
		};
		GLFWwindow* window;
		Scope<GraphicsContext> windowContext;
		WindowData windowData;
	};
}