workspace "Fractal Engine"
    architecture "x86_64"
    startproject "APP"
    configurations { "Debug", "GameBulid" }


    project "src"
        language "C++"    
		cppdialect "C++17"
        kind "ConsoleApp"
        targetname "Fractal"
        staticruntime "on"
		
        targetdir "bin/%{cfg.buildcfg}"  
        objdir ("bin/obj/%{cfg.buildcfg}/obj")
        
        pchheader "pch.h"
        pchsource "src/pch.cpp"  

        files {
            "%{prj.name}/**.h",
            "%{prj.name}/**.cpp",
			"%{prj.name}/**.hpp",
        }

        includedirs {
            "src/Vendor",            
	        "lib/includes",
        }          

        libdirs {
            "lib/lib/",          
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
