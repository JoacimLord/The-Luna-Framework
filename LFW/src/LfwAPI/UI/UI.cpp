#include "LFWpch.h"
#include "LfwAPI/Core/Defines.h"
#include "LfwAPI/UI/UI.h"
#include "LfwAPI/UI/ImGuiImpl.h"
#include "LfwAPI/Core/Application.h"
#include "LfwAPI/Core/Input.h"
#include "LfwAPI/Camera/OrthographicCamera.h"
#include "LfwAPI/Renderer/Renderer.h"

#include <backends/imgui_impl_glfw.h> 
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>

#include <GLFW/glfw3.h>


namespace LFW {

	UI::UI()
	{
		m_framebuffer = std::make_shared<Framebuffer>();
	}

	UI::~UI()
	{
		OnDetach();
	}
	
	void UI::OnAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows


		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetOriginalWindow());

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");

		LFW::FramebufferSpecification spec;
		spec.width = 1280;
		spec.height = 720;
		SetFramebufferSpec(spec);
	}
	
	void UI::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void UI::OnEvent(Event& event) 
	{ 
		//if (blockevents)
		//{
		//	ImGuiIO& io = ImGui::GetIO();
		//	event.m_HandledEvent |= event.IsInCategory(EventCategoryMouse) & io.WantCaptureMouse;
		//	event.m_HandledEvent |= event.IsInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
		//	std::cout << "Blocked event from app";
		//}
		//
		//dispatcher.Dispatch<MouseButtonPressedEvent>(DEFINE_EVENT_TYPE(UI::OnMouseButtonPressedEvent));
	}

	void UI::StartRenderFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void UI::BindFramebuffer(float r, float g, float b, float transparent)
	{
		//----------------------------------------------
		// UN-COMMENT THIS CODE TO ENABLE DOCKING
		//----------------------------------------------
		
		if (Docking::IsEnabled())
		{
			if (viewportSize.x > 0.0f && viewportSize.y > 0.0f && m_framebuffer->GetFramebufferSpecification().width != viewportSize.x || m_framebuffer->GetFramebufferSpecification().height != viewportSize.y)
			{
				std::cout << "Resetting framebuffer!\n";
				m_framebuffer->ResizeFramebuffer((uint32_t)viewportSize.x, (uint32_t)viewportSize.y);

				//Renderer::GetCamera().SetViewportSize(m_ViewportSize.x, m_ViewportSize.y);
				Renderer::GetCamera().OnResize(viewportSize.x, viewportSize.y);
			}

			m_framebuffer->Bind();
			Renderer::ClearColor(r, g, b, transparent);
			Renderer::Clear();
		}
	}

	void UI::UnbindFramebuffer()
	{
		m_framebuffer->Unbind();
	}

	void UI::SetFramebufferSpec(FramebufferSpecification spec)
	{
		m_framebuffer->CreateFramebufferSpecification(spec);
		m_framebuffer->Invalidate();
	}

	//Used in app
	void UI::RenderFrame()
	{
		if (Docking::IsEnabled())
		{
			static bool dockspaceOpen = false;
			static bool opt_fullscreen_persistant = true;
			bool opt_fullscreen = opt_fullscreen_persistant;
			static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

			ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
			if (opt_fullscreen)
			{
				ImGuiViewport* viewport = ImGui::GetMainViewport();
				ImGui::SetNextWindowPos(viewport->Pos);
				ImGui::SetNextWindowSize(viewport->Size);
				ImGui::SetNextWindowViewport(viewport->ID);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
				window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
				window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
			}

			if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
				window_flags |= ImGuiWindowFlags_NoBackground;


			//----------------------------------------------
			//			MAIN WINDOW (DOCKSPACE)
			//----------------------------------------------
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));


			//==============================================
			//Dockspace
			//==============================================
			ImGui::Begin("LFW Dockspace", &dockspaceOpen, window_flags);

			ImGui::PopStyleVar();

			if (opt_fullscreen)
				ImGui::PopStyleVar(2);

			// DockSpace
			ImGuiIO& io = ImGui::GetIO();
			ImGuiStyle& style = ImGui::GetStyle();

			if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
			{
				ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
				ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
			}

			//----------------------------------------------
			//					VIEWPORT
			//----------------------------------------------
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
			ImGui::Begin("Viewport");
			auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
			auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
			//auto viewportOffset = ImGui::GetWindowPos();
			//ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

			ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
			viewportSize = { viewportPanelSize.x, viewportPanelSize.y };

			uint64_t textureID = m_framebuffer->GetColorAttachment();
			ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ viewportSize.x, viewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

			ImGui::End();
			ImGui::PopStyleVar();
			ImGui::End();
		}

		//---------------------------------------------------
		//					DEMO WINDOW && GUI
		//---------------------------------------------------
		if (showDemo) { OnUIRender(); }
		LFW::Application::BuildUI();
	}


	//Dear ImGui Demo Window
	void UI::OnUIRender()
	{
		ImGui::Begin("Demo");
		ImGui::Text("Click for ImGui Demo Window");
		ImGui::Checkbox("Demo", &m_demoGuiWindow);
		if (m_demoGuiWindow) { ImGui::ShowDemoWindow(&m_demoGuiWindow); }
		ImGui::End();
	}

	//Used in app
	void UI::EndRenderFrame()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());
		//io.DisplaySize = ImVec2(m_ViewportSize.x, m_ViewportSize.y);

		// Rendering
		ImGui::Render();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}
}