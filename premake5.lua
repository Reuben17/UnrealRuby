workspace "UnrealRuby"
	architecture "x64"

	configurations 
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories raltive to root folder (solution directory)
IncludeDir ={}
IncludeDir["GLFW"] = "UnrealRuby/vendor/GLFW/include"

include "UnrealRuby/vendor/GLFW"

project "UnrealRuby"
	location "UnrealRuby"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "urpch.h"
	pchsource "UnrealRuby/src/urpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW",
		"opengl32.lib"
	}

filter "system:windows"
	cppdialect "C++17"
	staticruntime "On"
	systemversion "latest"

	defines
	{
		"UR_PLATFORM_WINDOWS",
		"UR_BUILD_DLL"
	}

	postbuildcommands
	{
		("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
	}

	filter "configurations:Debug"
		defines "UR_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "UR_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "UR_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"UnrealRuby/vendor/spdlog/include",
		"UnrealRuby/src"
	}

	links
	{
		"UnrealRuby"
	}

filter "system:windows"
	cppdialect "C++17"
	staticruntime "On"
	systemversion "latest"

	defines
	{
		"UR_PLATFORM_WINDOWS"
	}

	filter "configurations:Debug"
		defines "UR_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "UR_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "UR_DIST"
		optimize "On"