#include "sppch.h"
#include "WindowsWindow.h"

#include "Spectrum/Events/ApplicationEvent.h"
#include "Spectrum/Events/MouseEvent.h"
#include "Spectrum/Events/KeyEvent.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h> //include GLFW after glad


namespace Spectrum {

	static bool s_GLFWInitialized = false; // this is used as a static, since we maybe have more than one window and we dont want to shutdown it 

	static void GLFWErrorCallback(int error, const char* description)
	{
		SP_CORE_ERROR("GLFW Error{0}: {1}", error, description);
	}



	// This method comes from the windows class. But because is static, is no longer part of the class itself
	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props); // create a pointer in the heap. we will store it in an unique pointer to manage garbage collection
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{

	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		SP_CORE_INFO("Creating window {0} {1} {2}", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized) // if GLFW is not initialized
		{
			int success = glfwInit();
			//we check if its done successfully.
			SP_CORE_ASSERT(success, "Could not initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		SP_CORE_ASSERT(status, "Failed to initialize Glad");
		glfwSetWindowUserPointer(m_Window, &m_Data); // We pass a struct data with a function callback so it points it in the window
		SetVSync(true);

		//Set GLFW Callbacks

		//for the size callback it accepts a function pointerwith the arguments defined in the lambda expre
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window); // this returns to a void pointer, so we cast it to the WindowData struct and create a reference of it. 
				
				//dispatch it
				data.Width = width;
				data.Height = height;

				//every time this event is called, it will call EventCallback(event). Because it is binded
				// to OnEvent definition, this event will substitute the placeholder. 

				WindowResizeEvent event(width, height);
				data.EventCallback(event);

			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window); // this returns to a void pointer, so we cast it to the WindowData struct and create a reference of it. 
			WindowCloseEvent event;
			data.EventCallback(event);


			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window); // this returns to a void pointer, so we cast it to the WindowData struct and create a reference of it. 

				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent event(key, 0);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent event(key);
						data.EventCallback(event);
						break;
					}
					
					case GLFW_REPEAT:
					{
						KeyPressedEvent event(key, 1);
						data.EventCallback(event);
						break;
					}
				}
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window); // this returns to a void pointer, so we cast it to the WindowData struct and create a reference of it. 
				
				switch (action)
				{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent event(button);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonPressedEvent event(button);
						data.EventCallback(event);
						break;
					}
					
					case GLFW_REPEAT:
					{
						MouseButtonReleasedEvent event(button);
						data.EventCallback(event);
						break;
					}
				}

			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window); // this returns to a void pointer, so we cast it to the WindowData struct and create a reference of it. 
				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.EventCallback(event);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) 
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window); // this returns to a void pointer, so we cast it to the WindowData struct and create a reference of it. 
				MouseMovedEvent event((float)xPos, (float)yPos);
				data.EventCallback(event);

			});

	}

	void WindowsWindow::Shutdown()
	{
		Shutdown();
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window); //there are two buffers - one currently shown and one you draw on

	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
		{
			glfwSwapInterval(1);

		}
		else {
			glfwSwapInterval(0);
		}

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
}