#pragma once
#include "Xpch.h"
#include "../XCore.h"
namespace XEngine
{
	enum class EventType
	{
		// Event Types Enum:
		// All the events we want to record are in this enum
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
	enum EventCategory
	{
		// Event Category Enum:
		// With this enum we can single out events based on their category
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput       = BIT(1),
		EventCategoryKeyboard    = BIT(2),
		EventCategoryMouse       = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};
	class XENGINE_API Event 
	{
		// Event Class:
		// Base class for events
		// ----
		// Add Event Dispactcher Class as a friend so it
		// can access its private/protected members
	public:
		bool Handled = false;
		// Pure Virtual Function
		virtual EventType GetEventType() const = 0;
		// Pure Virtual Function
		virtual const char* GetName() const = 0;
		// Pure Virtual Function
		virtual int GetCategoryFlags() const = 0;
		// Function: Converts to string by getting event name
		virtual std::string ToString() const { return GetName(); }
		// Function: Is this event in the given category, 0 is false,
		// any other number refer to the Event Category enum
		inline bool IsInCategory(EventCategory category) { return GetCategoryFlags() & category; }
	};
	class EventDispatcher
	{
		// Event Dispactcher Class:
		// Class to dispactch events based on their type
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event) : m_Event(event) {}
		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};
	inline std::ostream& operator<<(std::ostream& os, const Event& e) { return os << e.ToString(); }
}
// Macro for event names
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; } virtual EventType GetEventType() const override { return GetStaticType(); } virtual const char* GetName() const override { return #type; }
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }
