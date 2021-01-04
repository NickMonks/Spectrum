#pragma once

#include "Core.h"

namespace Spectrum {
	class SP_API Application // we literally use the macro definition
	{
	public:
		Application();

		virtual ~Application(); // Declared as virtual so the derived class can destroy correctly the object

		void Run();
	};
	// To be defined in CLIENT
	Application* CreateApplication();

}


