outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
workspace "Lumix"
	configurations { "Debug", "Release" ,"Dist"}
	platforms { "x86", "x64" }
	startproject "Sandbox"

	systemversion "latest"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

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
	

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] =  "Lumix/vendor/GLFW/include"
IncludeDir["Glad"] =  "Lumix/vendor/Glad/include"
IncludeDir["ImGui"] = "Lumix/vendor/imgui"
IncludeDir["glm"] =   "Lumix/vendor/glm"

include "Lumix/vendor/GLFW"
include "Lumix/vendor/Glad"
include "Lumix/vendor/imgui"

project "Lumix"
	location "Lumix"
	kind "SharedLib"

	language "C++"
	cppdialect "C++20"
	staticruntime "off"

	defines { "LMX_BUILD_DLL" }

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
	}
	filter "system:windows"
		postbuildcommands {
			"{COPY} res/ ../bin/" .. outputdir .. "/%{prj.name}/res/", --copy resource files
			("{COPY} ../bin/" .. outputdir .. "/%{prj.name}/**.dll ../bin/" .. outputdir .. "/Sandbox"), --copy the dll to sandbox
		}
	filter ("files:Lumix/libraries/**.**")
		flags {"NoPCH"}

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"

	language "C++"
	cppdialect "C++20"

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
		"Lumix",
		"ImGui",
	}
	filter "system:windows"
		postbuildcommands {
			"{COPY} res/ ../bin/" .. outputdir .. "/%{prj.name}/res/",
		}
	filter ("files:Sandbox/libraries/**.**")
    	flags {"NoPCH"}

