/**
 * Project-wide configuration.
 */

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Utilities/macros.h"

// Resource paths
#define RESOURCES_PATH SOLUTION_DIR "AWO/Resources/"

#define TEXTURES_PATH RESOURCES_PATH "Textures/"
#define DATA_PATH     RESOURCES_PATH "Data/"
#define FONTS_PATH    RESOURCES_PATH "Fonts/"
#define SHADERS_PATH  RESOURCES_PATH SHADERS_DIR

#define SPRITE_SHEET_PATH   TEXTURES_PATH "spritesheet.png"
#define GAME_DATA_JSON_PATH DATA_PATH     "game_data.json"
#define DIALOGUE_FONT_PATH  FONTS_PATH    "aw2-gba.ttf"

// Window configuration
#define DEFAULT_WINDOW_TITLE "AWO"
#define DEFAULT_WINDOW_WIDTH 1440
#define DEFAULT_WINDOW_HEIGHT 960

// Game speed
#define FPS 60
#define FRAME_TIME 1.0f / FPS

// Game clock
#define GAME_CLOCK_FRAMES_TO_TICK  2 // How many frames it takes it tick the game clock
#define GAME_CLOCK_TICK_MAX       45 // Game clock's maximum tick value before resetting

// Default size of a tile (pixels)
#define DEFAULT_TILE_SIZE 16

// Default dimensions of game board (tiles)
#define DEFAULT_GAME_BOARD_WIDTH  5
#define DEFAULT_GAME_BOARD_HEIGHT 3

// Clear color
#define GAME_CLEAR_COLOR_R 255
#define GAME_CLEAR_COLOR_G 239
#define GAME_CLEAR_COLOR_B 239
#define GAME_CLEAR_COLOR_A 255

#define MAX_SPRITE_BATCH_ELEMENTS 2000

// Min/max amount of players for a game
#define MIN_PLAYER_COUNT 2
#define MAX_PLAYER_COUNT 4

// Stages
#define HQS_PER_ARMY 1
#define MAX_PROPERTIES_PER_PLAYER 50
#define MAX_LOADED_STAGE_COUNT 16

// Game Camera
#define DEFAULT_CAMERA_ZOOM (DEFAULT_TILE_SIZE * 2)
#define DEFAULT_CAMERA_X 0
#define DEFAULT_CAMERA_Y 0

#define MIN_ZOOM_VALUE 16.0f
#define MAX_ZOOM_VALUE 40.0f
