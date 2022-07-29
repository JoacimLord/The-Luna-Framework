#include "LFWpch.h"
#include "LunaAPI/Core/Application.h"
#include "LunaAPI/Renderer/Renderer.h"
#include "Input.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "imgui.h"

namespace LFW {

	void Viewport::Init(bool state)
	{
		m_EnableViewport = state;
	}
	bool Viewport::IsEnabled()
	{
		return m_EnableViewport;
	}

	Application* Application::s_Instance = nullptr;

	Application::Application(const std::string name) //by ref?
	{
		if (Viewport::IsEnabled()) std::cout << "Viewport enabled\n";
		if (!Viewport::IsEnabled()) std::cout << "Viewport not enabled\n";

		s_Instance = this;
		m_Window = std::unique_ptr<WindowInterface>(WindowInterface::Create(name));
		m_Window->SetEventCallback(DEFINE_EVENT_TYPE(OnEvent));
	
		Renderer::Init();

		if (Viewport::IsEnabled())
		{
			m_UI = std::make_unique<UI>();
			m_UI->OnAttach(); //Needs to happen here, crashes if it gets called in ImGuiLayers constructor.
		}
		//m_UI = std::make_unique<UI>();
		//m_UI->OnAttach(); //Needs to happen here, crashes if it gets called in ImGuiLayers constructor.
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(DEFINE_EVENT_TYPE(Application::OnWindowCloseEvent));
		dispatcher.Dispatch<WindowResizeEvent>(DEFINE_EVENT_TYPE(Application::OnWindowResizeEvent));
	}
	
	bool Application::OnWindowCloseEvent(WindowCloseEvent& e)
	{
		m_IsRunning = false;
		return true;
	}

	bool Application::OnWindowResizeEvent(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			std::cout << "Minimized\n";
		}

		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		return false;
	}

	void Application::OnGUIClose()
	{
		m_IsRunning = false;
	}

	bool Application::IsRunning()
	{
		return m_IsRunning;
	}

	void Application::UpdateGUI()
	{
		m_UI->StartRenderFrame();
		m_UI->RenderFrame();
		m_UI->EndRenderFrame();
	}

	void  Application::ShowImGuiDemoWindow()
	{
		m_UI->showDemo = true;
	}

	float Application::GetElapsedRuntime()
	{
		return (float)glfwGetTime();
	}

	void Application::EndRendering()
	{
		m_UI->UnbindFramebuffer();
	}

	void Application::UpdateWindow()
	{
		m_Window->OnUpdate();
	}



	// COPY THESE!!!!

	//This function also needs the branching of enabled viewport if the user chooses to use color values and not predefined. Remove???
	void Application::Clear(float r, float g, float b, float transparent)
	{
		if (Viewport::IsEnabled())
		{
			m_UI->BindFramebuffer(r, g, b, transparent);
		}
		//Added from the BindFB func if m_UI is nullptr
		else if (!Viewport::IsEnabled())
		{
			Renderer::ClearColor(r, g, b, transparent);
			Renderer::Clear();
		}
	}

	void Application::Clear(glm::vec4& temp)
	{
		//Original function
		if (Viewport::IsEnabled())
		{
			m_UI->BindFramebuffer(temp.x, temp.y, temp.z, temp.w);
		}
		//Added from the BindFB func if m_UI is nullptr
		else if (!Viewport::IsEnabled())
		{
			Renderer::ClearColor(temp.x, temp.y, temp.z, temp.w);
			Renderer::Clear();
		}
	}

	//This works, copy over this also!
	void Application::Clear()
	{
		if (Viewport::IsEnabled())
		{
			m_UI->BindFramebuffer(0, 0, 0, 1);
		}
		else if (!Viewport::IsEnabled())
		{
			Renderer::ClearColor(0, 0, 0, 1);
			Renderer::Clear();
		}
	}

	void Application::Render(Sprite& sprite)
	{
		LFW::Renderer::Draw(sprite);
	}


	void Application::Display()
	{
		//If enabled
		if (Viewport::IsEnabled())
		{
			EndRendering();
			DrawUI();
			UpdateWindow();
		}
		//If not enabled
		else if (!Viewport::IsEnabled())
		{
			UpdateWindow();
		}

		//EndRendering();
		//DrawUI();
		//UpdateWindow();
	}


	void Application::DrawUI()
	{
		UpdateGUI();
	}

	void Application::SetMouseCursorVisibility(bool visible)
	{
		GLFWwindow* window = (GLFWwindow*)GetWindow().GetOriginalWindow();
		if (visible) glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		if (!visible) glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	void Application::SetTitle(std::string title)
	{

		GLFWwindow* window = (GLFWwindow*)GetWindow().GetOriginalWindow();
		glfwSetWindowTitle(window, title.c_str());
	}

	void Application::SetIcon(std::string path)
	{
		//TODO: Destroy previous icon

		GLFWwindow* window = (GLFWwindow*)GetWindow().GetOriginalWindow();
		GLFWimage image[1];
		image[0].pixels = stbi_load(path.c_str(), &image[0].width, &image[0].height, 0, 4);
		glfwSetWindowIcon(window, 1, image);
		stbi_image_free(image[0].pixels);
	}


	void Application::CheckInputForCamera(DeltaTime dt)
	{
		float x = LFW::Renderer::GetCameraPosition().x;
		float y = LFW::Renderer::GetCameraPosition().y;
		float z = LFW::Renderer::GetCameraPosition().z;

		//Curr only works with arrows + left shift
		if (LFW::Input::IsKeyPressed(LFW::Key::Left))
		{
			x -= 0.05f * dt;
			LFW::Renderer::SetCameraPosition( { x, y, z } );
		}
		else if (LFW::Input::IsKeyPressed(LFW::Key::Right))
		{
			x += 0.05f * dt;
			LFW::Renderer::SetCameraPosition({ x, y, z });
		}
		if (LFW::Input::IsKeyPressed(LFW::Key::Down))
		{
			y -= 0.05f * dt;
			LFW::Renderer::SetCameraPosition({ x, y, z });
		}
		else if (LFW::Input::IsKeyPressed(LFW::Key::Up))
		{
			y += 0.05f * dt;
			LFW::Renderer::SetCameraPosition({ x, y, z });
		}
	}

	void Application::SetCameraToFollowTransform(glm::vec3 transform)
	{
		LFW::Renderer::SetCameraPosition(transform);
	}
}