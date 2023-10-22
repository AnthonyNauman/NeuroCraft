cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PROJ_VERSION 0.1.0.0)
add_compile_definitions(PROJECT_VERSION="${PROJ_VERSION}")

project(NeuroCraft VERSION ${PROJ_VERSION} LANGUAGES CXX)
add_compile_definitions(PROJECT_NAME="${PROJECT_NAME} ")


set(NEURO_CRAFT_PUBLIC_INCLUDES 
        src/app.hpp
        src/logger.hpp
)

set(NEURO_CRAFT_PUBLIC_SOURCES
        src/app.cpp
)

add_library(neuro_craft_static STATIC 
    ${NEURO_CRAFT_PUBLIC_INCLUDES}
    ${NEURO_CRAFT_PUBLIC_SOURCES}
)




add_executable(${PROJECT_NAME} src/main.cpp )

add_subdirectory(libs/glfw ${CMAKE_CURRENT_BINARY_DIR}/libs/glfw)
add_subdirectory(libs/spdlog ${CMAKE_CURRENT_BINARY_DIR}/libs/spdlog)
target_link_libraries(neuro_craft_static PUBLIC 
            glfw
            spdlog
)



target_link_libraries(${PROJECT_NAME} PRIVATE 
            neuro_craft_static
)
