workspace "Spectrum"
	architecture "x64"

	configurations
	{
		"Debug", 
		"Release",
		"Dist"
	}
-- we define a variable for our path to the target dir
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
-- we create a struct with all of our included directories
IncludeDir = {}
IncludeDir["GLFW"] = "Spectrum/vendor/GLFW/include"
IncludeDir["Glad"] = "Spectrum/vendor/Glad/include"
IncludeDir["ImGui"] = "Spectrum/vendor/imgui"

-- the same way we include in c++, lua does the same. it copies all the info inside the file and pastes it here
-- we do that for the premake5.lua of GLFW, which is a project static library
include "Spectrum/vendor/GLFW"
include "Spectrum/vendor/Glad"
include "Spectrum/vendor/imgui"


project "Spectrum"
	location "Spectrum"
	kind "SharedLib" -- basically dll export
	language "C++"
	
	-- targetdir is the bin files, we use tokens from lua to do thi
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	-- objdir is the intermidiate files
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	-- PRECOMPILE HEADER
	pchheader "sppch.h"
	pchsource "Spectrum/src/sppch.cpp"


	files -- files to include in premake. the '**' means to look recursively
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"

	}

	includedirs -- directories to include
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}", -- we include the GLFW as a struct 1
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links
	{-- as said, project GLFW is pasted in the document so we can link it 
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows" -- project configurations to apply for certain platforms, for example in this case is windows
		cppdialect "C++17"
		staticruntime "On" -- linking the libraries. In our case we want it to be static linked. 
		systemversion "latest"

		defines -- preprocessor definitions
		{
			"SP_PLATFORM_WINDOWS",
			"SP_BUILD_DLL"
		}

		postbuildcommands
		{	-- After building, copy the dll into the sandbox
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir.. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "SP_DEBUG"
		buildoptions "/MDd" -- to link the correct version of the dll at runtime. A good explanation is here: https://forums.codeguru.com/showthread.php?313913-When-to-use-Multithreaded-Single-Threaded-Multithreaded-DLL
		symbols "On"		-- https://stackoverflow.com/questions/35310117/debug-assertion-failed-expression-acrt-first-block-header

	filter "configurations:Release"
		defines "SP_RELEASE"
		buildoptions "/MD" -- IMPORTANT: MUST BE DONE IN BOTH!!!
		optimize "On"

	filter "configurations:Dist"
		defines "SP_DIST"
		buildoptions "/MD"
		optimize "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"

	language "C++"

	-- targetdir is the bin files, we use tokens from lua to do thi
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	-- objdir is the intermidiate files
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files -- files to include in premake. the '**' means to look recursively
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"

	}

	includedirs -- directories to include
	{
		"Spectrum/vendor/spdlog/include",
		"Spectrum/src"
	}

	links -- link to the spectrum project
	{
		"Spectrum"
	}

	filter "system:windows" -- project configurations to apply for certain platforms, for example in this case is windows
		cppdialect "C++17"
		staticruntime "On" -- linking the libraries. In our case we want it to be static linked. 
		systemversion "latest"

		defines -- preprocessor definitions
		{
			"SP_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "SP_DEBUG"
		buildoptions "/MDd" -- to link the correct version of the dll at runtime. A good explanation is here: https://forums.codeguru.com/showthread.php?313913-When-to-use-Multithreaded-Single-Threaded-Multithreaded-DLL
		symbols "On"

	filter "configurations:Release"
		defines "SP_RELEASE"
		buildoptions "/MD" -- to link the correct version of the dll at runtime. A good explanation is here: https://forums.codeguru.com/showthread.php?313913-When-to-use-Multithreaded-Single-Threaded-Multithreaded-DLL
		optimize "On"

	filter "configurations:Dist"
		defines "SP_DIST"
		buildoptions "/MD" -- to link the correct version of the dll at runtime. A good explanation is here: https://forums.codeguru.com/showthread.php?313913-When-to-use-Multithreaded-Single-Threaded-Multithreaded-DLL
		optimize "On"

