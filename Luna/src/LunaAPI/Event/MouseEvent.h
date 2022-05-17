#pragma once
#include "Lunapch.h"
#include "Event.h"

namespace Luna {

	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			: m_MouseX(x), m_MouseY(y) {}

		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }

		EVENT_TYPE(MouseMoved)
		EVENT_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_MouseX;
		float m_MouseY;
	};


	class MouseWheelScrolledEvent : public Event
	{
	public:
		MouseWheelScrolledEvent(float xOffset, float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {}

		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

		EVENT_TYPE(MouseWheelScrolled)
		EVENT_CATEGORY(EventCategoryMouse | EventCategoryInput)	

	private:
			float m_XOffset;
			float m_YOffset;
	};

	class MouseButtonEvent : public Event
	{

	public:
		MouseButtonEvent(int mouseButton)
			: m_MouseButton(mouseButton) {}

		inline float GetMouseButton() const { return m_MouseButton; }

		//EVENT_CLASS_TYPE(MouseWheelScrolled)
		EVENT_CATEGORY(EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton)

	protected:
		int m_MouseButton;
	};


	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:

		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button) {}


		EVENT_TYPE(MouseButtonPressed)
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:

		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {}

		EVENT_TYPE(MouseButtonReleased)
	};
}