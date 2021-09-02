project(Editor)

add_subdirectory(Engine)
include_directories(Engine/Source)

add_executable(${PROJECT_NAME}
    Source/App.cpp
)

target_link_libraries(${PROJECT_NAME} FractalEngine)