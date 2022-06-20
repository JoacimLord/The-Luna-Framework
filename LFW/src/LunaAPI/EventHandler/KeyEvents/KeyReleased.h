#pragma once
#include "LFWpch.h"
#include "LunaAPI/EventHandler/MainEventBaseClass.h"
#include "LunaAPI/EventHandler/KeyEvents/KeyButtonBaseEvent.h"

namespace Luna {

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {}

		CHECK_TYPE(KeyReleased)
	};
}