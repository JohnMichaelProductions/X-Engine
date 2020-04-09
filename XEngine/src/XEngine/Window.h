#pragma once
#include "Xpch.h"
#include "XCore.h"
#include "EventSystem/Event.h"
namespace XEngine
{
	struct WindowProps														// Window Properties
	{
		std::string Title;													// String Variable, Title of the window
		unsigned int Width;													// (Unsigned) Int, Width of the window
		unsigned int Height;												// (Unsigned) Int, Height of the window
		WindowProps(const std::string& title = "X-Engine", unsigned int width = 1280, unsigned int height = 720) : Title(title), Width(width), Height(height) // Window Properties Function: Sets properties
			{}
	};
	class XENGINE_API Window
	{
	public:																	// {PUBLIC}
		using EventCallbackFn = std::function<void(Event&)>;				
		virtual ~Window() {}												// Destructor
		virtual void OnUpdate() = 0;										// (Pure Virtual) On Update Function
		virtual unsigned int GetWidth() const = 0;							// (Pure Virtual) (Unsigned) (Const) Get Width Function 
		virtual unsigned int GetHeight() const = 0;							// (Pure Virtual) (Unsigned) (Const) Get Height Function
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;	// (Pure Virtual) Set Event Callback Function
		virtual void SetVSync(bool enabled) = 0;							// (Pure Virtual) Set V Sync Function
		virtual bool IsVSync() const = 0;									// (Pure Virtual) Is V Sync Function
		virtual void* GetNativeWindow() const = 0;							// (Pure Virtual) Get Native Window Function
		static Window* Create(const WindowProps& props = WindowProps());	// (Static) Create Function
	};
}