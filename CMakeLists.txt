cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PROJ_VERSION 0.1.0.0)
add_compile_definitions(PROJECT_VERSION="${PROJ_VERSION}")

project(NeuroCraft VERSION ${PROJ_VERSION} LANGUAGES CXX)
add_compile_definitions(PROJECT_NAME="${PROJECT_NAME}")


set(NEURO_CRAFT_PUBLIC_INCLUDES 
        src/app.hpp
        src/logger.hpp
        src/ui/main_window.hpp
)

set(NEURO_CRAFT_PUBLIC_SOURCES
        src/app.cpp
        src/ui/main_window.cpp
)

add_library(neuro_craft_static STATIC 
    ${NEURO_CRAFT_PUBLIC_INCLUDES}
    ${NEURO_CRAFT_PUBLIC_SOURCES}
)


set(IMGUI_INCLUDES 
        libs/imgui/imgui.h
        libs/imgui/backends/imgui_impl_glfw.h
        libs/imgui/backends/imgui_impl_opengl3.h
        # libs/imgui/backends/imgui_impl_opengl3_loader.h
)

set(IMGUI_SOURCES
        libs/imgui/imgui.cpp
        libs/imgui/backends/imgui_impl_glfw.cpp
        libs/imgui/backends/imgui_impl_opengl3.cpp
        # libs/imgui/backends/imgui_impl_opengl3_loader.cpp
        libs/imgui/imgui_demo.cpp
        libs/imgui/imgui_draw.cpp
        libs/imgui/imgui_tables.cpp
        libs/imgui/imgui_widgets.cpp
)

add_library(imgui_static STATIC 
    ${IMGUI_INCLUDES}
    ${IMGUI_SOURCES}
)

set(GRAPHICS_INCLUDES
        src/graphics/shader.hpp

)
set(GRAPHICS_SOURCES
        src/graphics/shader.cpp

)
add_library(graphics_static STATIC
        ${GRAPHICS_INCLUDES}
        ${GRAPHICS_SOURCES}
)

target_include_directories(imgui_static PUBLIC libs)
target_include_directories(imgui_static PUBLIC libs/imgui)
target_include_directories(graphics_static PUBLIC libs)
target_include_directories(graphics_static PUBLIC libs/imgui)
target_include_directories(graphics_static PUBLIC libs/spdlog)

add_executable(${PROJECT_NAME} src/main.cpp )

add_subdirectory(libs/glfw ${CMAKE_CURRENT_BINARY_DIR}/libs/glfw)
add_subdirectory(libs/spdlog ${CMAKE_CURRENT_BINARY_DIR}/libs/spdlog)
add_subdirectory(libs/glad ${CMAKE_CURRENT_BINARY_DIR}/libs/glad)
target_link_libraries(imgui_static PRIVATE glad glfw)
target_link_libraries(graphics_static PRIVATE glad glfw spdlog)
target_link_libraries(neuro_craft_static PUBLIC 
            glfw
            spdlog
            glad
            imgui_static
            graphics_static
)



target_link_libraries(${PROJECT_NAME} PRIVATE 
            neuro_craft_static
)
