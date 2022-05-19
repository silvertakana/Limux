outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
workspace "Limux"
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