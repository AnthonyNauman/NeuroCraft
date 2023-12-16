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
        src/logger/logger.hpp
        src/ui/main_window.hpp
        src/camera/camera.hpp
        src/camera/camera_controller.hpp
        src/managers/render_manager.hpp
)

set(NEURO_CRAFT_PUBLIC_SOURCES
        src/app.cpp
        src/logger/logger.cpp
        src/ui/main_window.cpp
        src/camera/camera.cpp
        src/camera/camera_controller.cpp
        src/managers/render_manager.cpp
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
        src/graphics/mesh.hpp
        src/graphics/render_commands.hpp
        src/graphics/frame_buffer.hpp

)
set(GRAPHICS_SOURCES
        src/graphics/shader.cpp
        src/graphics/mesh.cpp
        src/graphics/render_commands.cpp
        src/graphics/frame_buffer.cpp

)
add_library(graphics_static STATIC
        ${GRAPHICS_INCLUDES}
        ${GRAPHICS_SOURCES}
)

target_include_directories(imgui_static PUBLIC libs)
target_include_directories(imgui_static PUBLIC libs/imgui)
target_include_directories(graphics_static PUBLIC libs)
target_include_directories(graphics_static PUBLIC libs/imgui)
target_include_directories(graphics_static PUBLIC libs/glm)

add_executable(${PROJECT_NAME} src/main.cpp )

add_subdirectory(libs/glfw ${CMAKE_CURRENT_BINARY_DIR}/libs/glfw)
add_subdirectory(libs/nlohmann_json ${CMAKE_CURRENT_BINARY_DIR}/libs/nlohmann_json)
add_subdirectory(libs/glad ${CMAKE_CURRENT_BINARY_DIR}/libs/glad)
add_subdirectory(libs/glm ${CMAKE_CURRENT_BINARY_DIR}/libs/glm)
add_subdirectory(libs/termcolor ${CMAKE_CURRENT_BINARY_DIR}/libs/termcolor)
target_link_libraries(imgui_static PRIVATE glad glfw)
target_link_libraries(graphics_static PRIVATE glad glfw glm)
target_link_libraries(neuro_craft_static PUBLIC 
            glfw
            nlohmann_json
            glad
            imgui_static
            graphics_static
            termcolor
            glm
)



target_link_libraries(${PROJECT_NAME} PRIVATE 
            neuro_craft_static
)
