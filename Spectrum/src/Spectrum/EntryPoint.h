#pragma once

#ifdef SP_PLATFORM_WINDOWS

extern Spectrum::Application* Spectrum::CreateApplication();
// declared extern since its outside the translation unit
// we delegate the creation of the application to the client
// we define the create application in an extern, in our case in the sandboxapp.cpp

int main(int argc, char** argv)
{
	Spectrum::Log::Init();
	SP_CORE_WARN("Initialized Log");
	


	auto app = Spectrum::CreateApplication();
	app ->Run();
	delete app;

}

#endif