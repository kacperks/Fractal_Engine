workspace "Fractal_Engine"
    architecture "x64"
    startproject "Engine"
    configurations { "Editor", "Editor(C#)" ,"GameBulid" , "GameBulid(C#)"}
    platforms {"Win32", "x64"}

    project "Engine"
        location "%{prj.name}/"
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
            "%{prj.name}/lib/includes/**/*.h",
            "%{prj.name}/lib/includes/**/*.hpp",
            "%{prj.name}/lib/includes/**/*.cpp",
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
            "Gdi32",
            "User32",
		    "opengl32",
			"assimp-vc142-mt",
			"tinyxml2d",
	    }           

        defines {
            "GLEW_STATIC"
        }       
       	filter "system:windows"
		systemversion "latest"
			
		filter "configurations:Editor"
			runtime "Debug" -- Editor
			symbols "on"
			
		filter "configurations:Editor(C#)"
			defines "FRACTAL_CSHARP" -- Editor with C#
			links {"mono-2.0-sgen","MonoPosixHelper",}
			runtime "Debug"
			symbols "on"

		filter "configurations:GameBulid"
			defines "FR_BULID" -- Bulided Game
			runtime "Debug"
			optimize "on"
			
		filter "configurations:GameBulid(C#)"
			defines {"FR_BULID","FRACTAL_CSHARP",} -- Bulided Game with C# Scripts
			links {"mono-2.0-sgen","MonoPosixHelper",}
			runtime "Debug"
			optimize "on"
