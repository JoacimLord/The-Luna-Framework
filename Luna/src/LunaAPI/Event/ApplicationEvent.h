#pragma once
#include "Lunapch.h"
#include "Event.h"

namespace Luna {

	class WindowResizeEvent : public Event
	{

	public:
		WindowResizeEvent(uint32_t width, uint32_t height)
			: m_Width(width), m_Height(height) {}

		//inline unsigned int GetWidth() const { return m_Width; }
		//inline unsigned int GetHeight() const { return m_Height; }
		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }

		EVENT_TYPE(WindowResize)
		EVENT_CATEGORY(EventCategoryApplication)

	private:
		uint32_t m_Width;
		uint32_t m_Height;
	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		EVENT_TYPE(WindowClose)
		EVENT_CATEGORY(EventCategoryApplication)
	};

	class ApplicationTickEvent : public Event
	{

	public:
		ApplicationTickEvent() {}

		EVENT_TYPE(ApplicationTick)
		EVENT_CATEGORY(EventCategoryApplication)
	};

	class ApplicationUpdateEvent : public Event
	{

	public:
		ApplicationUpdateEvent() {}

		EVENT_TYPE(ApplicationUpdate)
		EVENT_CATEGORY(EventCategoryApplication)
	};

	class ApplicationRenderEvent : public Event
	{
	public:
		ApplicationRenderEvent() {}

		EVENT_TYPE(ApplicationRender)
		EVENT_CATEGORY(EventCategoryApplication)
	};
}