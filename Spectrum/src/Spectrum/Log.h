#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"



namespace Spectrum {

	class SP_API Log
	{
		
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; } //we return a reference to our CoreLogger (i.e, we dont want to make a copy!)
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger; // in order to be return in a static member function these should be static
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
		

	};
}


// Macro for the logger (CORE)
// the ellipsis means that accepts any arguments, and __VA_ARGS__ just passes those args there.
// Also, these macros will be stripped out in the build stage
#define SP_CORE_ERROR(...)  ::Spectrum::Log::GetCoreLogger()->error(__VA_ARGS__)
#define SP_CORE_WARN(...)   ::Spectrum::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define SP_CORE_INFO(...)   ::Spectrum::Log::GetCoreLogger()->info(__VA_ARGS__)
#define SP_CORE_TRACE(...)  ::Spectrum::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define SP_CORE_FATAL(...)  ::Spectrum::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Macro for the logger (CLIENT)
#define SP_ERROR(...)  ::Spectrum::Log::GetClientLogger()->error(__VA_ARGS__)
#define SP_WARN(...)   ::Spectrum::Log::GetClientLogger()->warn(__VA_ARGS__)
#define SP_INFO(...)   ::Spectrum::Log::GetClientLogger()->info(__VA_ARGS__)
#define SP_TRACE(...)  ::Spectrum::Log::GetClientLogger()->trace(__VA_ARGS__)
#define SP_FATAL(...)  ::Spectrum::Log::GetClientLogger()->fatal(__VA_ARGS__)