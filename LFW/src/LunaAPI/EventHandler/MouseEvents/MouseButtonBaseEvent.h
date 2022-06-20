#pragma once

#include "LFWpch.h"
#include "LunaAPI/EventHandler/MainEventBaseClass.h"

namespace Luna {

	class MouseButtonEvent : public Event
	{
	public:
		MouseButtonEvent(int mouseButton)
			: m_MouseButton(mouseButton) {}

		inline float GetMouseButton() const { return m_MouseButton; }

		CHECK_CATEGORY(EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton)

	protected:
		int m_MouseButton;
	};
}