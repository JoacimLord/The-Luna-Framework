#include "LFWpch.h"
#include "LunaAPI/Core/Defines.h"
#include "LunaAPI/UI/UI.h"
#include "LunaAPI/UI/ImGuiImpl.h"
#include "LunaAPI/Core/Application.h"
#include "LunaAPI/Core/Input.h"

#include <backends/imgui_impl_glfw.h> 
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>

#include <GLFW/glfw3.h>


namespace LFW {

	glm::vec2 m_ViewportSize = { 0.0f, 0.0f };

	UI::UI()
	{
		m_Framebuffer = std::make_shared<Framebuffer>();
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
		spec.Width = 1280;
		spec.Height = 720;
		SetFramebufferSpec(spec);
	}
	
	void UI::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	bool UI::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		//test
		std::cout << "Mousepress\n";
		return false;
	}

	void UI::OnEvent(Event& event) 
	{ 
		if (blockevents)
		{
			ImGuiIO& io = ImGui::GetIO();
			event.m_HandledEvent |= event.IsInCategory(EventCategoryMouse) & io.WantCaptureMouse;
			event.m_HandledEvent |= event.IsInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
			std::cout << "Blocked event from app";
		}

		EventDispatcher dispatcher(event); 
		dispatcher.Dispatch<MouseButtonPressedEvent>(DEFINE_EVENT_TYPE(UI::OnMouseButtonPressedEvent));
	}


	void UI::StartRenderFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void UI::BindFramebuffer(float r, float g, float b, float transparent)
	{
		//Wip
		if (m_ViewportSize.x != m_Framebuffer->GetFramebufferSpecification().Width || m_ViewportSize.y != m_Framebuffer->GetFramebufferSpecification().Height)
		{
			std::cout << "Resetting framebuffer!\n";
			m_Framebuffer->ResizeFramebuffer((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		}

		m_Framebuffer->Bind();
		Renderer::ClearColor(r, g, b, transparent);
		Renderer::Clear();
	}

	void UI::UnbindFramebuffer()
	{
		m_Framebuffer->Unbind();
	}

	void UI::SetFramebufferSpec(FramebufferSpecification spec)
	{
		m_Framebuffer->CreateFramebufferSpecification(spec);
		m_Framebuffer->Invalidate();
	}

	//Used in app
	void UI::RenderFrame()
	{
			static bool dockspaceOpen = true;
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
			//float minWinSizeX = style.WindowMinSize.x;

			//This sets the minimum width to 370. 
			//TODO: change to set this with a function from Application::SetMinimumPanelWidth(); Can be annyoing if they're used for UI elements (in game dev).
			//style.WindowMinSize.x = 370.0f;
			if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
			{
				ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
				ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
			}

			//style.WindowMinSize.x = minWinSizeX;


			//----------------------------------------------
			//					VIEWPORT
			//----------------------------------------------
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
			ImGui::Begin("Viewport");
			auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
			auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
			auto viewportOffset = ImGui::GetWindowPos();

			ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
			m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

			uint64_t textureID = m_Framebuffer->GetColorAttachment();
			ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });


			ImGui::End();
			ImGui::PopStyleVar();

			ImGui::End();


			//---------------------------------------------------
			//					DEMO WINDOW
			//---------------------------------------------------

			if (showDemo) { OnUIRender(); }
			LFW::Application::BuildUI();

	}


	//Dear ImGui Demo Window
	void UI::OnUIRender()
	{
		ImGui::Begin("Demo");
		ImGui::Text("Click for ImGui Demo Window");
		ImGui::Checkbox("Demo", &m_DemoGuiWindow);
		if (m_DemoGuiWindow) { ImGui::ShowDemoWindow(&m_DemoGuiWindow); }
		ImGui::End();
	}

	//Used in app
	void UI::EndRenderFrame()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

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