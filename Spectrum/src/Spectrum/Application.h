#pragma once

#include "Core.h"
#include "Events/Event.h"
namespace Spectrum {
	class SP_API Application // we use the macro definition
	{
	public:
		Application();

		virtual ~Application(); // Declared as virtual so the derived class can destroy correctly the object

		void Run();
	};
	// To be defined in CLIENT
	Application* CreateApplication();

}


