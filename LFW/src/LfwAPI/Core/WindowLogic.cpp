#include "LFWpch.h"
#include "LfwAPI/Core/WindowLogic.h"

#include <imgui.h>
#include <glad/glad.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>


namespace LFW {

	static bool s_GLFWInitialize = false;

	WindowLogic::WindowLogic(const Window& data)
	{
		Init(data);
	}

	WindowLogic::~WindowLogic()
	{
		//Close GLFW-window
		Shutdown();
	}

	void WindowLogic::SetWindowData(const Window& data)
	{
		m_data.title = data.title;
		m_data.width = data.width;
		m_data.height = data.height;
	}

	void WindowLogic::Init(const Window& data)
	{
		m_data.title = data.title;
		m_data.width = data.width;
		m_data.height = data.height;

		if (!s_GLFWInitialize)
		{
			int success = glfwInit();
			s_GLFWInitialize = true;
		}

		m_window = glfwCreateWindow((int)data.width, (int)data.height, m_data.title.c_str(), nullptr, nullptr);
		glfwFocusWindow(m_window);

		glfwMakeContextCurrent(m_window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		glfwSetWindowUserPointer(m_window, &m_data);
		SetVSync(true);

		//Set callbacks
		SetCallbackResize();
		SetCallbackClose();
		SetCallbackKeyboard();
		SetCallbackChars();
		SetCallbackMouseBtn();
		SetCallbackMouseScroll();
		SetCallbackCursorPos();
	}

	void WindowLogic::Shutdown()
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}

	void WindowLogic::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_window); //add this
	}


	void WindowLogic::SetVSync(bool enabled)
	{
		if (enabled) { glfwSwapInterval(1); }
		else { glfwSwapInterval(0); }
			
		m_data.vSync = enabled;
	}

	bool WindowLogic::VSyncActive() const { return m_data.vSync; }

	void WindowLogic::SetCallbackResize()
	{
		//Callback - Resize
		glfwSetWindowSizeCallback(m_window,
			[](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				data.width = width;
				data.height = height;

				WindowResizeEvent event(width, height);
				data.eventCallback(event);
			});
	}

	void WindowLogic::SetCallbackClose()
	{

		//Callback - Close
		glfwSetWindowCloseCallback(m_window,
			[](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				WindowCloseEvent event;
				data.eventCallback(event);
			});
	}

	void WindowLogic::SetCallbackKeyboard()
	{
		//Callback - Keys
		glfwSetKeyCallback(m_window,
			[](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.eventCallback(event);

					break;
				}

				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.eventCallback(event);

					break;
				}

				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.eventCallback(event);

					break;
				}
				}
			});
	}

	void WindowLogic::SetCallbackChars()
	{

		//Callback - Char
		glfwSetCharCallback(m_window,
			[](GLFWwindow* window, unsigned int keycode)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				KeyTypedEvent event(keycode);
				data.eventCallback(event);
			});
	}

	void WindowLogic::SetCallbackMouseBtn()
	{

		//Callback - MouseButton
		glfwSetMouseButtonCallback(m_window,
			[](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.eventCallback(event);

					break;
				}

				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.eventCallback(event);

					break;
				}
				}
			});
	}

	void WindowLogic::SetCallbackMouseScroll()
	{

		//Callback - MouseScroll
		glfwSetScrollCallback(m_window,
			[](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseWheelScrolledEvent event((float)xOffset, (float)yOffset);
				data.eventCallback(event);
			});
	}
	void WindowLogic::SetCallbackCursorPos()
	{
		//Callback - CursorPos
		glfwSetCursorPosCallback(m_window,
			[](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xPos, (float)yPos);
				data.eventCallback(event);
			});
	}

	WindowInterface* WindowInterface::Create(const Window& props)
	{
		return new WindowLogic(props); //This pushes the heap-memory into a unique_ptr, shouldn't be any problems.
	}
}