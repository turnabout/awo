#include "conf.h"
#include "Game/Entities/Tile/tile.h"
#include "Game/Board/Tiles_Map/tiles_map.h"

#include "game_board.h"

typedef Tile** Tile_Row;

struct Game_Board {
    int n_columns, n_lines; // Dimensions of full game board, in tiles

    Tile_Row* tiles;        // Contains all tiles on the game board. tiles[y][x]
    Tiles_Map* tiles_map;   // Map holding every unique `Tile`
    Tiles_Data* td;         // Reference to the game's tiles' data.

    Unit** units;           // Contains all units on the game board.
    int u_count;            // How many units are on the game board.

    Game_Clock* gc;         // Reference to the game clock.
};

Game_Board* GB_create(Tiles_Data* td, Game_Clock* gc)
{
    Game_Board* gb = malloc(sizeof(Game_Board));

    gb->td = td;
    gb->gc = gc;

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

void GB_fill(Game_Board* gb, Game_Clock* gc, Tile_Type tt, Tile_Var tv)
{
    // Attempt to get existing tile from map
    Tile* tile = TM_get_map_tile(gb->tiles_map, tt, tv);

    // If nonexistent, make new one and add to map
    if (tile == NULL) {
        tile = tile_create(gc, gb->td, tt, tv);
        TM_add_map_tile(gb->tiles_map, tile, tt, tv);
    }

    // Loop lines
    for (int y = 0; y < gb->n_lines; y++) {
        // Loop columns
        for (int x = 0; x < gb->n_columns; x++) {
            gb->tiles[y][x] = tile;
        }
    }
}

void GB_draw(Game_Board* gb, SDL_Renderer* rend, SDL_Texture* tile_texture)
{
    // Draw tiles
    // Loop lines
    for (int y = 0; y < gb->n_lines; y++) {

        // Loop columns
        for (int x = 0; x < gb->n_columns; x++) {
            if (gb->tiles[y][x] != NULL) {
                int xPos = x * DEFAULT_TILE_DIMENSION;
                int yPos = y * DEFAULT_TILE_DIMENSION;

                tile_draw(
                    gb->tiles[y][x], 
                    rend, 
                    tile_texture, 
                    x * DEFAULT_TILE_DIMENSION,
                    y * DEFAULT_TILE_DIMENSION
                );
            }
        }
    }

    // Draw units
    for (int i = 0; i < gb->u_count; i++) {
        unit_draw(gb->units[i], rend);
    }
}

void GB_edit_tile(Game_Board* gb, Tile_Type tt, Tile_Var tv, int x, int y)
{
    // Attempt to get existing tile of given type/variation
    Tile* tile = TM_get_map_tile(gb->tiles_map, tt, tv);

    // If nonexistent, make new one and add to map
    if (tile == NULL) {
        tile = tile_create(gb->gc, gb->td, tt, tv);
        TM_add_map_tile(gb->tiles_map, tile, tt, tv);
    }

    gb->tiles[y][x] = tile;
}

void GB_free(Game_Board* gb)
{
    free(gb);

    // TODO: Free all entities belonging to game board
}