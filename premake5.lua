workspace "FR"
    architecture "x86_64"
    startproject "APP"
    configurations { "Debug", "Release" }


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
		    "glew32s.lib",
		    "glfw3.lib",
		    "opengl32.lib",
			"assimp-vc142-mt.lib",
			"tinyxml2d.lib",
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

		filter "configurations:Release"
			defines "FR_RELEASE"
			runtime "Release"
			optimize "on"
