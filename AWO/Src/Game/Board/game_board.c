#include "conf.h"
#include "Game/Entities/Tile/tile.h"
#include "Game/Board/Tiles_Map/tiles_map.h"

#include "game_board.h"

typedef Tile** Tile_Row;

struct Game_Board {
    int n_columns, n_lines; // Dimensions of full game board, in tiles
    Unit** units;           // Contains all units on the game board.
    Tile_Row* tiles;        // Contains all tiles on the game board.
    int u_count;            // How many units are on the game board.
    Tiles_Map* tiles_map;   // Map holding every unique `Tile`
};

Game_Board* GB_create()
{
    Game_Board* gb = malloc(sizeof(Game_Board));

    gb->n_columns = DEFAULT_GB_WIDTH;
    gb->n_lines   = DEFAULT_GB_HEIGHT;

    // Allocate space for tiles
    gb->tiles = (Tile_Row*)malloc(sizeof(Tile_Row) * gb->n_lines);

    for (int i = 0; i < gb->n_lines; i++) {
        gb->tiles[i] = (Tile**)malloc(sizeof(Tile*) * gb->n_columns);
    }

    // Allocate space for units
    gb->u_count = 0;
    gb->units = malloc(sizeof(Unit*) * MAX_UNITS_PER_ARMY);

    // Create map for holding unique tiles
    gb->tiles_map = TM_create();

    return gb;
}

void GB_add_unit(Game_Board* gb, Unit* u)
{
    gb->units[gb->u_count] = u;
    gb->u_count++;
}

void GB_update(Game_Board* gb)
{
}

void GB_change_tile(int tile_x, int tile_y)
{
}

void GB_fill(Game_Board* gb, Game_Clock* gc, Tiles_Data* td, Tile_Type tt, Tile_Var tv)
{
    // Attempt to get existing tile from map
    Tile* tile = TM_get_map_tile(gb->tiles_map, tt, tv);

    // If nonexistent, make new one and add to map
    if (tile == NULL) {
        tile = tile_create(gc, td, tt, tv);
        TM_add_map_tile(gb->tiles_map, tile, tt, tv);
    }

    // Loop lines
    for (int i = 0; i < gb->n_lines; i++) {
        // Loop columns
        for (int j = 0; j < gb->n_columns; j++) {
            gb->tiles[i][j] = tile;
        }
    }
}

void GB_draw(Game_Board* gb, SDL_Renderer* rend, SDL_Texture* tile_texture)
{
    // Draw tiles
    // Loop lines
    for (int i = 0; i < gb->n_lines; i++) {

        // Loop columns
        for (int j = 0; j < gb->n_columns; j++) {
            if (gb->tiles[i][j] != NULL) {
                tile_draw(
                    gb->tiles[i][j], 
                    rend, 
                    tile_texture, 
                    j * DEFAULT_TILE_DIMENSION,
                    i * DEFAULT_TILE_DIMENSION
                );
            }
        }
    }

    // Draw units
    for (int i = 0; i < gb->u_count; i++) {
        unit_draw(gb->units[i], rend);
    }
}

void GB_free(Game_Board* gb)
{
    free(gb);

    // TODO: Free all entities belonging to game board
}