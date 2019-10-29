#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

/**
 * Project-wide configuration.
 */

// Resource paths
#define RESOURCES_PATH    "Resources/"

#define TEXTURES_PATH RESOURCES_PATH "Textures/"
#define DATA_PATH     RESOURCES_PATH "Data/"
#define SHADERS_PATH  RESOURCES_PATH "Shaders/"
#define FONTS_PATH    RESOURCES_PATH "Fonts/"

#define SPRITE_SHEET_PATH   TEXTURES_PATH "spritesheet.png"
#define GAME_DATA_JSON_PATH DATA_PATH "visuals.json"
#define DIALOGUE_FONT_PATH  FONTS_PATH "aw2-gba.ttf"

// Window configuration
#define DEFAULT_WINDOW_TITLE "AWO"
#define DEFAULT_WINDOW_WIDTH 1440
#define DEFAULT_WINDOW_HEIGHT 960

// Game speed
#define FPS 60
#define FRAME_TIME 1.0f / FPS

// Game clock
#define GAME_CLOCK_FRAMES_TO_TICK 60 // How many frames it takes it tick the game clock
#define GAME_CLOCK_TICK_MAX       45 // Game clock's maximum tick value before resetting

// Default dimension of a tile (pixels)
#define DEFAULT_TILE_DIMENSION 16

// Default dimensions of game board (tiles)
#define DEFAULT_GB_WIDTH  40
#define DEFAULT_GB_HEIGHT 20

// Starting background color when first initializing game
#define DEFAULT_GAME_BG_R 255
#define DEFAULT_GAME_BG_G 239
#define DEFAULT_GAME_BG_B 239
#define DEFAULT_GAME_BG_A 255

#define MAX_SPRITE_BATCH_ELEMENTS 200
