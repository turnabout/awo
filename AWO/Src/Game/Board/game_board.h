#pragma once
#include <SDL.h>
#include "Game/Entities/Unit/unit.h"
#include "Game/game_arg_enums.h"

// Represents the game board used by players during gameplay. Includes all units, tiles, etc.
typedef struct Game_Board Game_Board;

// Creates the game board.
Game_Board* GB_create();

// Updates the game board and its entities.
void GB_update(Game_Board* gb);

// Adds a unit to the game board
void GB_add_unit(Game_Board* gb, Unit* u);

// Draws entities visible on the game board.
void GB_draw(Game_Board* gb, SDL_Renderer* rend, SDL_Texture* tile_texture);

// Fills the game board with the given tile type/variation.
void GB_fill(
    Game_Board* gb,
    Game_Clock* gc,
    Tiles_Data* td,
    Tile_Type tt,
    Tile_Var tv
);

// Frees the game board.
void GB_free(Game_Board* gb);