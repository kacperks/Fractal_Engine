import os
import platform
import glob

env = Environment(CXXCOMSTR="Compiling => $SOURCES", LINKCOMSTR="Linking Program => $TARGET",
                CPPPATH=["Engine/Source", "Engine/Source/Vendor", "Engine/Thirdparty/scons/includes"], CXXFLAGS="/std:c++17 /EHsc", TARGET_ARCH="x86")


libraries = [
	"glew32",
    "glfw3",
    "shell32",
    "gdi32",
    "user32",
    "opengl32",
    "msvcrt",
    "assimp-vc142-mt",
    "tinyxml2d"
]

sources = glob.glob("Engine/Source/**/*.cpp", recursive=True)
sources.extend(glob.glob("Engine/Thirdparty/scons/includes/**/*.cpp", recursive=True))

for source in sources:
    n_object = os.path.basename(source).replace(".cpp", ".obj")
    env.Object("App/obj/%s" % n_object, source)

env.Program("App/Fractal_Engine", Glob("App/obj/*.obj"), LIBPATH="Engine/Thirdparty/scons/lib", LIBS=libraries)