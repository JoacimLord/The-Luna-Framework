#pragma once
#include "LFWpch.h"
#include "LfwAPI/EventHandler/MainEventBaseClass.h"
#include "LfwAPI/EventHandler/KeyEvents/KeyButtonBaseEvent.h"

namespace LFW {

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }
		CHECK_TYPE(KeyPressed)

	private:
		int m_RepeatCount;
	};
}