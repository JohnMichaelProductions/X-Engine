// Mouse event classes
#pragma once
#include "Event.h" 
namespace XEngine 
{
	class XENGINE_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y) : eventMouseX(x), eventMouseY(y)
			{ /* Called everytime the mouse is moved */ }
		inline float GetX() const
			{ return eventMouseX; }
		inline float GetY() const
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
	class XENGINE_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset) : eventXOffset(xOffset), eventYOffset(yOffset) {}
		inline float GetXOffset() const 
			{ return eventXOffset; }
		inline float GetYOffset() const 
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
	class XENGINE_API MouseButtonEvent : public Event
	{
	public:
		inline int GetMouseButton() const
			{ return mouseButton; }
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	protected:
		MouseButtonEvent(int button) : mouseButton(button) {}
		int mouseButton;
	};
	class XENGINE_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << mouseButton;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseButtonPressed)
	};
	class XENGINE_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << mouseButton;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}