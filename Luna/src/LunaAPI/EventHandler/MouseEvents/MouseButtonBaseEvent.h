#pragma once

#include "Lunapch.h"
#include "LunaAPI/EventHandler/MainEventBaseClass.h"

namespace Luna {

	class MouseButtonEvent : public Event
	{
	//This needs to be here for some reason. Won't compile if it's below the function?
	protected:
		int m_MouseButton;

		MouseButtonEvent(int mouseButton)
			: m_MouseButton(mouseButton) {}

	public:
		inline float GetMouseButton() const { return m_MouseButton; }

		CHECK_CATEGORY(EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton)
	};
}