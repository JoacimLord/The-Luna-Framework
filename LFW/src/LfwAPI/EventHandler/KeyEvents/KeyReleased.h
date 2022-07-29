#pragma once
#include "LFWpch.h"
#include "LfwAPI/EventHandler/MainEventBaseClass.h"
#include "LfwAPI/EventHandler/KeyEvents/KeyButtonBaseEvent.h"

namespace LFW {

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {}

		CHECK_TYPE(KeyReleased)
	};
}