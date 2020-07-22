// Key event classes
#pragma once
#include "XEngine/EventSystem/Event.h"
namespace XEngine 
{
	class KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const 
			{ return eventKeyCode; }
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(int keycode) : eventKeyCode(keycode) {}
		int eventKeyCode;
	};
	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeatCount) : KeyEvent(keycode), eventRepeatCount(repeatCount) {}
		inline int GetRepeatCount() const 
			{ return eventRepeatCount; }
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << eventKeyCode << " (" << eventRepeatCount << " repeats)";
			return ss.str();  
		}
		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int eventRepeatCount;
	};
	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << eventKeyCode;
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyReleased)
	};
	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keycode) : KeyEvent(keycode) {}
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTyped: " << eventKeyCode;
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyTyped)
	};
}