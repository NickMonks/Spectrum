#pragma once

// We defined the Spectrum as dll, so we need to export and import.
// to do so, we define the macro for this preprocessor directive. 

#ifdef SP_PLATFORM_WINDOWS
	#ifdef SP_BUILD_DLL // if we are in build mode of Spectrum, we will export. Otherwise we will import the dll
		#define SP_API __declspec(dllexport)
	#else
		#define SP_API __declspec(dllimport)
	#endif
#else
	#error Spectrum only supports Windows!
#endif

#define BIT(x) (1<<x) // This shifts the x 1 bit left. 
