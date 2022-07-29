#pragma once

#include "LFWpch.h"
#include "LfwAPI/EventHandler/MainEventBaseClass.h"
#include "LfwAPI/EventHandler/MouseEvents/MouseButtonBaseEvent.h"

namespace LFW {

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {}

		CHECK_TYPE(MouseButtonReleased)
	};
}