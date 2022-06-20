#pragma once

#include "Lunapch.h"
#include "LunaAPI/EventHandler/MainEventBaseClass.h"
#include "LunaAPI/EventHandler/MouseEvents/MouseButtonBaseEvent.h"

namespace Luna {

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {}

		CHECK_TYPE(MouseButtonReleased)
	};
}