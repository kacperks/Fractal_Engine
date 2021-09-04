cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(FractalEngine)

set(CONFIGURATION "Release")

add_subdirectory(Thirdparty/cmake/glad)

if (WIN32)
    set(PLATFORM "Windows")
endif (WIN32)

if(UNIX AND NOT APPLE)
    set(PLATFORM "Linux")
endif()

find_package(OpenGL REQUIRED)

include_directories(Thirdparty/includes)
include_directories(Source/)

if(CONFIGURATION STREQUAL "Release")

add_subdirectory(Thirdparty/cmake/glfw)
add_subdirectory(Thirdparty/cmake/glm)
add_subdirectory(Thirdparty/cmake/assimp)
add_subdirectory(Thirdparty/cmake/tinyxml2)

endif()

file(GLOB_RECURSE EngineSources "Source/**.cpp" "Source/**.h" "Source/**.hpp")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Bin/")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_library(FractalEngine SHARED ${EngineSources})

if(PLATFORM STREQUAL "Linux")
target_link_libraries(FractalEngine -lGL)
target_link_libraries(FractalEngine -lglfw)
target_link_libraries(FractalEngine -lglad)
target_link_libraries(FractalEngine -lassimp)
target_link_libraries(FractalEngine -ltinyxml2)
endif()

if(PLATFORM STREQUAL "Windows")
target_link_libraries(FractalEngine opengl32)
target_link_libraries(FractalEngine glfw3)
target_link_libraries(FractalEngine glad)
target_link_libraries(FractalEngine tinyxml2)
target_link_libraries(FractalEngine assimp)
endif()