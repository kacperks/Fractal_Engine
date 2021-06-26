cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(FractalEngine)

set(PLATFORM "Linux")

find_package(OpenGL REQUIRED)

add_subdirectory(Thirdparty/cmake/assimp)
add_subdirectory(Thirdparty/cmake/glew-cmake)
add_subdirectory(Thirdparty/cmake/glfw)
add_subdirectory(Thirdparty/cmake/glm)
add_subdirectory(Thirdparty/cmake/tinyxml2)

file(GLOB_RECURSE Runtime "Source/**.cpp" "Source/**.h" "Source/**.hpp")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/App/")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_executable(FractalEngine ${Runtime})

if(PLATFORM STREQUAL "Linux") # not tested yet!
target_link_libraries(FractalEngine -lGL)
target_link_libraries(FractalEngine -lglfw)
target_link_libraries(FractalEngine -lGLEW)
target_link_libraries(FractalEngine -lassimp)
target_link_libraries(FractalEngine -ltinyxml2)
endif()

if(PLATFORM STREQUAL "Windows") # not tested yet!
target_link_libraries(FractalEngine -lopengl32 -lglfw3 -lglew32 -lshell32 -lgdi32 -luser32 -lmsvcrt -lassimp-vc142-mt -ltinyxml2d)
endif()