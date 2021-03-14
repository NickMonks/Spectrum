#include <Spectrum.h>

class ExampleLayer : public Spectrum::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{

	}

	void OnUpdate() override
	{
		SP_INFO("ExampleLayer::Update");
	}

	void OnEvent(Spectrum::Event& event) override
	{
		SP_INFO("{0}", event);
	}
};



class Sandbox : public Spectrum::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Spectrum::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

// The actual client allocates in the heap the new client
Spectrum::Application* Spectrum::CreateApplication() {
	// sandbox inherits from application, so it creates both sandbox and application from spectrum engine
	return new Sandbox();
}