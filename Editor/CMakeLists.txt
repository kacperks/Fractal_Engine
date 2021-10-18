project(Editor)

if (WIN32)
    set(PLATFORM "Windows")
endif (WIN32)

if(UNIX AND NOT APPLE)
    set(PLATFORM "Linux")
endif()

include_directories(Source)
include_directories(../Engine/Source)
include_directories(../Engine/Thirdparty/includes)

file(GLOB_RECURSE EditorSources "Source/**.cpp" "Source/**.h")

add_executable(${PROJECT_NAME} ${EditorSources})

if(PLATFORM STREQUAL "Linux")
target_link_libraries(${PROJECT_NAME} -lFractalEngine)
target_link_libraries(${PROJECT_NAME} -lGL)
target_link_libraries(${PROJECT_NAME} -lglfw)
target_link_libraries(${PROJECT_NAME} -lglad)
target_link_libraries(${PROJECT_NAME} -lassimp)
target_link_libraries(${PROJECT_NAME} -ltinyxml2)
endif()

if(PLATFORM STREQUAL "Windows")
target_link_libraries(${PROJECT_NAME} FractalEngine)
target_link_libraries(${PROJECT_NAME} opengl32)
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} tinyxml2)
target_link_libraries(${PROJECT_NAME} assimp)
endif()