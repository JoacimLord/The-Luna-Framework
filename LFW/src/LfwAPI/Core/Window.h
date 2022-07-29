#pragma once

#include <memory>

#include "LfwAPI/Core/Defines.h"

//MOUSE
#include "LfwAPI/EventHandler/MouseEvents/MouseButtonBaseEvent.h"
#include "LfwAPI/EventHandler/MouseEvents/MouseButtonPressed.h"
#include "LfwAPI/EventHandler/MouseEvents/MouseButtonReleased.h"
#include "LfwAPI/EventHandler/MouseEvents/MouseMove.h"
#include "LfwAPI/EventHandler/MouseEvents/MouseWheelScroll.h"

//WINDOW
#include "LfwAPI/EventHandler/WindowEvents/WindowClose.h"
#include "LfwAPI/EventHandler/WindowEvents/WindowResize.h"

#include "LfwAPI/EventHandler/EventDispatcher/EventDispatcher.h"

namespace LFW {

	struct Window
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		Window(const std::string& title = "LFW App",
			uint32_t width = 1280,
			uint32_t height = 720)
			: Title(title), Width(width), Height(height)
		{
		}
	};
}