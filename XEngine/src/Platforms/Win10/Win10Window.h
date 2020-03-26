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
		inline unsigned int GetWidth() const override 
			{ return windowData.Width; }
		inline unsigned int GetHeight() const override 
			{ return windowData.Height; }
		inline void SetEventCallback(const EventCallbackFn& callback) override { windowData.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
		inline virtual void* GetNativeWindow() const { return window; }
		// ---------------
	private:
		virtual void Init(const WindowProps& props);	// (Virtual)
		virtual void Shutdown();						// (Virtual)
	private:
		GLFWwindow* window;					// GLFW Variable, window 
		GraphicsContext* windowContext;		// Graphics Context Variable, graphics context for window
		struct WindowData					// Window Data Struct: Stores all data for the window properties
		{
			std::string Title;				// String Variable, Title of the window
			unsigned int Width, Height;		// Integer Variables, Width and Height of the window
			bool VSync;						// Bool Variable, tells whether vsync is on
			EventCallbackFn EventCallback;	// EventCallbackFn Variable
		};
		WindowData windowData;				// Window Data Variable, window data stored in this struct
	};	
}

