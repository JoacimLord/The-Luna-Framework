#pragma once

#include <memory>

#include "LunaAPI/Core/Defines.h"
#include "LunaAPI/Event/Event.h"
#include "LunaAPI/Core/Window.h"


namespace Luna {

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