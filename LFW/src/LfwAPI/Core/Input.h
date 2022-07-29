#pragma once

#include "LfwAPI/Core/KeyCodes.h"
#include "LfwAPI/Core/MouseCodes.h"

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