#pragma once

#include "sppch.h"

#include "Spectrum/Core.h"
#include "Spectrum/Events/Event.h"

namespace Spectrum {

	//windows properties that should have
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Spectrum Engine",
			unsigned int width = 1280,
			unsigned int height = 720)
			: Title(title), Width(width), Height(height) {}
	};

	// Interface representing a desktop system based Window
	// This must be implemented PER PLTFORM
	class SP_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>; // Event& references to any member in Event (or derived class). Event& is the "this" pointer

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		//Window Attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProps& props = WindowProps()); // this static member function will call the default struct if none is specified

	};
	
}
