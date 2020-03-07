project "GLAD"
	kind "StaticLib"
	language "C"
	targetdir ("bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}")
	objdir ("bin-int/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}")
	files { "include/GLAD/glad.h", "include/KHR/khrplatform.h", "src/glad.c", }
	includedirs { "include" }
	filter "system:windows"
		systemversion "latest"
		staticruntime "On"
	filter { "system:windows", "configurations:Release" }
		buildoptions "/MT"