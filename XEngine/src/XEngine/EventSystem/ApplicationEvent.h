#pragma once
#pragma region INCLUDE / NAMESPACES
#include "Event.h"
#pragma endregion
namespace XEngine 
{
	#pragma region WINDOW RESIZE EVENT CLASS
	class XENGINE_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height) : m_Width(width), m_Height(height) {}
		// Function: Returns window width
		inline unsigned int GetWidth() const { return m_Width; }
		// Function: Returns window height
		inline unsigned int GetHeight() const { return m_Height; }
		// Function: Prints Window Resize Event info
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}
		// Macros
		EVENT_CLASS_TYPE(WindowResize)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
		unsigned int m_Width, m_Height;
	};
	#pragma endregion
	#pragma region WINDOW CLOSE EVENT CLASS
	class XENGINE_API WindowCloseEvent : public Event
	{
	public:
		// Function: Window Closes Event
		WindowCloseEvent() {}
		// Macros
		EVENT_CLASS_TYPE(WindowClose)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
	#pragma endregion
	#pragma region APP TICK EVENT CLASS
	class XENGINE_API AppTickEvent : public Event
	{
	public:
		AppTickEvent() {}
		// Macros
		EVENT_CLASS_TYPE(AppTick)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
	#pragma endregion
	#pragma region APP UPDATE EVENT CLASS
	class XENGINE_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() {}
		// Macros
		EVENT_CLASS_TYPE(AppUpdate)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
	#pragma endregion
	#pragma region APP RENDER EVENT CLASS
	class XENGINE_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() {}
		// Macros
		EVENT_CLASS_TYPE(AppRender)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
	#pragma endregion
}