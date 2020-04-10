#pragma once
#include "Xpch.h"
#include "../XCore.h"
namespace XEngine
{
	enum class EventType	// Event Type enum: All the events we want to record are in this enum
	{
		None = 0,
		WindowClose,		// Application Events
		WindowResize,		// Application Events
		WindowFocus,		// Application Events
		WindowLostFocus,	// Application Events
		WindowMoved,		// Application Events
		AppTick,			// Application Events
		AppUpdate,			// Application Events
		AppRender,			// Application Events
		KeyPressed,			// Key Events
		KeyReleased,		// Key Events
		KeyTyped,			// Key Events
		MouseButtonPressed,	// Mouse Events
		MouseButtonReleased,// Mouse Events
		MouseMoved,			// Mouse Events
		MouseScrolled		// Mouse Events
	};
	enum EventCategory		// Event Category enum: With this enum we can single out events based on their category
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput       = BIT(1),
		EventCategoryKeyboard    = BIT(2),
		EventCategoryMouse       = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};
	class XENGINE_API Event 
	{
	public:
		virtual EventType GetEventType() const = 0;			// (Pure Virtual) (Const) Get Event Type Function
		virtual const char* GetName() const = 0;			// (Pure Virtual) (Const) Get Name Function
		virtual int GetCategoryFlags() const = 0;			// (Pure Virtual) (Const) Get Category Flags Function
		virtual std::string ToString() const				// (Virtual) (Const) To String: Uses the Get Name function to get the category name and returns it as a string
			{ return GetName(); }
		inline bool IsInCategory(EventCategory category)	// (Inline) Returns true or false based on if the event is in the specified event category
			{ return GetCategoryFlags() & category; }
		bool handled = false;								// Boolean Variable
	};
	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event) : memberEvent(event) 
			{}
		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (memberEvent.GetEventType() == T::GetStaticType())
			{
				memberEvent.handled = func(*(T*)&memberEvent);
				return true;
			}
			return false;
		}
	private:
		Event& memberEvent;
	};
	inline std::ostream& operator<<(std::ostream& os, const Event& e) { return os << e.ToString(); }
}
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; } virtual EventType GetEventType() const override { return GetStaticType(); } virtual const char* GetName() const override { return #type; }
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }
