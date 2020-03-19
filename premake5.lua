workspace "XEngine"
	architecture "x64"
	startproject "Game"
	configurations { "Debug", "Release", "Dist" }
outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
IncludeDir = {}
IncludeDir["GLFW"] = "XEngine/Dependencies/GLFW/include"
IncludeDir["GLAD"] = "XEngine/Dependencies/GLAD/include"
IncludeDir["ImGui"] = "XEngine/Dependencies/ImGui"
IncludeDir["glm"] = "XEngine/Dependencies/glm"
group "Dependencies"
	include "XEngine/Dependencies/GLFW"
	include "XEngine/Dependencies/Glad"
	include "XEngine/Dependencies/imgui"
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
		files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp", "%{prj.name}/Dependencies/glm/glm/**.hpp", "%{prj.name}/Dependencies/glm/glm/**.inl" }
		defines { "_CRT_SECURE_NO_WARNINGS" }
		includedirs { "%{prj.name}/src", "%{prj.name}/Dependencies/spdlog/include", "%{IncludeDir.GLFW}", "%{IncludeDir.GLAD}", "%{IncludeDir.ImGui}", "%{IncludeDir.glm}" }
		links{ "GLFW", "GLAD", "ImGui", "opengl32.lib" }
		filter "system:windows"
			staticruntime "On"
			systemversion "latest"
			defines { "X_PLATFORM_WINDOWS", "X_BUILD_DLL", "GLFW_INCLUDE_NONE" }
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
		includedirs { "%{prj.name}/src", "XEngine/Dependencies/spdlog/include", "XEngine/src", "%{IncludeDir.glm}", "XEngine/Dependencies" }
		links { "XEngine" }
		filter "system:windows"
			systemversion "latest"
			defines { "X_PLATFORM_WINDOWS" }
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