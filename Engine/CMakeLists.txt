cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(FractalEngine)

if (WIN32)
    set(PLATFORM "Windows")
endif (WIN32)

if(UNIX AND NOT APPLE)
    set(PLATFORM "Linux")
endif()

include_directories(Source/)

include_directories(Thirdparty/includes)

file(GLOB_RECURSE EngineSources "Source/**.cpp" "Source/**.h" "Source/**.hpp")

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
target_link_libraries(FractalEngine glfw)
target_link_libraries(FractalEngine glad)
target_link_libraries(FractalEngine tinyxml2)
target_link_libraries(FractalEngine assimp)
endif()