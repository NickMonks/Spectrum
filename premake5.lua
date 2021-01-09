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
project "Spectrum"
	location "Spectrum"
	kind "SharedLib" -- basically dll export
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
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include"
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
		symbols "On"

	filter "configurations:Release"
		defines "SP_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "SP_DIST"
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
		symbols "On"

	filter "configurations:Release"
		defines "SP_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "SP_DIST"
		optimize "On"

