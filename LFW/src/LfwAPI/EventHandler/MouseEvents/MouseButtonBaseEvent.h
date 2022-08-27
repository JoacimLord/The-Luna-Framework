#pragma once

#include "LFWpch.h"
#include "LfwAPI/EventHandler/MainEventBaseClass.h"

namespace LFW {

	class MouseButtonEvent : public Event
	{
	public:
		MouseButtonEvent(int mouseButton)
			: m_mouseButton(mouseButton) {}

		inline float GetMouseButton() const { return m_mouseButton; }

		CHECK_CATEGORY(EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton)

	protected:
		int m_mouseButton;
	};
}