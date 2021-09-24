project(Editor)

add_subdirectory(../Engine)
include_directories(../Engine/Source)

file(GLOB_RECURSE EditorSources "Source/**.cpp" "Source/**.h")

add_executable(${PROJECT_NAME} ${EditorSources})

target_link_libraries(${PROJECT_NAME} FractalEngine)
