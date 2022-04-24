
libFiles = {  }
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
workspace "Lumix"
	configurations { "Debug", "Release" ,"Dist"}
	platforms { "x86", "x64" }

	language "C++"
	cppdialect "C++20"
	systemversion "latest"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	includedirs {
		"libraries/include",
		"%{prj.name}/libraries/include",
	}
	libdirs {
		"%{prj.name}/libraries/lib",
		"libraries/lib",
	}
	links{
		libFiles,
	}

	files {
		"%{prj.name}/src/**.hpp", 
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.cpp", 
		"%{prj.name}/src/**.c", 
		"%{prj.name}/res/**.**",
		"%{prj.name}/libraries/**.**",
	}
		
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
		defines { "_DEBUG" }
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		defines { "_NDEBUG" }
		runtime "Release"
		optimize "On"
		
	filter "configurations:Dist"
		defines { "_NDEBUG","_DIST" }
		runtime "Release"
		optimize "On"
	
	filter "system:windows"
		postbuildcommands {
			"{COPY} res/ ../bin/" .. outputdir .. "/%{prj.name}/res/",
			("{COPY} %{prj.name}/libraries/bin ../bin/" .. outputdir .. "/%{prj.name}"),
			("{COPY} libraries/bin ../bin/" .. outputdir .. "/%{prj.name}"),
		}


project "Lumix"
	location "Lumix"
	kind "SharedLib"

	defines { "LMX_BUILD_DLL" }

	pchheader "lmxpch.h"
	pchsource "%{prj.name}/src/lmxpch.cpp"
	includedirs{
		"%{prj.name}/src"
	}
	links{
		"opengl32.lib", 
		"glfw3.lib", 
		"assimp-vc143-mt",
	}
	postbuildcommands {
		("{COPY} ../bin/" .. outputdir .. "/%{prj.name}/**.dll ../bin/" .. outputdir .. "/Sandbox"),
	}
	filter ("files:Lumix/libraries/**.**")
		flags {"NoPCH"}

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"

	links {"Lumix"}
	
	includedirs {
		"Lumix/src"
	}

	filter ("files:Sandbox/libraries/**.**")
    	flags {"NoPCH"}

