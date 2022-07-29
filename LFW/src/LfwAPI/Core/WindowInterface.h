#pragma once

#include <memory>

#include "LfwAPI/Core/Defines.h"
#include "LfwAPI/EventHandler/MainEventBaseClass.h"
#include "LfwAPI/Core/Window.h"


namespace LFW {

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