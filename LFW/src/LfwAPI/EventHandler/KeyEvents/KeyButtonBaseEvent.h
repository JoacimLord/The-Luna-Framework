#pragma once
#include "LFWpch.h"
#include "LfwAPI/EventHandler/MainEventBaseClass.h"

namespace LFW {

	class KeyEvent : public Event
	{
	protected:
		KeyEvent(int keycode)
			: m_keyCode(keycode) {}

	public:
		inline int GetKeyCode() const { return m_keyCode; }
		CHECK_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		int m_keyCode;
	};
}

