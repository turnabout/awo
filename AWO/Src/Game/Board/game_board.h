#pragma once
#include <SDL.h>
#include "Game/Entities/Unit/unit.h"
#include "Game/game_arg_enums.h"

// Represents the game board used by players during gameplay. Includes all units, tiles, etc.
typedef struct Game_Board Game_Board;

// Creates the game board.
Game_Board* GB_create(Tiles_Data* td, Game_Clock* gc);

// Updates the game board and its entities.
void GB_update(Game_Board* gb);

// Adds a unit to the game board
void GB_add_unit(Game_Board* gb, Unit* u);

// Draws entities visible on the game board.
void GB_draw(Game_Board* gb, SDL_Renderer* rend, SDL_Texture* tile_texture);

// Edits tile type/variation at given tile x/y index.
void GB_edit_tile(Game_Board* gb, Tile_Type tt, Tile_Var tv, int x, int y);

// Fills the game board with tile of the given type/variation.
void GB_fill(Game_Board* gb, Game_Clock* gc, Tile_Type tt, Tile_Var tv);

// Frees the game board.
void GB_free(Game_Board* gb);