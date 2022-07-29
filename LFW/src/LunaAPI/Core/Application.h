#pragma once

#include "LunaAPI/Core/Defines.h"
#include "LunaAPI/Core/Window.h" 
#include "LunaAPI/Core/WindowInterface.h" 
#include "LunaAPI/EventHandler/MainEventBaseClass.h"
#include "LunaAPI/UI/UI.h"
#include "LunaAPI/Core/DeltaTime.h"
#include "LunaAPI/Renderer/Framebuffer.h"

//MOUSE
#include "LunaAPI/EventHandler/MouseEvents/MouseButtonBaseEvent.h"
#include "LunaAPI/EventHandler/MouseEvents/MouseButtonPressed.h"
#include "LunaAPI/EventHandler/MouseEvents/MouseButtonReleased.h"
#include "LunaAPI/EventHandler/MouseEvents/MouseMove.h"
#include "LunaAPI/EventHandler/MouseEvents/MouseWheelScroll.h"

//WINDOW
#include "LunaAPI/EventHandler/WindowEvents/WindowClose.h"
#include "LunaAPI/EventHandler/WindowEvents/WindowResize.h"
#include "LunaAPI/EventHandler/EventDispatcher/EventDispatcher.h"

#include "GLFW/glfw3.h"


namespace LFW {

	//TODO: Thinking about moving this to be initialized in the application constructor instead
	//Sets a bool for the Dear ImGui Viewport
	namespace Viewport
	{
		static bool m_EnableViewport;

		//If true this enables Dear ImGui in the application.
		//If false, the application renders to the GLFW window instead.
		void Init(bool state);

		//Checks if the viewport is enabled, used in Application.cpp at initialization and Clear()-checks.
		bool IsEnabled();
	}


	class Application
	{
	public:
		Application(const std::string name);
		~Application() = default;

		//------------
		//API for the main.cpp (app dev) -> All user interaction happens from here!
		//------------

		//Initiates Dear ImGui's own demo window.
		//This needs the viewport to be set to true.
		void ShowImGuiDemoWindow();

		//Returns elapsed time since start of application
		float GetElapsedRuntime();

		//Checks if application is runnning (use in main while loop as condition)
		bool IsRunning();

		//Clears the screens background with a specified color values
		void Clear(float r, float g, float b, float transparent);

		//Clears the screens background with a pre defined color from LFW::Colors
		void Clear(glm::vec4& temp); 

		//Clears the screen with the default color (black)
		void Clear();

		//Needs to be called at the end of each frame (furthest down in while loop). Clears frame buffers and displays graphics
		void Display();

		/////////////////////////////////////////////
		/* Window (GLFW) functionality */
		/////////////////////////////////////////////

		//Sets the title of the LFW application
		void SetTitle(std::string title);

		//Sets the icon of the LFW application
		void SetIcon(std::string path);
		//Sets the default icon to the application window title bar.
		void SetDefaultIcon();

		//Sets a custom image as the cursor. Wip, not done for usage.
		void SetCustomCursor();

		//Sets the default cursor. Wip, not done for usage.
		void SetDefaultCursor();

		//Sets the application window minimum and maximum size (minimum Width, minimum Height, maximum Width, maximum Height)
		void SetWindowConstraint(float minWidth, float minHeight, float maxWidth, float maxHeight);

		//Sets the application window minimum size. Can't be used together with SetWindowMaxSize(), instead use SetWindowConstraint to set both constraints
		void SetWindowMinSize(float minWidth, float minHeight);

		//Sets the application window maximum size. Can't be used together with SetWindowMaxSize(), instead use SetWindowConstraint to set both constraints
		void SetWindowMaxSize(float maxWidth, float maxHeight);

		//Sets visiblity of mouse cursor
		void SetMouseCursorVisibility(bool visible);

		//Renders target sprite to screen
		void Render(Sprite& sprite);

		//TODO: Remove dt?
		//Function for moving the camera. Currently controlled with the Arrow-keys
		void CheckInputForCamera(DeltaTime dt);

		//Sets the camera to follow a specific transform (attached by default to sprites)
		void SetCameraToFollowTransform(glm::vec3 transform);

		//Needed to define and build your own UI with ImGui (documentation can be found it Dear ImGuis repo).
		//This can only be used if the viewport is initialized and set to true.
		static void BuildUI();

	public:
		inline static Application& Get() { return *s_Instance; }
		WindowInterface& GetWindow() const { return *m_Window; }

	private:
		void OnEvent(Event& event);
		bool OnWindowCloseEvent(WindowCloseEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);

		void UpdateGUI();
		void EndRendering();
		void UpdateWindow();
		void DrawUI();
		void OnGUIClose();

	private:
		static Application* s_Instance;
		bool m_IsRunning = true;
		std::unique_ptr<WindowInterface> m_Window = nullptr;
		std::unique_ptr<UI> m_UI = nullptr;
	};
}