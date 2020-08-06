workspace "XEngine"	
	architecture "x86_64"
	startproject "X-Editor"
	configurations 
	{
		"Debug",
		"Release",
		"Dist"
	}
outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
IncludeDir = {}
IncludeDir["GLFW"]  = "X-Engine/vendor/GLFW/include"
IncludeDir["GLAD"]  = "X-Engine/vendor/GLAD/include"
IncludeDir["ImGui"] = "X-Engine/vendor/ImGui"
IncludeDir["ImGuiFileBrowser"] = "X-Engine/vendor/ImGuiFileBrowser"
IncludeDir["glm"]   = "X-Engine/vendor/glm"
IncludeDir["stb"]   = "X-Engine/vendor/stb"
group "Dependencies"
	include "X-Engine/vendor/GLFW"
	include "X-Engine/vendor/GLAD"
	include "X-Engine/vendor/imgui"
group "Engine"
	project "X-Engine"
		location "X-Engine"
		kind "StaticLib"
		language "C++"
		cppdialect "C++17"
		staticruntime "on"
		targetdir ("bin/" .. outputDir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputDir .. "/%{prj.name}")
		pchheader "Xpch.h"
		pchsource "X-Engine/src/Xpch.cpp"
		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp",
			"%{prj.name}/vendor/stb/**.h",
			"%{prj.name}/vendor/stb/**.cpp",
			"%{prj.name}/vendor/glm/glm/**.hpp",
			"%{prj.name}/glm/glm/**.inl",
			"%{prj.name}/vendor/ImGuiFileBrowser/**.h"
		}
		defines
		{
			"_CRT_SECURE_NO_WARNINGS",
			"GLFW_INCLUDE_NONE"
		}
		includedirs
		{ 
			"%{prj.name}/src",
			"%{prj.name}/vendor/spdlog/include",
			"%{IncludeDir.GLFW}",
			"%{IncludeDir.GLAD}",
			"%{IncludeDir.ImGui}",
			"%{IncludeDir.ImGuiFileBrowser}",
			"%{IncludeDir.glm}",
			"%{IncludeDir.stb}"
		}
		links
		{ 
			"GLFW",
			"GLAD",
			"ImGui",
			"opengl32.lib"
		}
		filter "system:windows"
			staticruntime "On"
			systemversion "latest"
		filter "configurations:Debug"
			defines "XDEBUG"
			symbols "on"
			staticruntime "off"
		filter "configurations:Release"
			defines "XRELEASE"
			runtime "Release"
			optimize "on"
		filter "configurations:Dist"
			defines "XDIST"
			runtime "Release"
			optimize "on"
group "Game"
	project "Game"
		location "Game"
		kind "ConsoleApp"
		language "C++"
		cppdialect "C++17"
		targetdir ("bin/" .. outputDir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputDir .. "/%{prj.name}")
		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp"
		}
		includedirs
		{
			"%{prj.name}/src",
			"X-Engine/vendor/spdlog/include",
			"X-Engine/src",
			"%{IncludeDir.glm}",
			"X-Engine/vendor"
		}
		links 
			{ "X-Engine" }
		filter "system:windows"
			systemversion "latest"
		filter "configurations:Debug"
			defines "XDEBUG"
			-- BUG: Staticruntime should be set to on, but the project generates errors when built
			staticruntime "off"
			symbols "on"
			runtime "Debug"
		filter "configurations:Release"
			defines "XRELEASE"
			optimize "on"
			staticruntime "on"
			runtime "Release"
		filter "configurations:Dist"
			defines "XDIST"
			optimize "on"
			staticruntime "on"
			runtime "Release"
group "Editor"
	project "X-Editor"
		location "X-Editor"
		kind "ConsoleApp"
		language "C++"
		cppdialect "C++17"
		targetdir ("bin/" .. outputDir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputDir .. "/%{prj.name}")
		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp"
		}
		includedirs
		{
			"%{prj.name}/src",
			"X-Engine/vendor/spdlog/include",
			"X-Engine/src",
			"%{IncludeDir.glm}",
			"X-Engine/vendor"
		}
		links 
			{ "X-Engine" }
		filter "system:windows"
			systemversion "latest"
		filter "configurations:Debug"
			defines "XDEBUG"
			symbols "on"
			staticruntime "off"
			runtime "Debug"
		filter "configurations:Release"
			defines "XRELEASE"
			optimize "on"
			staticruntime "on"
			runtime "Release"
		filter "configurations:Dist"
			defines "XDIST"
			optimize "on"
			staticruntime "on"
			runtime "Release"