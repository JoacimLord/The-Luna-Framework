#include "LFWpch.h"
#include "LunaAPI/Core/WindowLogic.h"

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
		m_Data.Title = data.Title;
		m_Data.Width = data.Width;
		m_Data.Height = data.Height;
	}

	void WindowLogic::Init(const Window& data)
	{
		m_Data.Title = data.Title;
		m_Data.Width = data.Width;
		m_Data.Height = data.Height;

		if (!s_GLFWInitialize)
		{
			int success = glfwInit();
			s_GLFWInitialize = true;
		}

		m_Window = glfwCreateWindow((int)data.Width, (int)data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwFocusWindow(m_Window);

		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		glfwSetWindowUserPointer(m_Window, &m_Data);
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
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void WindowLogic::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window); //add this
	}


	void WindowLogic::SetVSync(bool enabled)
	{
		if (enabled) { glfwSwapInterval(1); }
		else { glfwSwapInterval(0); }
			
		m_Data.VSync = enabled;
	}

	bool WindowLogic::VSyncActive() const { return m_Data.VSync; }

	void WindowLogic::SetCallbackResize()
	{
		//Callback - Resize
		glfwSetWindowSizeCallback(m_Window,
			[](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				data.Width = width;
				data.Height = height;

				WindowResizeEvent event(width, height);
				data.EventCallback(event);
			});
	}

	void WindowLogic::SetCallbackClose()
	{

		//Callback - Close
		glfwSetWindowCloseCallback(m_Window,
			[](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				WindowCloseEvent event;
				data.EventCallback(event);
			});
	}

	void WindowLogic::SetCallbackKeyboard()
	{
		//Callback - Keys
		glfwSetKeyCallback(m_Window,
			[](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);

					break;
				}

				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);

					break;
				}

				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);

					break;
				}
				}
			});
	}

	void WindowLogic::SetCallbackChars()
	{

		//Callback - Char
		glfwSetCharCallback(m_Window,
			[](GLFWwindow* window, unsigned int keycode)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				KeyTypedEvent event(keycode);
				data.EventCallback(event);
			});
	}

	void WindowLogic::SetCallbackMouseBtn()
	{

		//Callback - MouseButton
		glfwSetMouseButtonCallback(m_Window,
			[](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);

					break;
				}

				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);

					break;
				}
				}
			});
	}

	void WindowLogic::SetCallbackMouseScroll()
	{

		//Callback - MouseScroll
		glfwSetScrollCallback(m_Window,
			[](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseWheelScrolledEvent event((float)xOffset, (float)yOffset);
				data.EventCallback(event);
			});
	}
	void WindowLogic::SetCallbackCursorPos()
	{
		//Callback - CursorPos
		glfwSetCursorPosCallback(m_Window,
			[](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xPos, (float)yPos);
				data.EventCallback(event);
			});
	}

	WindowInterface* WindowInterface::Create(const Window& props)
	{
		return new WindowLogic(props); //This pushes the heap-memory into a unique_ptr, shouldn't be any problems.
	}
}