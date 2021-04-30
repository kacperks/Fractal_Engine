workspace "FR"
    architecture "x86_64"
    startproject "APP"
    configurations { "Debug", "Release" }


    project "src"
        language "C++"    
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
            "src",
            "src/Vendor",            
	    "lib/includes",
        }          

        libdirs {
            "libs/lib/Shared",  
            "libs/lib/%{cfg.buildcfg}"        
        }

        links {
            "nfd.lib",
		    "glew32s.lib",
		    "glfw3dll.lib",
		    "opengl32.lib",
	    }           

        defines {
            "GLEW_STATIC"
        }       
-- test
       	filter "system:windows"
		systemversion "latest"
			
		filter "configurations:Debug"
			defines "FR_DEBUG"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			defines "FR_RELEASE"
			runtime "Release"
			optimize "on"
