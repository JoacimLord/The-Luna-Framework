#pragma once

#include "LunaAPI/Core/KeyCodes.h"
#include "LunaAPI/Core/MouseCodes.h"

namespace LFW {

	class Input
	{
	public:
		static bool IsKeyPressed(Key::KeyCode key);
		static bool IsMouseButtonPressed(Mouse::MouseCode mouseCode);
		static std::pair<float, float> GetMousePosition();

		static float GetMousePositionX();
		static float GetMousePositionY();
	};
}