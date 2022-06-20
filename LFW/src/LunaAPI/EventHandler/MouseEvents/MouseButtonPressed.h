#pragma once

#include "LFWpch.h"
#include "LunaAPI/EventHandler/MainEventBaseClass.h"
#include "LunaAPI/EventHandler/MouseEvents/MouseButtonBaseEvent.h"

namespace Luna {

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button) {}

		CHECK_TYPE(MouseButtonPressed)
	};
}