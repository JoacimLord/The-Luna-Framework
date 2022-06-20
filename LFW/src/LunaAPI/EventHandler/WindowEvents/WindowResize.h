#pragma once

#include "LFWpch.h"
#include "LunaAPI/EventHandler/MainEventBaseClass.h"

namespace Luna {

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height) {}

		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }

		CHECK_TYPE(WindowResize)
		CHECK_CATEGORY(EventCategoryApplication)

	private:
		unsigned int m_Width;
		unsigned int m_Height;
	};
}