#pragma once

#include "Lunapch.h"

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


namespace Luna {

	class Application
	{
	public:
		Application(const std::string name);
		virtual ~Application();

		//API for the main.cpp (app dev)
		void ShowImGuiDemoWindow();
		float GetElapsedRuntime();
		bool IsRunning();
		void Clear(float r, float g, float b, float transparent); //Step 1
		void Clear(glm::vec4& temp); //To enable passing in a vec4

		void Render(std::shared_ptr<Texture>& texture, glm::mat4 transform); //Step 2
		void Display(); //Step 3
		void DrawUI(); //Step 4


		//Add deltatime later
		void CheckInputForCamera();
		//RenderShaderColor
		void RenderShaderColor(glm::vec4 clr, glm::mat4 transform);

		static void BuildUI(); //Outside of class in its own namespace?



	// - DISCLAIMER! -
	//Used internally, use on own risk. Change to private later.
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

	public:
		UI m_UI;

	private:
		static Application* s_Instance;
		bool m_IsRunning = true;
		//float m_LastFrameTime = 0.0f;
		std::unique_ptr<WindowInterface> m_Window; //Window
		//unsigned int m_FrameBuffer;
	};
}