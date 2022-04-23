
libFiles = { "opengl32.lib", "glfw3.lib" }
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
		libFiles
	}

	files {
		"%{prj.name}/src/**.hpp", 
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.cpp", 
		"%{prj.name}/src/**.c", 
		"%{prj.name}/res/**.**"
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
		}


project "Lumix"
	location "Lumix"
	kind "SharedLib"

	filter ("files:" .. "Lumix" .. "/libraries/**.**")
    	flags {"NoPCH"}
	postbuildcommands {
		"{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox",
	}

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"

	links {"Lumix"}

	filter ("files: Sandbox/libraries/**.**")
    	flags {"NoPCH"}

