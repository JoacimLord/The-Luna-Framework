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

	class Application
	{
	public:
		Application(const std::string name);
		~Application() = default;

		//------------
		//API for the main.cpp (app dev) -> All user interaction happens from here!
		//------------

		//Initiates ImGui's own demo window
		void ShowImGuiDemoWindow();

		//Returns elapsed time since start of application
		float GetElapsedRuntime();

		//Checks if application is runnning (use in main while loop as condition)
		bool IsRunning();

		//Clears the screens background with a specified color values
		void Clear(float r, float g, float b, float transparent);

		//Clears the screens background with a pre defined color from LFW::Colors
		void Clear(glm::vec4& temp); 

		//Renders target sprite to screen
		void Render(Sprite sprite);

		//Needs to be called at the end of each frame (furthest down in while loop). Clears frame buffers and displays graphics
		void Display();

		//DISCLAIMER -> This is only called internally, don't use this function.
		void DrawUI();

		//Sets visiblity of mouse cursor
		void SetMouseCursorVisibility(bool visible);

		//Sets the title of the LFW application
		void SetTitle(std::string title);

		//Sets the icon of the LFW application
		void SetIcon(std::string path);

		//TODO: Remove dt?
		//Function for moving the camera. Currently controlled with the Arrow-keys
		void CheckInputForCamera(DeltaTime dt);

		//Sets the camera to follow a specific transform (attached by default to sprites)
		void SetCameraToFollowTransform(glm::vec3 transform);

		//Needed to define and build your own UI with ImGui (documentation can be found it it's own repo)
		static void BuildUI();

	// - DISCLAIMER! -
	//Used internally, don't use these.
	public:
		inline static Application& Get() { return *s_Instance; }
		WindowInterface& GetWindow() const { return *m_Window; }
		void OnGUIClose();

	private:
		void OnEvent(Event& event);
		bool OnWindowCloseEvent(WindowCloseEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);

		void UpdateGUI();
		void EndRendering();
		void UpdateWindow();

	private:
		static Application* s_Instance;
		bool m_IsRunning = true;
		std::unique_ptr<WindowInterface> m_Window;
		std::unique_ptr<UI> m_UI;
	};
}