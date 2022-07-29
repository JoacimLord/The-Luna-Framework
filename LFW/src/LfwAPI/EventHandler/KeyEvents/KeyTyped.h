#pragma once
#include "LFWpch.h"
#include "LfwAPI/EventHandler/MainEventBaseClass.h"
#include "LfwAPI/EventHandler/KeyEvents/KeyButtonBaseEvent.h"

namespace LFW {

	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keycode)
			: KeyEvent(keycode) {}

		CHECK_TYPE(KeyTyped)
	};
}