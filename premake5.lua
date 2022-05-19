outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
<<<<<<< HEAD
workspace "Limux"
=======
workspace "Lumix"
>>>>>>> 5b95b19c54b3dbd73c4028756609e5ad568466b1
	configurations { "Debug", "Release" ,"Dist"}
	platforms { "x86", "x64" }
	startproject "Sandbox"

	systemversion "latest"

	vpaths {
		["Headers"] = { "%{prj.name}/src/**.hpp","%{prj.name}/src/**.h" },
		["Sources"] = { "%{prj.name}/src/**.cpp","%{prj.name}/src/**.c" },
		["images"] = {"**.png","**.jpg","**.bmp","**.ppm","**.pgm","**.pbm","**.tga","**.gif","**.ico","**.icns","**.cur","**.xbm","**.xpm"},
		["shaders"] = {"**.shader","**.frag","**.vert","**.glsl","**.hlsl"},
		["Docs"] = "**.md",
	}
	
	filter "platforms:x86"
		architecture "x86"
		defines { "x86" }
		
	filter "platforms:x64"
		architecture "x86_64"
		defines { "x64" }

	
	
<<<<<<< HEAD
IncludeDir = {}
IncludeDir["GLFW"] =  "%{wks.location}/Limux/vendor/GLFW/include"
IncludeDir["Glad"] =  "%{wks.location}/Limux/vendor/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/Limux/vendor/imgui"
IncludeDir["glm"] =   "%{wks.location}/Limux/vendor/glm"
IncludeDir["stb"] =   "%{wks.location}/Limux/vendor/stb"



group "Dependencies"
	include "Limux/vendor/GLFW"
	include "Limux/vendor/Glad"
	include "Limux/vendor/imgui"
	include "Limux/vendor/stb"
	
group ""
--group "Engine"
	include "Limux"
	include "sandbox"
--group ""
=======

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] =  "Lumix/vendor/GLFW/include"
IncludeDir["Glad"] =  "Lumix/vendor/Glad/include"
IncludeDir["ImGui"] = "Lumix/vendor/imgui"
IncludeDir["glm"] =   "Lumix/vendor/glm"
IncludeDir["stb"] =   "Lumix/vendor/stb"

group "Dependencies"
	include "Lumix/vendor/GLFW"
	include "Lumix/vendor/Glad"
	include "Lumix/vendor/imgui"
	include "Lumix/vendor/stb"

group ""

project "Lumix"
	location "Lumix"
	kind "StaticLib"

	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	defines { 
		"LMX_BUILD_DLL", 
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE",
	}
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "lmxpch.h"
	pchsource "%{prj.name}/src/lmxpch.cpp"

	files {
		"%{prj.name}/src/**.hpp", 
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.cpp", 
		"%{prj.name}/src/**.c", 
		"%{prj.name}/res/**.**",
	}

	includedirs {
		"%{prj.name}/src",
		IncludeDir,
	}
	links{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32",
		"stb",
	}
	filter "system:windows"
		postbuildcommands {
			"{COPY} res/ ../bin/" .. outputdir .. "/%{prj.name}/res/", --copy resource files
			-- ("{COPY} ../bin/" .. outputdir .. "/%{prj.name}/**.dll ../bin/" .. outputdir .. "/Sandbox"), --copy the dll to sandbox
		}
		defines{
			"LMX_PLATFORM_WINDOWS"
		}
	filter ("files:Lumix/libraries/**.**")
		flags {"NoPCH"}

	filter "configurations:Debug"
		defines { "LMX_DEBUG" }
		runtime "Debug"
		buildoptions "/MDd"
		symbols "On"
		
	filter "configurations:Release"
		defines { "LMX_NDEBUG" }
		runtime "Release"
		buildoptions "/MD"
		optimize "On"
		
	filter "configurations:Dist"
		defines { "LMX_NDEBUG","LMX_DIST" }
		runtime "Release"
		buildoptions "/MD"
		optimize "On"
		

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"

	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files {
		"%{prj.name}/src/**.hpp", 
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.cpp", 
		"%{prj.name}/src/**.c", 
		"%{prj.name}/res/**.**",
	}

	includedirs {
		"Lumix/src",
		"Lumix/vendor",
		IncludeDir,
	}
	links {
		"Lumix"
	}
	filter "system:windows"
		postbuildcommands {
			"{COPY} res/ ../bin/" .. outputdir .. "/%{prj.name}/res/",
		}
		defines{
			"LMX_PLATFORM_WINDOWS"
		}
	filter ("files:Sandbox/libraries/**.**")
    	flags {"NoPCH"}

	filter "configurations:Debug"
		defines { "LMX_DEBUG" }
		runtime "Debug"
		buildoptions "/MDd"
		symbols "On"
		
	filter "configurations:Release"
		defines { "LMX_NDEBUG" }
		runtime "Release"
		buildoptions "/MD"
		optimize "On"
		
	filter "configurations:Dist"
		defines { "LMX_NDEBUG","LMX_DIST" }
		runtime "Release"
		buildoptions "/MD"
		optimize "On"
>>>>>>> 5b95b19c54b3dbd73c4028756609e5ad568466b1
