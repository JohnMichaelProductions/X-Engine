#pragma once		
// Mid Files
#include "XEngine/Window.h"
// Renderer Files
#include "XEngine/Renderer/GraphicsContext.h"
// GLFW Library Files
#include <GLFW/glfw3.h>
namespace XEngine
{
	class Win10Window : public Window
	{
	public:
		// ---FUNCTIONS---
		Win10Window(const WindowProps& props);
		virtual ~Win10Window();
		void OnUpdate() override;
		inline unsigned int GetWidth() const override { return windowData.Width; }
		inline unsigned int GetHeight() const override { return windowData.Height; }
		inline void SetEventCallback(const EventCallbackFn& callback) override { windowData.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
		inline virtual void* GetNativeWindow() const { return mainWindow; }
		// ---------------
	private:
		// ---FUNCTIONS---
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
		// ---------------
	private:
		// Window Variable
		GLFWwindow* mainWindow;
		GraphicsContext* mainContext;
		// Window Data Struct: Struct for window properties
		struct WindowData
		{
			// string: Title of Window
			std::string Title;
			// ints: Length of Window
			unsigned int Width, Height;
			// bool: VSync on or off
			bool VSync;
			// EventCallBack variable
			EventCallbackFn EventCallback;
		};
		// Window Data Variable
		WindowData windowData;
	};	
}

