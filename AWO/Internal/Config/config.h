#pragma once

// Resource paths
#define RESOURCES_PATH AWO_PROJECT_DIR "/Resources/"

#ifdef __EMSCRIPTEN__
    #define SHADERS_DIR "Shaders_ES"
#else
    #define SHADERS_DIR "Shaders"
#endif

#define TEXTURES_PATH RESOURCES_PATH "Textures/"
#define DATA_PATH     RESOURCES_PATH "Data/"
#define FONTS_PATH    RESOURCES_PATH "Fonts/"
#define SHADERS_PATH  RESOURCES_PATH SHADERS_DIR

#define GRID_SHADER "grid"
#define BASIC_SHADER "basic"

#define SPRITE_SHEET_PATH   TEXTURES_PATH "spritesheet.png"
#define GAME_DATA_JSON_PATH DATA_PATH     "game_data.json"
#define DIALOGUE_FONT_PATH  FONTS_PATH    "aw2-gba.ttf"

// Macro for getting a shader's full path
#define VERTEX_SHADER_PATH(shader)   SHADERS_PATH shader ".vert"
#define FRAGMENT_SHADER_PATH(shader) SHADERS_PATH shader ".frag"

// Window configuration
#define DEFAULT_WINDOW_TITLE "AWO"
#define DEFAULT_WINDOW_WIDTH 1440
#define DEFAULT_WINDOW_HEIGHT 960

// Game speed
#define FPS 60
#define FRAME_TIME 0.01666666666f

// Default size of an entity (pixels)
#define DEFAULT_ENTITY_SIZE 16

// Default dimensions of game board (tiles)
#define DEFAULT_GAME_BOARD_WIDTH  5
#define DEFAULT_GAME_BOARD_HEIGHT 3

// Clear color
#define GAME_CLEAR_COLOR_R 255
#define GAME_CLEAR_COLOR_G 239
#define GAME_CLEAR_COLOR_B 239
#define GAME_CLEAR_COLOR_A 255

// Stages
#define HQS_PER_ARMY 1
#define MAX_PROPERTIES_PER_PLAYER 50

// Units
#define MAX_UNITS_PER_PLAYER 50

// Min/max amount of players for a game
#define MIN_PLAYER_COUNT 2
#define MAX_PLAYER_COUNT 4

// Sprite batch
#define MAX_SPRITE_BATCH_ELEMENTS 10
