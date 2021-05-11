workspace "Fractal Engine"
    architecture "x86_64"
    startproject "APP"
    configurations { "Debug", "GameBulid" }


    project "Engine"
        language "C++"    
		cppdialect "C++17"
        kind "ConsoleApp"
        targetname "Fractal"
        staticruntime "on"
		
        targetdir "bin/%{cfg.buildcfg}"  
        objdir ("bin/obj/%{cfg.buildcfg}/obj")
        
        pchheader "pch.h"
        pchsource "%{prj.name}/src/pch.cpp" 

        files {
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp",
			"%{prj.name}/src/**.hpp",
        }

        includedirs {
            "%{prj.name}/src/Vendor",
            "%{prj.name}/src",            
	        "%{prj.name}/lib/includes",
        }          

        libdirs {
            "%{prj.name}/lib/lib/",          
        }

        links {
		    "glew32s",
		    "glfw3",
            "Shell32",
            "Gdi32.",
            "User32",
		    "opengl32",
            "mono-2.0-sgen", -- if your compiler doesn't support mono remove this and 43 line' 
            "MonoPosixHelper",
			"assimp-vc142-mt",
			"tinyxml2d",
	    }           

        defines {
            "GLEW_STATIC"
        }       
       	filter "system:windows"
		systemversion "latest"
			
		filter "configurations:Debug"
			defines "FR_DEBUG"
			runtime "Debug"
			symbols "on"

		filter "configurations:GameBulid"
			defines "FR_BULID" -- Bulided Game
			runtime "Release"
			optimize "on"
