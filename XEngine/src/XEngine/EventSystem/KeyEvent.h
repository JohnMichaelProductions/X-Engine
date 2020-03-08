#pragma once
#include "Event.h"
#include "Xpch.h"
namespace XEngine 
{
	class XENGINE_API KeyEvent : public Event
	{
	public:
		// Function: Returns key code of pressed key
		inline int GetKeyCode() const { return m_KeyCode; }
		// Macro
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(int keycode) : m_KeyCode(keycode) {}
		// Key Code Integer
		int m_KeyCode;
	};
	class XENGINE_API KeyPressedEvent : public KeyEvent
	{
	public:
		// Function: Key Pressed event with key code and repeat count
		KeyPressedEvent(int keycode, int repeatCount) : KeyEvent(keycode), m_RepeatCount(repeatCount) {}
		// Function: Returns how many times the key code was repeated
		inline int GetRepeatCount() const { return m_RepeatCount; }
		// Function: Prints which key code has been pressed and how
		// many times its been pressed
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();  
		}
		// Macro
		EVENT_CLASS_TYPE(KeyPressed)
	private:
		// Repeat Count Integer
		int m_RepeatCount;
	};
	class XENGINE_API KeyReleasedEvent : public KeyEvent
	{
	public:
		// Function: Released key's key code data
		KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}
		// Function: Prints which key code has been released
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}
		// Macro
		EVENT_CLASS_TYPE(KeyReleased)
	};
	class XENGINE_API KeyTypedEvent : public KeyEvent
	{
	public:
		// Function: Typed key's key code data
		KeyTypedEvent(int keycode) : KeyEvent(keycode) {}
		// Function: Prints which key code has been typed

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTyped: " << m_KeyCode;
			return ss.str();
		}
		// Macro
		EVENT_CLASS_TYPE(KeyTyped)
	};
}