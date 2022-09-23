#pragma once

#include "LfwAPI/Core/Defines.h"
#include "LfwAPI/Core/Window.h" 
#include "LfwAPI/Core/WindowInterface.h" 
#include "LfwAPI/Core/DeltaTime.h"
#include "LfwAPI/Core/KeyCodes.h"

#include "LfwAPI/UI/UI.h"

#include "LfwAPI/Renderer/Framebuffer.h"

#include "LfwAPI/EventHandler/MainEventBaseClass.h"
#include "LfwAPI/EventHandler/MouseEvents/MouseButtonBaseEvent.h"
#include "LfwAPI/EventHandler/MouseEvents/MouseButtonPressed.h"
#include "LfwAPI/EventHandler/MouseEvents/MouseButtonReleased.h"
#include "LfwAPI/EventHandler/MouseEvents/MouseMove.h"
#include "LfwAPI/EventHandler/MouseEvents/MouseWheelScroll.h"

#include "LfwAPI/EventHandler/WindowEvents/WindowClose.h"
#include "LfwAPI/EventHandler/WindowEvents/WindowResize.h"
#include "LfwAPI/EventHandler/EventDispatcher/EventDispatcher.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "GLFW/glfw3.h"


namespace LFW {

	//To enable vsync in the application
	namespace VSYNC
	{
		static bool vsync;

		//Enables vsync if true, disabled if false4
		void Init(bool state);

		//Used internally to check if vsync is activated in the applications constructor
		bool IsEnabled();
	}

	//To enable 'floating' GUI panels
	namespace DebugGUI
	{
		static bool enableDebugGUI;

		//If true this enables Dear ImGui in the application.
		//If false, the application renders directly to the GLFW window instead.
		void Init(bool state);

		//Checks if the DebugGUI is enabled, used in Application.cpp at initialization and Clear()-checks
		bool IsEnabled();
	}

	//To enable dockable GUI panels
	namespace Docking
	{
		static bool enableDocking;

		//If true this enables Dear ImGui in the application.
		//If false, the application renders directly to the GLFW window instead.
		void Init(bool state);

		//Checks if the Docking is enabled, used in Application.cpp at initialization and Clear()-checks
		bool IsEnabled();
	}


	class Application
	{
	public:
		//Initializes the application with a name (title bar)
		Application(const std::string name);
		~Application() = default;

		//Initiates Dear ImGui's own demo window.
		//This needs the viewport to be set to true.
		void ShowImGuiDemoWindow();

		//Returns elapsed time since start of application
		float GetElapsedRuntime();

		//Returns DeltaTime
		DeltaTime GetDeltaTime();

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

		//Returns the mouse position converted from world space to screen points in pixels. Origin is 0,0 (center of screen).
		glm::vec2 WorldToScreenPoint();

		//Returns the mouse position converted from screen space to world point.
		//This function only returns correct values if the viewport is not initialized and uses the "original" glfw window for rendering.
		glm::vec2 ScreenToWorldPoint();

		//Sets the title of the LFW application
		void SetTitle(std::string title);

		//Sets the icon of the LFW application
		void SetIcon(std::string path);

		//Sets the default icon to the application window title bar
		void SetDefaultIcon();

		//!!DON'T USE!! Sets a custom image as the cursor
		void SetCustomCursor();

		//!!DON'T USE!! Sets the default cursor
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

		//Renders target sprite to screen (from spritesheet). 
		//Takes in the index number of the texture (0 is in the top left corner of the texture)
		void Render(Spritesheet& spritesheet, int indexPosition);

		//Renders instanced sprites(textures). Takes in amount of textures to render
		void Render(Batch& batch, int amount);

		//Function for moving the "in-game" camera. 
		//Uses DeltaTime and specified keys for controls (in order: Up, Down, Left, Right).
		void CheckInputForGameCamera(LFW::Key::KeyCode keyUp, LFW::Key::KeyCode keyDown, LFW::Key::KeyCode keyLeft, LFW::Key::KeyCode keyRight, DeltaTime dt, float speed);

		//Function for moving the "debug" camera. Currently controlled with the Arrow-keys
		void CheckInputForDebugCamera(float speed);

		//Sets the camera to follow a specific transform (attached by default to sprites)
		void SetCameraToFollowTransform(glm::vec3 transform);

		//Returns the applications viewport IF GUI is enabled
		glm::vec2 GetViewportSize();

		//Needed to define and build your own UI with ImGui (documentation can be found it Dear ImGuis repo).
		//This can only be used if the viewport is initialized and set to true.
		static void BuildUI();

	public:
		//Returns the singleton instance of the application
		inline static Application& Get() { return *s_instance; }
		WindowInterface& GetWindow() const { return *m_window; }

	private:
		//Handles application events
		void OnEvent(Event& event);
		bool OnWindowCloseEvent(WindowCloseEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);

		//Private functions for handling rendering
		void UpdateGUI();
		void EndRendering();
		void UpdateWindow();
		void DrawUI();
		void OnGUIClose();

	private:
		static Application* s_instance;
		bool m_isRunning = true;
		std::unique_ptr<WindowInterface> m_window = nullptr;
		std::unique_ptr<UI> m_ui = nullptr;
		float m_lastFrameTime = 0.0f;
	};
}