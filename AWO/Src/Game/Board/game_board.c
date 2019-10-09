#include "conf.h"
#include "game_board.h"

#include "Game/Entities/Tile/tile.h"
#include "Game/Entities/Tile/Tile_Factory/tile_factory.h"

typedef Tile** Tile_Row;

struct Game_Board {
    int n_columns;     // Amount of tile columns making up the game board
    int n_lines;       // Amount of tile lines making up the game board

    Tile_Row* tiles;   // Contains all tiles on the game board. tiles[y][x]
    Tile_Factory* tf;  // Factory responsible for getting new tiles

    Unit** units;      // Contains all units on the game board.
    int u_count;       // How many units are on the game board.
};

Game_Board* GB_create(Tiles_Data* td, Game_Clock* gc)
{
    Game_Board* gb = malloc(sizeof(Game_Board));

    gb->n_columns = DEFAULT_GB_WIDTH;
    gb->n_lines   = DEFAULT_GB_HEIGHT;

    gb->tf = TF_create(td, gc);

    // Allocate space for tiles
    gb->tiles = (Tile_Row*)malloc(sizeof(Tile_Row) * gb->n_lines);

    for (int i = 0; i < gb->n_lines; i++) {
        gb->tiles[i] = (Tile**)malloc(sizeof(Tile*) * gb->n_columns);
    }

    // Allocate space for units
    gb->u_count = 0;
    gb->units = malloc(sizeof(Unit*) * MAX_UNITS_PER_ARMY);

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

void GB_fill_tiles(Game_Board* gb, Tile_Type type, Tile_Var var)
{
    // Get tile of given type and variation
    Tile* tile = TF_get_tile(gb->tf, type, var);

    // Loop lines
    for (int y = 0; y < gb->n_lines; y++) {
        // Loop columns
        for (int x = 0; x < gb->n_columns; x++) {
            gb->tiles[y][x] = tile;
        }
    }
}

void GB_edit_tile(Game_Board* gb, Tile_Type type, Tile_Var var, int x, int y)
{
    // Ensure x/y are within the game board tile boundaries
    if (x <= gb->n_columns && y <= gb->n_lines) {
        gb->tiles[y][x] = TF_get_tile(gb->tf, type, var);
    }
}

void GB_get_pointer_board_coords(Game_Board* gb, SDL_Point* pointer, int* x, int* y)
{
    *x = (int)((float)pointer->x / (float)DEFAULT_TILE_DIMENSION);
    *y = (int)((float)pointer->y / (float)DEFAULT_TILE_DIMENSION);
}

Tile_Type GB_get_tile_type_at_coords(Game_Board* gb, int x, int y)
{
    if (x < 0 || x >= gb->n_columns || y < 0 || y >= gb->n_lines) {
        return OOB;
    }

    return tile_get_type(gb->tiles[y][x]);
}

/*
void GB_edit_tile_pointer_coords(Game_Board* gb, Tile_Type type, Tile_Var var, SDL_Point* pointer)
{
    GB_edit_tile(
        gb,
        type,
        var,
        (int)((float)pointer->x / (float)DEFAULT_TILE_DIMENSION),
        (int)((float)pointer->y / (float)DEFAULT_TILE_DIMENSION)
    );
}*/

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

void GB_free(Game_Board* gb)
{
    free(gb);

    // TODO: Free all entities belonging to game board
}