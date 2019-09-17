#pragma once

/**
 * Project-wide configuration definitions.
 */

// Resource paths
#define SPRITE_SHEET_PATH "Resources/spritesheet.png"
#define JSON_PATH         "Resources/visuals.json"

// Window configuration
#define GAME_TITLE "SDL2 Window"
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 640
#define SDL_WINDOW_FLAGS SDL_WINDOW_OPENGL

// SDL initialization flags
#define SDL_INIT_FLAGS SDL_INIT_VIDEO | SDL_INIT_TIMER
#define REND_INIT_FLAGS SDL_RENDERER_ACCELERATED

// Return values on success/failure
#define ERR -1
#define OK  0

// Game speed
#define FPS 60
#define SCREEN_TICKS_PER_FRAME 1000 / FPS