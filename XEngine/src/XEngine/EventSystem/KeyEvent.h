// Key event classes
#pragma once
#include "XEngine/InputSystem/Input.h"
#include "XEngine/EventSystem/Event.h"
namespace XEngine 
{
	class KeyEvent : public Event
	{
	public:
		KeyCode GetKeyCode() const 
			{ return eventKeyCode; }
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(KeyCode keycode) : eventKeyCode(keycode) {}
		KeyCode eventKeyCode;
	};
	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(KeyCode keycode, int repeatCount) : KeyEvent(keycode), eventRepeatCount(repeatCount) {}
		int GetRepeatCount() const 
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
		KeyReleasedEvent(KeyCode keycode) : KeyEvent(keycode) {}
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
		KeyTypedEvent(KeyCode keycode) : KeyEvent(keycode) {}
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTyped: " << eventKeyCode;
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyTyped)
	};
}