#pragma once
#include <SDL.h>
#include "SDL_FontCache.h"

#include "Visuals/visuals_data.h"

#include "Game/Entities/Tile/enums.h"
#include "Game/Clock/game_clock.h"
#include "Game/Board/game_board.h"
#include "Game/Editor/editor.h"
#include "Game/Input_State/input_state.h"
#include "Game/game_arg_enums.h"

// Holds components required to run the game.
typedef struct Game
{
    SDL_Window*   win;
    SDL_Renderer* rend;
    SDL_Surface*  surface;
    SDL_Texture*  ss;
    Units_Data*   ud;
    Tiles_Data*   td;
    Game_Clock*   clock;
    FC_Font*      font;
    Mouse_State*  mouse_state;
    Editor*       editor;

    Uint32 w; // Current game width
    Uint32 h; // Current game height

    // Tile/unit textures
    SDL_Texture* tile_textures[WEATHER_COUNT];

    // State
    Weather current_weather; // Currently active weather

    // Game board
    Game_Board* board;
} Game;

// Initializes the game and populates the game instance pointed at by `game`.
// Returns ERR if an error occured, or OK.
Game* init_game(Game_Arg_Weathers weathers, int w, int h);

// Exits the game and cleans up resources.
void exit_game(Game* game);

// Runs the main game loop continuously.

#ifdef __EMSCRIPTEN__
void run_game(void* game);
#else
void run_game(Game* game);
#endif
