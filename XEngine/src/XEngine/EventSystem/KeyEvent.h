#pragma once
#pragma region INCLUDE / NAMESPACES
#include "Event.h"
#include <sstream>
#pragma endregion
namespace XEngine 
{
	#pragma region KEY EVENT CLASS
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
	#pragma endregion
	#pragma region KEY PRESSED EVENT CLASS
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
	#pragma endregion
	#pragma region KEY RELEASED EVENT CLASS
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
	#pragma endregion
}