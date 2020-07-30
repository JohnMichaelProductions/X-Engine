// Mouse event classes
#pragma once
#include "XEngine/InputSystem/Input.h"
#include "XEngine/EventSystem/Event.h" 
namespace XEngine 
{
	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y) : eventMouseX(x), eventMouseY(y)
			{ /* Called everytime the mouse is moved */ }
		float GetX() const
			{ return eventMouseX; }
		float GetY() const
			{ return eventMouseY; }
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << eventMouseX << ", " << eventMouseY;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseMoved)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float eventMouseX, eventMouseY;
	};
	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset) : eventXOffset(xOffset), eventYOffset(yOffset) {}
		float GetXOffset() const 
			{ return eventXOffset; }
		float GetYOffset() const 
			{ return eventYOffset; }
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float eventXOffset, eventYOffset;
	};
	class MouseButtonEvent : public Event
	{
	public:
		inline MouseCode GetMouseButton() const
			{ return mouseButton; }
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	protected:
		MouseButtonEvent(MouseCode button) : mouseButton(button) {}
		MouseCode mouseButton;
	};
	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(MouseCode button) : MouseButtonEvent(button) {}
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << mouseButton;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseButtonPressed)
	};
	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(MouseCode button) : MouseButtonEvent(button) {}
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << mouseButton;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}