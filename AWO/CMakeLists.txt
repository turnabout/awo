cmake_minimum_required(VERSION 3.16)
project(AWO C)

set(CMAKE_C_STANDARD 99)

# Add library with sources
add_library(${PROJECT_NAME} STATIC
        Internal/GL_Helpers/glad.c
        Internal/Linked_List/linked_list.c
        Internal/Linked_List/list_entry.c
        Libs/Game_Window/game_window.c
        Libs/Game_Message/game_message.c
        Libs/Game_Message/game_message_simple.c
)

## Add GLFW & GL dependencies
find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

# Add other dependencies
find_package(cJSON CONFIG REQUIRED)
# TODO

# Link dependencies
target_link_libraries(${PROJECT_NAME}
    glfw
    OpenGL::GL
    cjson
    ${CMAKE_DL_LIBS}
)

# Set include directories
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/Include
    PRIVATE
        ${PROJECT_SOURCE_DIR}/Internal
        ${PROJECT_SOURCE_DIR}/Libs
)
