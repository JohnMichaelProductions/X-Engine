#pragma once
#pragma region INCLUDE / NAMESPACES
#include "Event.h" 
#include "XEngine/Xpch.h"
#pragma endregion
namespace XEngine 
{
	#pragma region MOUSE MOVED EVENT CLASS
	class XENGINE_API MouseMovedEvent : public Event
	{
	public:
		// Function: Mouse movement data
		MouseMovedEvent(float x, float y) : m_MouseX(x), m_MouseY(y) {}
		// Fucntion: Returns X position of the mouse 
		inline float GetX() const { return m_MouseX; }
		// Fucntion: Returns Y position of the mouse 
		inline float GetY() const { return m_MouseY; }
		// Function: Prints mouse X and Y data
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}
		// Macros
		EVENT_CLASS_TYPE(MouseMoved)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		// Mouse X and Y floats
		float m_MouseX, m_MouseY;
	};
	#pragma endregion
	#pragma region MOUSE SCROLLED EVENT CLASS
	class XENGINE_API MouseScrolledEvent : public Event
	{
	public:
		// Function: Mouse offset data
		MouseScrolledEvent(float xOffset, float yOffset) : m_XOffset(xOffset), m_YOffset(yOffset) {}
		// Function: Returns X offset
		inline float GetXOffset() const { return m_XOffset; }
		// Function: Returns Y offset
		inline float GetYOffset() const { return m_YOffset; }
		// Function: Prints X and Y offset as an event
		std::string ToString() const override
		{
			std::stringstream ss;
			// Uses previously defined functions to print data
			ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}
		// Macro
		EVENT_CLASS_TYPE(MouseScrolled)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		// X and Y offset floats
		float m_XOffset, m_YOffset;
	};
	#pragma endregion
	#pragma region MOUSE BUTTON EVENT CLASS
	class XENGINE_API MouseButtonEvent : public Event
	{
	public:
		// Function: Returns the mouse button
		inline int GetMouseButton() const { return m_Button; }
		// Macro
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	protected:
		MouseButtonEvent(int button) : m_Button(button) {}
		// Button integer
		int m_Button;
	};
	#pragma endregion
	#pragma region MOUSE BUTTON PRESSED EVENT CLASS
	class XENGINE_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		// Function: Returns pressed mouse button
		MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}
		// Function: Prints pressed mouse button
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}
		// Macro
		EVENT_CLASS_TYPE(MouseButtonPressed)
	};
	#pragma endregion
	#pragma region MOUSE BUTTON RELEASED CLASS
	class XENGINE_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		// Function: Released button data
		MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}
		// Function: Prints released button data
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}
		// Macro
		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
	#pragma endregion
}