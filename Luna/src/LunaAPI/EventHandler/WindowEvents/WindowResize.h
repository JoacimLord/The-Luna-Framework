#pragma once

#include "Lunapch.h"
#include "LunaAPI/EventHandler/MainEventBaseClass.h"


//DELA UPP KLASSERNA

namespace Luna {

	class WindowResizeEvent : public Event
	{
	private:
		unsigned int m_Width;
		unsigned int m_Height;

	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height) {}

		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }



		CHECK_TYPE(WindowResize)
		CHECK_CATEGORY(EventCategoryApplication)
	};
}

//MainEventBaseClass