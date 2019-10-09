#pragma once

#include <SDL.h>
#include "Visuals/visuals_data.h"
#include "Game/Entities/Unit/unit.h"
#include "Game/Clock/game_clock.h"

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

// Edits the tile type/variation at given tile x/y index.
void GB_edit_tile(Game_Board* gb, Tile_Type tt, Tile_Var tv, int x, int y);

// Gets the board coordinates at given screen pointer coordinates. Stores in x/y pointer args.
void GB_get_pointer_board_coords(Game_Board* gb, SDL_Point* pointer, int* x, int* y);

// Returns the tile type of the tile at given board coordinates.
Tile_Type GB_get_tile_type_at_coords(Game_Board* gb, int x, int y);

// Fills the game board with tile of the given type/variation.
void GB_fill_tiles(Game_Board* gb, Tile_Type type, Tile_Var var);

// Frees the game board.
void GB_free(Game_Board* gb);