#pragma once

/**
 * Project-wide configuration.
 */

// Resource paths
#define SPRITE_SHEET_PATH "Resources/spritesheet.png"
#define JSON_PATH         "Resources/visuals.json"
#define FONT_PATH         "Resources/Font/aw2-gba.ttf"

// Window configuration
#define GAME_TITLE "AWO"
#define SCREEN_WIDTH 1440
#define SCREEN_HEIGHT 960
#define SDL_WINDOW_FLAGS SDL_WINDOW_OPENGL

#define X1_SCREEN_WIDTH  1440
#define X1_SCREEN_HEIGHT 960

// SDL initialization flags
#define SDL_INIT_FLAGS SDL_INIT_VIDEO | SDL_INIT_TIMER
#define REND_INIT_FLAGS SDL_RENDERER_ACCELERATED

// Return values on success/failure
#define ERR -1
#define OK  0

// Font conf
#define FONT_SIZE 24

// Game speed
#define FPS 60
#define SCREEN_TICKS_PER_FRAME 1000 / FPS

// Game clock
#define GAME_CLOCK_MAX_ACCUM_MS SCREEN_TICKS_PER_FRAME * 2
#define GAME_CLOCK_TICK_MAX 45

// Default dimension of a tile, in pixels
#define DEFAULT_TILE_DIMENSION 16

// Default dimensions of game board, in tiles
#define DEFAULT_GB_WIDTH  40
#define DEFAULT_GB_HEIGHT 20

// Max amount of units for each player
#define MAX_UNITS_PER_ARMY 50

// Editor configuration
#define EDITOR_UI_R     0
#define EDITOR_UI_G     0
#define EDITOR_UI_B     0
#define EDITOR_UI_ALPHA 130
#define EDITOR_FONT_SIZE 20

// Tile selector
#define TILE_SELECTOR_WIDTH   DEFAULT_TILE_DIMENSION * 2
#define TILE_SELECTOR_PADDING TILE_SELECTOR_WIDTH / 8
#define TILE_SELECTOR_X       TILE_SELECTOR_PADDING
#define TILE_SELECTOR_Y       TILE_SELECTOR_PADDING
