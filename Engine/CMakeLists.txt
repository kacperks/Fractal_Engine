cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(FractalEngine)

set(PLATFORM "Windows")

find_package(OpenGL REQUIRED)

include_directories(Thirdparty/scons/includes)
include_directories(Source/)

add_subdirectory(Thirdparty/cmake/glew-cmake)
add_subdirectory(Thirdparty/cmake/glfw)
add_subdirectory(Thirdparty/cmake/glm)
add_subdirectory(Thirdparty/cmake/assimp)
add_subdirectory(Thirdparty/cmake/tinyxml2)

file(GLOB_RECURSE EngineSources "Source/**.cpp" "Source/**.h" "Source/**.hpp")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/App/")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_library(FractalEngine SHARED ${EngineSources})

if(PLATFORM STREQUAL "Linux") # not tested yet!
target_link_libraries(FractalEngine -lGL)
target_link_libraries(FractalEngine -lglfw)
target_link_libraries(FractalEngine -lGLEW)
target_link_libraries(FractalEngine -lassimp)
target_link_libraries(FractalEngine -ltinyxml2)
endif()

if(PLATFORM STREQUAL "Windows") # not tested yet!
target_link_libraries(FractalEngine opengl32)
target_link_libraries(FractalEngine glfw3)
target_link_libraries(FractalEngine glew32s)
target_link_libraries(FractalEngine tinyxml2)
target_link_libraries(FractalEngine assimp)
endif()