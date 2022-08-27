#include "LFWpch.h"
#include "LfwAPI/Core/Application.h"
#include "LfwAPI/Renderer/Renderer.h"
#include "Input.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "imgui.h"

namespace LFW {

	void DebugGUI::Init(bool state)
	{
		enableDebugGUI = state;
	}
	bool DebugGUI::IsEnabled()
	{
		return enableDebugGUI;
	}

	void Docking::Init(bool state)
	{
		m_enableDocking = state;
	}
	bool Docking::IsEnabled()
	{
		return m_enableDocking;
	}

	Application* Application::s_instance = nullptr;

	Application::Application(const std::string name) //by ref?
	{
		if (!DebugGUI::IsEnabled() && !Docking::IsEnabled())
		{
			
		}
		if (DebugGUI::IsEnabled()) std::cout << "DebugGUI enabled\n";
		if (!DebugGUI::IsEnabled()) std::cout << "DebugGUI not enabled\n";

		if (Docking::IsEnabled()) std::cout << "Docking enabled\n";
		if (!Docking::IsEnabled()) std::cout << "Docking not enabled\n";


		s_instance = this;
		m_window = std::unique_ptr<WindowInterface>(WindowInterface::Create(name));
		m_window->SetEventCallback(DEFINE_EVENT_TYPE(OnEvent));
	
		Renderer::Init();

		if (DebugGUI::IsEnabled())
		{
			m_ui = std::make_unique<UI>();
			m_ui->OnAttach(); //Needs to happen here, crashes if it gets called in ImGuiLayers constructor.
			//Renderer::GetCamera().SetViewportSize(m_UI->m_ViewportSize.x, m_UI->m_ViewportSize.y);
		}
		if (Docking::IsEnabled())
		{
			m_ui = std::make_unique<UI>();
			m_ui->OnAttach(); //Needs to happen here, crashes if it gets called in ImGuiLayers constructor.
			//Renderer::GetCamera().SetViewportSize(m_UI->m_ViewportSize.x, m_UI->m_ViewportSize.y);
		}
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(DEFINE_EVENT_TYPE(Application::OnWindowCloseEvent));
		dispatcher.Dispatch<WindowResizeEvent>(DEFINE_EVENT_TYPE(Application::OnWindowResizeEvent));
	}
	
	bool Application::OnWindowCloseEvent(WindowCloseEvent& e)
	{
		m_isRunning = false;
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
		m_isRunning = false;
	}

	bool Application::IsRunning()
	{
		return m_isRunning;
	}

	void Application::UpdateGUI()
	{
		m_ui->StartRenderFrame();
		m_ui->RenderFrame();
		m_ui->EndRenderFrame();
	}

	void  Application::ShowImGuiDemoWindow()
	{
		m_ui->showDemo = true;
	}

	float Application::GetElapsedRuntime()
	{
		return (float)glfwGetTime();
	}

	void Application::EndRendering()
	{
		m_ui->UnbindFramebuffer();
	}

	void Application::UpdateWindow()
	{
		m_window->OnUpdate();
	}

	void Application::Clear(float r, float g, float b, float transparent)
	{
		if (Docking::IsEnabled())
		{
			m_ui->BindFramebuffer(r, g, b, transparent);
		}
		else
		{
			Renderer::ClearColor(r, g, b, transparent);
			Renderer::Clear();
		}
	}

	void Application::Clear(glm::vec4& temp)
	{
		if (Docking::IsEnabled())
		{
			m_ui->BindFramebuffer(temp.x, temp.y, temp.z, temp.w);
		}
		else 
		{
			Renderer::ClearColor(temp.x, temp.y, temp.z, temp.w);
			Renderer::Clear();
		}
	}

	void Application::Clear()
	{
		if (Docking::IsEnabled())
		{
			m_ui->BindFramebuffer(0, 0, 0, 1);
		}
		else
		{
			Renderer::ClearColor(0, 0, 0, 1);
			Renderer::Clear();
		}
	}

	void Application::Display()
	{
		//UpdateWindow();
		if (DebugGUI::IsEnabled())
		{
			EndRendering();
			DrawUI();
			UpdateWindow();
		}
		else if (Docking::IsEnabled())
		{
			EndRendering();
			DrawUI();
			UpdateWindow();
		}
		else
		{
			UpdateWindow();
		}
	}

	glm::vec2 Application::WorldToScreenPoint()
	{
		float mouseX = Input::GetMousePositionX();
		float mouseY = Input::GetMousePositionY();
		glm::vec2 mouseCoords = glm::vec2(mouseX, mouseY);
		return Renderer::GetCamera().WorldToScreenPoint(mouseCoords, (float)m_window->GetWidth(), (float)m_window->GetHeight());
	}

	glm::vec2 Application::ScreenToWorldPoint()
	{
		return Renderer::GetCamera().ScreenToWorldPoint(m_window->GetWidth(), m_window->GetHeight());
	}


	void Application::SetTitle(std::string title)
	{
		GLFWwindow* window = (GLFWwindow*)GetWindow().GetOriginalWindow();
		glfwSetWindowTitle(window, title.c_str());
	}

	void Application::SetIcon(std::string path)
	{
		//TODO: Destroy previous icon before initalizing a new one
		GLFWwindow* window = (GLFWwindow*)GetWindow().GetOriginalWindow();
		GLFWimage image[1];
		image[0].pixels = stbi_load(path.c_str(), &image[0].width, &image[0].height, 0, 4);
		glfwSetWindowIcon(window, 1, image);
		stbi_image_free(image[0].pixels);
	}

	void Application::SetDefaultIcon()
	{
		GLFWwindow* window = (GLFWwindow*)GetWindow().GetOriginalWindow();
		glfwSetWindowIcon(window, 0, NULL);
	}

	void Application::SetCustomCursor()
	{
		//TODO: add support for a custom cursor
	}

	void Application::SetDefaultCursor()
	{
		//glfwDestroyCursor();
		GLFWwindow* window = (GLFWwindow*)GetWindow().GetOriginalWindow();
		glfwSetCursor(window, NULL);
	}

	void Application::SetWindowConstraint(float minWidth, float minHeight, float maxWidth, float maxHeight)
	{
		GLFWwindow* window = (GLFWwindow*)GetWindow().GetOriginalWindow();
		glfwSetWindowSizeLimits(window, minWidth, minHeight, maxWidth, maxHeight);
	}

	void Application::SetWindowMinSize(float minWidth, float minHeight)
	{
		GLFWwindow* window = (GLFWwindow*)GetWindow().GetOriginalWindow();
		glfwSetWindowSizeLimits(window, minWidth, minHeight, GLFW_DONT_CARE, GLFW_DONT_CARE);
	}

	void Application::SetWindowMaxSize(float maxWidth, float maxHeight)
	{
		GLFWwindow* window = (GLFWwindow*)GetWindow().GetOriginalWindow();
		glfwSetWindowSizeLimits(window, GLFW_DONT_CARE, GLFW_DONT_CARE, maxWidth, maxHeight);

	}
	void Application::SetMouseCursorVisibility(bool visible)
	{
		GLFWwindow* window = (GLFWwindow*)GetWindow().GetOriginalWindow();
		if (visible) glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		if (!visible) glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	void Application::Render(Sprite& sprite)
	{
		LFW::Renderer::Draw(sprite);
	}

	void Application::Render(Spritesheet& spritesheet)
	{
		LFW::Renderer::DrawFromSpritesheet(spritesheet);
	}
	
	void Application::CheckInputForGameCamera(LFW::Key::KeyCode keyUp, LFW::Key::KeyCode keyDown, LFW::Key::KeyCode keyLeft, LFW::Key::KeyCode keyRight, DeltaTime dt, float speed)
	{
		float x = Renderer::GetCameraPosition().x;
		float y = Renderer::GetCameraPosition().y;
		float z = Renderer::GetCameraPosition().z;

		if (LFW::Input::IsKeyPressed(keyLeft))
		{
			x -= speed * dt;
			Renderer::SetCameraPosition( { x, y, z } );
		}
		else if (LFW::Input::IsKeyPressed(keyRight))
		{
			x += speed * dt;
			Renderer::SetCameraPosition({ x, y, z });
		}
		if (LFW::Input::IsKeyPressed(keyDown))
		{
			y -= speed * dt;
			Renderer::SetCameraPosition({ x, y, z });
		}
		else if (LFW::Input::IsKeyPressed(keyUp))
		{
			y += speed * dt;
			Renderer::SetCameraPosition({ x, y, z });
		}
	}

	void Application::CheckInputForDebugCamera(float speed)
	{
		float x = Renderer::GetCameraPosition().x;
		float y = Renderer::GetCameraPosition().y;
		float z = Renderer::GetCameraPosition().z;

		if (Input::IsKeyPressed(LFW::Key::Left))
		{
			x -= speed;
			LFW::Renderer::SetCameraPosition({ x, y, z });
		}
		else if (Input::IsKeyPressed(LFW::Key::Right))
		{
			x += speed;
			LFW::Renderer::SetCameraPosition({ x, y, z });
		}
		if (Input::IsKeyPressed(LFW::Key::Down))
		{
			y -= speed;
			Renderer::SetCameraPosition({ x, y, z });
		}
		else if (LFW::Input::IsKeyPressed(LFW::Key::Up))
		{
			y += speed;
			Renderer::SetCameraPosition({ x, y, z });
		}
	}

	void Application::SetCameraToFollowTransform(glm::vec3 transform)
	{
		Renderer::SetCameraPosition(transform);
	}

	glm::vec2 Application::GetViewportSize()
	{
		if (!DebugGUI::IsEnabled())
		{
			std::cout << "Viewport not enabled. Returning 0\n";
			return glm::vec2(0,0);
		}
		glm::vec2 viewportSize = glm::vec2(m_ui->viewportSize.x, m_ui->viewportSize.y);
		return viewportSize;
	}

	void Application::DrawUI()
	{
		UpdateGUI();
	}
}