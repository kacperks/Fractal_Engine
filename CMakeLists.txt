cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(FractalEngine)

set(PLATFORM "Linux")

find_package(OpenGL REQUIRED)


file(GLOB_RECURSE Runtime "Engine/Source/**.cpp" "Engine/Source/**.h" "Engine/Source/**.hpp" "Engine/Thirdparty/includes/**.cpp" "Engine/Thirdparty/includes/**.hpp" "Engine/Thirdparty/includes/**.h")

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