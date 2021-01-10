#include "sppch.h"
#include "Application.h"
#include "Log.h"

#include <GLFW/glfw3.h>



namespace Spectrum {

	// In order to include the function to eventcallback, we use bind. Which takes a reference to OnEvent (why?), the argument and the placeholders
	// the bind returns the function wrapper std::function. We pass the function member pointer
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application() {
		m_Window = std::unique_ptr<Window>(Window::Create());// explicit constructor for unique pointer
															// thanks to this we dont need to take care of destruction;
		
		// this will save the callback event into the m_Data struct, passed as a function pointer
		// it will create a function wrapper with format function(x), where x is the placeholder.
		//in our case, the placeholder is Event& e. 

		// every time we 
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	
	}

	void Application::OnEvent(Event& e)
	{
		//once the function pointer in the m_data struct is called, because we initially bind it to OnEvent, it gets called here. 
		EventDispatcher dispatcher(e);

		//We call the dispatcher with the type of event.
		//The argument is binded with Application::OnWindowClose. If T (<WindowCloseEvent>) gets called, then 
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		SP_CORE_TRACE("{0}", e);
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		//When this event is called, automatically it will stop running the application
		m_Running = false;
		return true;
	}

	Application::~Application() {
	}

	void Application::Run() {

		
		while (m_Running)
		{	
			//because we created a window context, we can start doing stuff there:
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}
}

