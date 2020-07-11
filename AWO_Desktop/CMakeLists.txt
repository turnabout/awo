cmake_minimum_required(VERSION 3.16)
project(AWO_Desktop C)
set(CMAKE_C_STANDARD 99)

add_executable(${PROJECT_NAME} Src/main.c)

# Use AWO
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        AWO
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ../AWO/Internal
)
