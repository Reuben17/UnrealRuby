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
IncludeDir["stb_image"] = "UnrealRuby/vendor/stb_image"

--group "Dependancies"
	include "UnrealRuby/vendor/GLFW"
	include "UnrealRuby/vendor/Glad"
	include "UnrealRuby/vendor/imgui"

--group ""



project "UnrealRuby"
	location "UnrealRuby"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "urpch.h"
	pchsource "UnrealRuby/src/urpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.ini"
	}

	defines	
	{
		"_CRT_SECURE_NO_WARNINGS"
	}
	
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

filter "system:windows"
	systemversion "latest"

	defines
	{
		"UR_PLATFORM_WINDOWS",
		"UR_BUILD_DLL",
		"GLFW_INCLUDE_NONE"
	}

	filter "configurations:Debug"
		defines "UR_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "UR_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "UR_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"UnrealRuby/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"UnrealRuby"
	}

filter "system:windows"
	systemversion "latest"

	defines
	{
		"UR_PLATFORM_WINDOWS"
	}

	filter "configurations:Debug"
		defines "UR_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "UR_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "UR_DIST"
		runtime "Release"
		optimize "on"
