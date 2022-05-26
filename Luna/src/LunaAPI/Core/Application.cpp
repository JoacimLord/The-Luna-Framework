#include "Lunapch.h"
#include "LunaAPI/Core/Application.h"
#include "LunaAPI/Renderer/Renderer.h"
#include "Input.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "imgui.h"

namespace Luna {

	Application* Application::s_Instance = nullptr;

	Application::Application(const std::string name)
	{
		s_Instance = this;
		m_Window = std::unique_ptr<WindowInterface>(WindowInterface::Create(name));
		m_Window->SetEventCallback(DEFINE_EVENT_TYPE(OnEvent));
	
		Renderer::Init();
		m_ImGuiLayer.OnAttach(); //Needs to happen here, crashes if it gets called in ImGuiLayers constructor.
	}

	Application::~Application()
	{
		//Do nothing
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(DEFINE_EVENT_TYPE(Application::OnWindowCloseEvent));
		dispatcher.Dispatch<WindowResizeEvent>(DEFINE_EVENT_TYPE(Application::OnWindowResizeEvent));


		//NEW!!!!!!
		//for (auto it = m_Layerstack.end(); it != m_Layerstack.begin(); )
		//{
		//	(*--it)->OnEvent(e);
		//	if (e.Handled)
		//		break;
		//}

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
		m_ImGuiLayer.StartRenderFrame();
		m_ImGuiLayer.RenderFrame();
		m_ImGuiLayer.EndRenderFrame();
	}

	void  Application::ShowImGuiDemoWindow()
	{
		m_ImGuiLayer.showDemo = true;
	}


	float Application::GetElapsedRuntime()
	{
		return (float)glfwGetTime();
	}

	void Application::EndRendering()
	{
		m_ImGuiLayer.UnbindFramebuffer();
	}

	void Application::UpdateWindow()
	{
		UpdateGUI(); //Updates ImGUI, abstracted away in this function call. Goes before the window-update.
		m_Window->OnUpdate();
	}

	void Application::Clear(float r, float g, float b, float transparent)
	{

		m_ImGuiLayer.BindFramebuffer(r, g, b, transparent);
	}


	void Application::Clear(glm::vec4& temp)
	{
		m_ImGuiLayer.BindFramebuffer(temp.x, temp.y, temp.z, temp.w);
	}

	void Application::Render(std::shared_ptr<Texture>& texture, glm::mat4 transform)
	{
		Luna::Renderer::Draw(texture, transform);
	}

	void Application::Display()
	{
		EndRendering();
		DrawUI();
	}

	void Application::DrawUI()
	{
		UpdateGUI();
	}

	void Application::Update()
	{
		UpdateWindow();
	}
}