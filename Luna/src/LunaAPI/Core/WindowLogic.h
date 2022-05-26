#pragma once


//Moved from the cpp file
#include "LunaAPI/Core/Window.h"
#include "LunaAPI/Core/WindowInterface.h"
#include "LunaAPI/EventHandler/MainEventBaseClass.h"
#include "LunaAPI/EventHandler/KeyEvents/KeyButtonBaseEvent.h"
#include "LunaAPI/EventHandler/KeyEvents/KeyPressed.h"
#include "LunaAPI/EventHandler/KeyEvents/KeyReleased.h"
#include "LunaAPI/EventHandler/KeyEvents/KeyTyped.h"


#include "GLFW/glfw3.h"

namespace Luna {

	class WindowLogic : public WindowInterface
	{
	public:
		WindowLogic(const Window& details);
		virtual ~WindowLogic();

		void SetWindowData(const Window& data);
		void OnUpdate() override;

		//inline?
		//inline unsigned int GetWidth() override { return m_Data.Width; }
		//inline unsigned int GetHeight() override { return m_Data.Width; }
		uint32_t GetWidth() override { return m_Data.Width; }
		uint32_t GetHeight() override { return m_Data.Width; }


		void SetEventCallback(const EventCallBackFn& callback) override { m_Data.EventCallback = callback; }


		//Setup for callback
		void SetCallbackResize();
		void SetCallbackClose();
		void SetCallbackKeyboard();
		void SetCallbackChars();
		void SetCallbackMouseBtn();
		void SetCallbackMouseScroll();
		void SetCallbackCursorPos();


		void SetVSync(bool enabled) override;
		bool VSyncActive() const override;
		virtual void* GetOriginalWindow() const { return m_Window; }

	private:
		virtual void Init(const Window& data);
		virtual void Shutdown();

	private:
		GLFWwindow* m_Window;

	private:
		struct WindowData
		{
			std::string Title;
			uint32_t Width;
			uint32_t Height;
			bool VSync;

			EventCallBackFn EventCallback;
		};

		WindowData m_Data;
	};
}