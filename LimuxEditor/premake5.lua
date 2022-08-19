-- Include directories relative to root folder (solution directory)

project "LimuxEditor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir (outputOrigin .."/bin/" .. outputdir .. "/%{prj.name}")
	objdir (outputOrigin .."/bin-int/" .. outputdir .. "/%{prj.name}")

	disablewarnings { "4996" }
	
	files {
		"src/**.hpp", 
		"src/**.h", 
		"src/**.cpp", 
		"src/**.c", 
		"res/**.**",
	}

	includedirs {
		"%{wks.location}/Limux/src",
		"%{wks.location}/Limux/vendor",
		IncludeDir,
	}
	
	links {
		"Limux"
	}
	filter "system:windows"
		postbuildcommands {
			"{COPY} res/ " .. outputOrigin .. "/bin/" .. outputdir .. "/%{prj.name}/res/", --copy resource files
			"{COPY} **.ini " .. outputOrigin .. "/bin/" .. outputdir .. "/%{prj.name}", --copy ini files
		}
	filter ("files:Sandbox/vendor/**.**")
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