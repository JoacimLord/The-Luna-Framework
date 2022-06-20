#pragma once
#include "LFWpch.h"
#include "LunaAPI/EventHandler/MainEventBaseClass.h"

namespace LFW {

	class KeyEvent : public Event
	{
	protected:
		KeyEvent(int keycode)
			: m_KeyCode(keycode) {}

	public:
		inline int GetKeyCode() const { return m_KeyCode; }
		CHECK_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		int m_KeyCode;
	};
}

