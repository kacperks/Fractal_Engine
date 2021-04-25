set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

include(cmake/glfw.cmake)
include(cmake/imgui.cmake)