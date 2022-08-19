-- Include directories relative to root folder (solution directory)

project "Limux"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"
	disablewarnings { "4996" }
	defines { 
		"LMX_BUILD_DLL", 
		--"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE",
	}
	
	targetdir (outputOrigin .."/bin/" .. outputdir .. "/%{prj.name}")
	objdir (outputOrigin .."/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "lmxpch.h"
	pchsource "src/lmxpch.cpp"

	files {
		"src/**.hpp", 
		"src/**.h", 
		"src/**.cpp", 
		"src/**.c", 
		"res/**.**",
	}

	includedirs {
		"src/",
		"../",
		IncludeDir,
	}
	links{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32",
		"stb",
		"assimp"
	}
	filter "system:windows"
		postbuildcommands {
			"{COPY} res/ " .. outputOrigin .. "/bin/" .. outputdir .. "/%{prj.name}/res/", --copy resource files
			"{COPY} **.ini " .. outputOrigin .. "/bin/" .. outputdir .. "/%{prj.name}", --copy ini files
			-- ("{COPY} ../bin/" .. outputdir .. "/**.dll ../bin/" .. outputdir .. "/Sandbox"), --copy the dll to sandbox
		}
	filter ("files:Limux/vendor/**.**")
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