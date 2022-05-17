#pragma once

#include <memory>

#include "LunaAPI/Core/Defines.h"
#include "LunaAPI/Event/Event.h"

namespace Luna {

	//RENAME
	struct Window
	{
		std::string Title;
		unsigned int Width;  //uint32_t
		unsigned int Height; //uint32_t

		Window(const std::string& title = "Luna Engine",
			unsigned int width = 1280, 
			unsigned int height = 720)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	class WindowInterface
	{
	public:
		using EventCallBackFn = std::function<void(Event&)>;

		virtual ~WindowInterface() = default;

		virtual void OnUpdate() = 0;
		virtual unsigned int GetWidth() = 0;
		virtual unsigned int GetHeight() = 0;
		virtual void SetEventCallback(const EventCallBackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool VSyncActive() const = 0;
		virtual void* GetOriginalWindow() const = 0;

		static WindowInterface* Create(const Window& props = Window());
	};
}