#pragma once
#include "Xpch.h"
#include "../XCore.h"
namespace XEngine
{
	enum class EventType
	{
		None = 0,
		WindowClose,
		WindowResize,
		WindowFocus,
		WindowLostFocus,
		WindowMoved,
		AppTick,
		AppUpdate,
		AppRender,
		KeyPressed,
		KeyReleased,
		KeyTyped,
		MouseButtonPressed,
		MouseButtonReleased,
		MouseMoved,
		MouseScrolled
	};
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};
	class XENGINE_API Event 
	{
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const
			{ return GetName(); }
		inline bool IsInCategory(EventCategory category)
			{ return GetCategoryFlags() & category; }
		bool handled = false;
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