cmake_minimum_required(VERSION 3.16)
project(AWO C)

set(CMAKE_C_STANDARD 99)

# Add library with sources
set(SOURCES
        AWO/Internal/GL_Helpers/glad.c
        AWO/Libs/Game_Window/game_window.c
        )

add_library(${PROJECT_NAME} STATIC ${SOURCES})

## Add GLFW & GL dependencies
find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

# Add other dependencies
# TODO

# Link
target_link_libraries(${PROJECT_NAME} glfw OpenGL::GL ${CMAKE_DL_LIBS})

# Set include directories
target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${PROJECT_SOURCE_DIR}/AWO
        ${PROJECT_SOURCE_DIR}/AWO/Internal
        ${PROJECT_SOURCE_DIR}/AWO/Libs
        )
