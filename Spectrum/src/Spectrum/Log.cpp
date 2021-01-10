#include "sppch.h"

#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Spectrum {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;


	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$"); // for more info of the type of pattern that we can write refer to the wiki in github
		s_CoreLogger = spdlog::stdout_color_mt("SPECTRUM"); // this will create a shared pointer 
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);




	}
	

}
