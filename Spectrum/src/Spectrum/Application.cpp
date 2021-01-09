#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Log.h"

namespace Spectrum {
	Application::Application() {

	}

	Application::~Application() {
	}

	void Application::Run() {

		WindowResizeEvent e(1200, 720);
		SP_TRACE(e);

		while (true);
	}
}

