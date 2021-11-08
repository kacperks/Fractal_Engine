cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(Fractal)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(COMMON_CXX_FLAGS "${COMMON_CXX_FLAGS} -g3 -O0 -Wall -pedantic -Wextra -m64 -mavx2 -mfma -ffast-math")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(COMMON_CXX_FLAGS "${COMMON_CXX_FLAGS} -Wall -pedantic -Wextra -m64 -mavx2 -mfma -ffast-math")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(COMMON_CXX_FLAGS "${COMMON_CXX_FLAGS} /std:c++17 /W4 /arch:AVX2 /fp:fast /MP /DNOMINMAX")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Bin/")

find_package(OpenGL REQUIRED)

add_subdirectory(Engine/Thirdparty/cmake/glad)
add_subdirectory(Engine/Thirdparty/cmake/glfw)
add_subdirectory(Engine/Thirdparty/cmake/glm)
add_subdirectory(Engine/Thirdparty/cmake/assimp)
add_subdirectory(Engine/Thirdparty/cmake/tinyxml2)

add_subdirectory(Engine)
add_subdirectory(Runtime)
add_subdirectory(Editor)