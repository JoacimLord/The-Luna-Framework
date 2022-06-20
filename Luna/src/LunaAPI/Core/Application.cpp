#include "Lunapch.h"
#include "LunaAPI/Core/Application.h"
#include "LunaAPI/Renderer/Renderer.h"
#include "Input.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "imgui.h"

namespace Luna {

	Application* Application::s_Instance = nullptr;

	Application::Application(const std::string name) //by ref?
	{
		s_Instance = this;
		m_Window = std::unique_ptr<WindowInterface>(WindowInterface::Create(name));
		m_Window->SetEventCallback(DEFINE_EVENT_TYPE(OnEvent));
	
		Renderer::Init();
		m_UI.OnAttach(); //Needs to happen here, crashes if it gets called in ImGuiLayers constructor.
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
		m_UI.StartRenderFrame();
		m_UI.RenderFrame();
		m_UI.EndRenderFrame();
	}

	void  Application::ShowImGuiDemoWindow()
	{
		m_UI.showDemo = true;
	}

	float Application::GetElapsedRuntime()
	{
		return (float)glfwGetTime();
	}

	void Application::EndRendering()
	{
		m_UI.UnbindFramebuffer();
	}

	void Application::UpdateWindow()
	{
		m_Window->OnUpdate();
	}

	void Application::Clear(float r, float g, float b, float transparent)
	{
		m_UI.BindFramebuffer(r, g, b, transparent);
	}

	void Application::Clear(glm::vec4& temp)
	{
		m_UI.BindFramebuffer(temp.x, temp.y, temp.z, temp.w);
	}

	void Application::Render(std::shared_ptr<Texture>& texture, glm::mat4 transform)
	{
		Luna::Renderer::Draw(texture, transform);
	}

	void Application::Display()
	{
		EndRendering();
		DrawUI();
		UpdateWindow();
	}

	void Application::DrawUI()
	{
		UpdateGUI();
	}

	//Add deltatime later
	void Application::CheckInputForCamera()
	{
		float x = Luna::Renderer::GetCameraPosition().x;
		float y = Luna::Renderer::GetCameraPosition().y;
		float z = Luna::Renderer::GetCameraPosition().z;

		//Curr only works with arrows + left shift
		if (Luna::Input::IsKeyPressed(Luna::Key::Left) && Luna::Input::IsKeyPressed(Luna::Key::LeftShift))
		{
			x -= 0.05f;
			Luna::Renderer::SetCameraPosition( { x, y, z } );
		}
		else if (Luna::Input::IsKeyPressed(Luna::Key::Right) && Luna::Input::IsKeyPressed(Luna::Key::LeftShift))
		{
			x += 0.05f;
			Luna::Renderer::SetCameraPosition({ x, y, z });
		}
		if (Luna::Input::IsKeyPressed(Luna::Key::Down) && Luna::Input::IsKeyPressed(Luna::Key::LeftShift))
		{
			y -= 0.05f;
			Luna::Renderer::SetCameraPosition({ x, y, z });
		}
		else if (Luna::Input::IsKeyPressed(Luna::Key::Up) && Luna::Input::IsKeyPressed(Luna::Key::LeftShift))
		{
			y += 0.05f;
			Luna::Renderer::SetCameraPosition({ x, y, z });
		}
	}

	void Application::SetCameraToFollowTransform(glm::vec3 transform)
	{
		Luna::Renderer::SetCameraPosition(transform);
	}

	void Application::Render(glm::vec4 clr, glm::mat4 transform) //by refs (&) ?
	{
		Luna::Renderer::Draw(clr, transform);
	}
}