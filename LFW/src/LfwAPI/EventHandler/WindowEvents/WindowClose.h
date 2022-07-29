#pragma once

#include "LFWpch.h"
#include "LfwAPI/EventHandler/MainEventBaseClass.h"

namespace LFW {

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		CHECK_TYPE(WindowClose)
		CHECK_CATEGORY(EventCategoryApplication)
	};
}