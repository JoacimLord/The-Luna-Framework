#pragma once

#include <memory>

#include "LunaAPI/Core/Defines.h"
#include "LunaAPI/Event/Event.h"

namespace Luna {

	struct Window
	{
		std::string Title;
		uint32_t Width;  //uint32_t
		uint32_t Height; //uint32_t

		Window(const std::string& title = "Luna Engine",
			uint32_t width = 1280,
			uint32_t height = 720)
			: Title(title), Width(width), Height(height)
		{
		}
	};
}