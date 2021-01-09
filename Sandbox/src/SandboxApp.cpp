

#include <Spectrum.h>

class Sandbox : public Spectrum::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

// The actual client allocates in the heap the new client
Spectrum::Application* Spectrum::CreateApplication() {
	return new Sandbox();
}