#pragma once

#include "LFWpch.h"
#include "LfwAPI/EventHandler/MainEventBaseClass.h"

namespace LFW {

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_width(width), m_height(height) {}

		inline unsigned int GetWidth() const { return m_width; }
		inline unsigned int GetHeight() const { return m_height; }

		CHECK_TYPE(WindowResize)
		CHECK_CATEGORY(EventCategoryApplication)

	private:
		unsigned int m_width;
		unsigned int m_height;
	};
}