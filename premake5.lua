workspace "UnrealRuby"
	architecture "x64"
	startproject "Sandbox"

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
IncludeDir["Glad"] = "UnrealRuby/vendor/Glad/include"
IncludeDir["ImGui"] = "UnrealRuby/vendor/imgui"
IncludeDir["glm"] = "UnrealRuby/vendor/glm"

--group "Dependancies"
	include "UnrealRuby/vendor/GLFW"
	include "UnrealRuby/vendor/Glad"
	include "UnrealRuby/vendor/imgui"

--group ""



project "UnrealRuby"
	location "UnrealRuby"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

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
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

filter "system:windows"
	cppdialect "C++17"
	systemversion "latest"

	defines
	{
		"UR_PLATFORM_WINDOWS",
		"UR_BUILD_DLL",
		"GLFW_INCLUDE_NONE"
	}

	postbuildcommands
	{
		("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
	}

	filter "configurations:Debug"
		defines "UR_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "UR_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "UR_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

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
		"UnrealRuby/src",
		"%{IncludeDir.glm}"
	}

	links
	{
		"UnrealRuby"
	}

filter "system:windows"
	cppdialect "C++17"
	systemversion "latest"

	defines
	{
		"UR_PLATFORM_WINDOWS"
	}

	filter "configurations:Debug"
		defines "UR_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "UR_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "UR_DIST"
		runtime "Release"
		optimize "On"