workspace "XEngine"	
	architecture "x86_64"
	startproject "Game"
	configurations 
	{
		"Debug",
		"Release",
		"Dist"
	}
outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
IncludeDir = {}
IncludeDir["GLFW"]  = "XEngine/vendor/GLFW/include"
IncludeDir["GLAD"]  = "XEngine/vendor/GLAD/include"
IncludeDir["ImGui"] = "XEngine/vendor/ImGui"
IncludeDir["glm"]   = "XEngine/vendor/glm"
IncludeDir["stb"]   = "XEngine/vendor/stb"
group "Dependencies"
	include "XEngine/vendor/GLFW"
	include "XEngine/vendor/GLAD"
	include "XEngine/vendor/imgui"
group "X-Engine"
	project "XEngine"
		location "XEngine"
		kind "StaticLib"
		language "C++"
		cppdialect "C++17"
		staticruntime "on"
		targetdir ("bin/" .. outputDir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputDir .. "/%{prj.name}")
		pchheader "Xpch.h"
		pchsource "XEngine/src/Xpch.cpp"
		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp",
			"%{prj.name}/vendor/stb/**.h",
			"%{prj.name}/vendor/stb/**.cpp",
			"%{prj.name}/vendor/glm/glm/**.hpp",
			"%{prj.name}/glm/glm/**.inl"
		}
		defines
			{ "_CRT_SECURE_NO_WARNINGS" }
		includedirs
		{ 
			"%{prj.name}/src",
			"%{prj.name}/vendor/spdlog/include",
			"%{IncludeDir.GLFW}",
			"%{IncludeDir.GLAD}",
			"%{IncludeDir.ImGui}",
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
			defines 
			{
				"X_BUILD_DLL",
				"GLFW_INCLUDE_NONE"
			}
		filter "configurations:Debug"
			defines "X_DEBUG"
			symbols "on"
			staticruntime "off"
		filter "configurations:Release"
			defines "X_RELEASE"
			runtime "Release"
			optimize "on"
		filter "configurations:Dist"
			defines "X_DIST"
			runtime "Release"
			optimize "on"
group "Game"
	project "Game"
		location "Game"
		kind "ConsoleApp"
		language "C++"
		cppdialect "C++17"
		staticruntime "off"
		targetdir ("bin/" .. outputDir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputDir .. "/%{prj.name}")
		files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }
		includedirs
		{
			"%{prj.name}/src",
			"XEngine/vendor/spdlog/include",
			"XEngine/src",
			"%{IncludeDir.glm}",
			"XEngine/vendor"
			}
		links 
			{ "XEngine" }
		filter "system:windows"
			systemversion "latest"
		filter "configurations:Debug"
			defines "X_DEBUG"
			symbols "on"
			runtime "Debug"
		filter "configurations:Release"
			defines "X_RELEASE"
			optimize "on"
			runtime "Release"
		filter "configurations:Dist"
			defines "X_DIST"
			optimize "on"
			runtime "Release"
