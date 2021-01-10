#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"


#include <Spectrum/Window.h>

namespace Spectrum {
	class SP_API Application // we use the macro definition
	{
	public:
		Application();

		virtual ~Application(); // Declared as virtual so the derived class can destroy correctly the object

		void Run();
		void OnEvent(Event& e);
	private:

		//event signature
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};
	// To be defined in CLIENT
	Application* CreateApplication();

}


