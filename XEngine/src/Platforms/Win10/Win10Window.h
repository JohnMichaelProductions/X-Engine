// Header file for Win10Window class, configured for Windows 10
#pragma once
#include "XEngine/Window.h"
#include "XEngine/Renderer/GraphicsContext.h"
#include <GLFW/glfw3.h>
namespace XEngine
{
	class Win10Window : public Window
	{
	public:
		Win10Window(const WindowProps& props);
		virtual ~Win10Window();
		void OnUpdate() override;
		inline unsigned int GetWidth() const override 
			{ return windowData.Width; }
		inline unsigned int GetHeight() const override 
			{ return windowData.Height; }
		inline void SetEventCallback(const EventCallbackFn& callback) override 
			{ windowData.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
		inline virtual void* GetNativeWindow() const 
			{ return window; }
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* window;
		GraphicsContext* windowContext;
		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;
			EventCallbackFn EventCallback;
		};
		WindowData windowData;
	};
}