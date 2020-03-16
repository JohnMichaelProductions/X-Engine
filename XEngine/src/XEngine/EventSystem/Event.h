#pragma once
// Top Files
#include "Xpch.h"
// Mid Files
#include "../XCore.h"
namespace XEngine
{
	// Event Type enum: All the events we want to record are in this enum
	enum class EventType
	{
		None = 0,
		// Application Events:
		WindowClose,
		WindowResize,
		WindowFocus,
		WindowLostFocus,
		WindowMoved,
		AppTick,
		AppUpdate,
		AppRender,
		// Key Events:
		KeyPressed,
		KeyReleased,
		KeyTyped,
		// Mouse Events:
		MouseButtonPressed,
		MouseButtonReleased,
		MouseMoved,
		MouseScrolled
	};
	// Event Category enum: With this enum we can single out events based on their category
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput       = BIT(1),
		EventCategoryKeyboard    = BIT(2),
		EventCategoryMouse       = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};
	// Event Class: Base Class for events
	class XENGINE_API Event 
	{
	public:
		// ---FUNCTIONS---
		bool Handled = false;
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		// To String Function: Returns Event Name
		virtual std::string ToString() const { return GetName(); }
		// Is In Category: Returns true or false based on whether the event is in the category that is specified
		inline bool IsInCategory(EventCategory category) { return GetCategoryFlags() & category; }
		// ---------------
	};
	// Event Dispactcher Class: Class to dispactch events based on their type
	class EventDispatcher
	{
		// New Type
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event) : mainEvent(event) {}
		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (mainEvent.GetEventType() == T::GetStaticType())
			{
				mainEvent.Handled = func(*(T*)&mainEvent);
				return true;
			}
			return false;
		}
	private:
		Event& mainEvent;
	};
	inline std::ostream& operator<<(std::ostream& os, const Event& e) { return os << e.ToString(); }
}
// Macro for event names
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; } virtual EventType GetEventType() const override { return GetStaticType(); } virtual const char* GetName() const override { return #type; }
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }
