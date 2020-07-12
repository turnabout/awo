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
        Libs/Game_Data/game_data.c
        Libs/Game_Data/Unit_Data/unit_data_access.c
        Libs/Game_Data/Unit_Data/unit_data_creation.c
        Libs/Game_Data/UI_Data/UI_data_access.c
        Libs/Game_Data/UI_Data/UI_data_creation.c
        Libs/Game_Data/Tile_Data/tile_variation_data_access.c
        Libs/Game_Data/Tile_Data/tile_placement_rule_access.c
        Libs/Game_Data/Tile_Data/tile_data.c
        Libs/Game_Data/Tile_Data/tile_auto_var_access.c
        Libs/Game_Data/Tile_Data/Tile_Variation_Data/tile_variation_data.c
        Libs/Game_Data/Tile_Data/Tile_Type_Data/tile_type_data.c
        Libs/Game_Data/Tile_Data/Tile_Placement_Rule/tile_placement_rule.c
        Libs/Game_Data/Tile_Data/Tile_Placement_Rule/tile_placement_rule_set.c
        Libs/Game_Data/Tile_Data/Tile_Auto_Var/tile_auto_var.c
        Libs/Game_Data/Sprite_Sheet_Data/sprite_sheet_data.c
        Libs/Game_Data/Property_Data/property_data.c
        Libs/Game_Data/Property_Data/property_data_access.c
        Libs/Game_Data/Palette_Data/palette_data.c
        Libs/Game_Data/Palette_Data/palette_data_access.c
        Libs/Game_Data/Palette_Data/palette_NDC_index.c
        Libs/Game_Data/Frame/frame.c
        Libs/Game_Data/CO_Data/CO_data_access.c
        Libs/Game_Data/CO_Data/CO_data_creation.c
        Libs/Game_Data/Clock_Data/clock_data.c
        Libs/Game_Data/Animation/animation.c
)

# Add preprocessor macro definitions
add_compile_definitions(AWO_PROJECT_DIR=${PROJECT_SOURCE_DIR})

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
