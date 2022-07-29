#include "LFWpch.h"
#include "LfwAPI/Core/Input.h"
#include "LfwAPI/Core/Application.h"
#include <GLFW/glfw3.h>

namespace LFW {

	bool Input::IsKeyPressed(Key::KeyCode key)
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetOriginalWindow());
		auto state = glfwGetKey(window, static_cast<int32_t>(key));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonPressed(Mouse::MouseCode mouseCode)
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetOriginalWindow());
		auto state = glfwGetMouseButton(window, static_cast<int32_t>(mouseCode));
		return state == GLFW_PRESS;
	}

	std::pair<float, float> Input::GetMousePosition()
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetOriginalWindow());
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);
		return { (float)xPos , (float)yPos };
	}


	float Input::GetMousePositionX()
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetOriginalWindow());
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);
		return (float)xPos;
	}

	float Input::GetMousePositionY()
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetOriginalWindow());
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);
		return (float)yPos;
	}
}
