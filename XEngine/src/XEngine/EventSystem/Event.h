#pragma once
#include "../XCore.h"
#include <string>
#include <functional>
namespace XEngine
{
	// Event Types Enum:
	// All the events we want to record are in this enum
	enum class EventType
	{
		None = 0,
		WindowClose,
		WindowResize,
		WindowFocus,
		WindowLostFocus,
		WindowMoved,
		AppTrick,
		AppUpdate,
		AppRender,
		KeyPressed,
		KeyReleased,
		MouseButtonPressed,
		MouseButtonReleased,
		MouseMoved,
		MouseScrolled
	};
	// Event Category Enum:
	// With this enum we can single out events based on their category
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput       = BIT(1),
		EventCategoryKeyboard    = BIT(2),
		EventCategoryMouse       = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};
//Macro for event names
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
virtual EventType GetEventType() const override { return GetStaticType(); }\
virtual const char* GetName() const override { return #type; }
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }
	// Event Class:
	// Base class for events
	class XENGINE_API Event 
	{
		friend class EventDispatcher;
	public:
		// Function: Return event type
		virtual EventType GetEventType() const = 0;
		// Function: Return event name
		virtual const char* GetName() const = 0;
		// Function: Return event category flags
		virtual int GetCategoryFlags() const = 0;
		// Function: Converts to string by getting event name
		virtual std::string ToString() const { return GetName(); }
		// Function: Is this event in the given category, 0 is false,
		// any other number refer to the Event Category enum
		inline bool IsInCategory(EventCategory category) { return GetCategoryFlags() & category; }
	protected:
		// This bool is important because we need to see whether it 
		// has been handled or not
		bool m_Handled = false;
	};
	// Event Dispactcher Class:
	// Class to dispactch events based on their type
	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event) : m_Event(event) {}
		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};
	inline std::ostream& operator<<(std::ostream& os, const Event& e) { return os << e.ToString(); }
}