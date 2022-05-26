#pragma once

/*
	Thank you Cherno for help with this architecture!
*/

#include "Lunapch.h"
#include "LunaAPI/Core/Defines.h"

namespace Luna {

	enum class EventType
	{
		None = 0,

		WindowClose,
		WindowResize,
		WindowMoved,

		KeyPressed,
		KeyReleased,
		KeyTyped,

		MouseButtonPressed,
		MouseButtonReleased,
		MouseWheelScrolled,
		
		MouseMoved
	};

	enum EventCategory
	{
		None = 0,

		/*
			0
			1
			2
			3
			4
		*/

		EventCategoryApplication  = (1 << 0),
		EventCategoryInput        = (1 << 1),
		EventCategoryKeyboard     = (1 << 2),
		EventCategoryMouse        = (1 << 3),
		EventCategoryMouseButton  = (1 << 4)
	};


#define CHECK_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
							   virtual EventType GetEventType() const override { return GetStaticType(); }\
							   virtual const char* GetName() const override { return #type; }

#define CHECK_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }


	class Event 
	{
		friend class EventDispatcher;

	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}

		bool m_HandledEvent = false;
	};
}