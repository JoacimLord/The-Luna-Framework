#pragma once

#include "LFWpch.h"
#include "LfwAPI/EventHandler/MainEventBaseClass.h"
#include "LfwAPI/EventHandler/MouseEvents/MouseButtonBaseEvent.h"

namespace LFW {

	class MouseWheelScrolledEvent : public Event
	{
	public:
		MouseWheelScrolledEvent(float xOffset, float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {}

		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

		CHECK_TYPE(MouseWheelScrolled)
		CHECK_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_XOffset;
		float m_YOffset;
	};
}