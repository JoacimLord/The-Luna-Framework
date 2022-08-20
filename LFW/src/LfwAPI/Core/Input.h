#pragma once

#include "LfwAPI/Core/KeyCodes.h"
#include "LfwAPI/Core/MouseCodes.h"

namespace LFW {

	class Input
	{
	public:
		//Returns state if key has been pressed
		static bool IsKeyPressed(Key::KeyCode key);

		//Returns state if mouse has been pressed
		static bool IsMouseButtonPressed(Mouse::MouseCode mouseCode);

		//returns mouse pos in pixels (glfw)
		static std::pair<float, float> GetMousePosition();

		//returns mouse X pos in pixels (glfw)
		static float GetMousePositionX();

		//returns mouse Y pos in pixels (glfw)
		static float GetMousePositionY();
	};
}