#pragma once

#include "LunaAPI/Core/Window.h"
#include "GLFW/glfw3.h"

namespace Luna {

	class WindowLogic : public WindowInterface
	{

	public:
		WindowLogic(const Window& details);
		virtual ~WindowLogic();

		void OnUpdate() override;
		inline unsigned int GetWidth() override { return m_Data.Width; }
		inline unsigned int GetHeight() override { return m_Data.Width; }

		void SetEventCallback(const EventCallBackFn& callback) override { m_Data.EventCallback = callback; }
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