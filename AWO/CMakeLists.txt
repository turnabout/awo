cmake_minimum_required(VERSION 3.16)
project(AWO C)

set(CMAKE_C_STANDARD 99)

# Add library with sources
file(GLOB_RECURSE AWO_SOURCES *.c)

message("Herro: ${AWO_SOURCES}")

add_library(${PROJECT_NAME} STATIC ${AWO_SOURCES})

# Add preprocessor macro definitions
add_compile_definitions(AWO_PROJECT_DIR="${PROJECT_SOURCE_DIR}")

## Add GLFW & GL dependencies
find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

# Add other dependencies
find_package(cJSON CONFIG REQUIRED)
find_package(cglm CONFIG REQUIRED)
# TODO

# Link dependencies
target_link_libraries(${PROJECT_NAME}
        glfw
        OpenGL::GL
        cjson
        cglm
        ${CMAKE_DL_LIBS}
)

# Set include directories
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/Include
    PRIVATE
        ${PROJECT_SOURCE_DIR}/External
        ${PROJECT_SOURCE_DIR}/Internal
        ${PROJECT_SOURCE_DIR}/Libs
)
