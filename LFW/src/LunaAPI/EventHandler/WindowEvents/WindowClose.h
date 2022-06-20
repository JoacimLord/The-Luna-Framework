#pragma once

#include "LFWpch.h"
#include "LunaAPI/EventHandler/MainEventBaseClass.h"

namespace Luna {

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		CHECK_TYPE(WindowClose)
		CHECK_CATEGORY(EventCategoryApplication)
	};
}