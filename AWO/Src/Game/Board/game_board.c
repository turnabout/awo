#include "conf.h"
#include "Game/Entities/Unit/unit.h"
#include "Game/Entities/Tile/tile.h"
#include "game_board.h"

#pragma warning( disable : 6011 )

typedef Tile** Tile_Row;

struct Game_Board {
    int w, h;        // Dimensions of full game board, in tiles
    Unit** units;    // Contains all units on the game board.
    Tile_Row* tiles; // Contains all tiles on the game board.
    int u_count;     // How many units are on the game board.
};

Game_Board* GB_create()
{
    Game_Board* gb = malloc(sizeof(Game_Board));

    gb->w = DEFAULT_GB_WIDTH;
    gb->h = DEFAULT_GB_HEIGHT;

    // Allocate space for tiles
    gb->tiles = malloc(sizeof(Tile_Row) * gb->h);

    for (int i = 0; i < gb->h; i++) {
        gb->tiles[i] = malloc(sizeof(Tile*) * gb->w);
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

void GB_fill(
    Game_Board* gb,
    Game_Clock* gc,
    Tiles_Data* td,
    SDL_Texture* src_texture,
    tile_type tt,
    tile_var tv
)
{
    // Columns
    for (int i = 0; i < gb->h; i++) {
        // Rows
        for (int j = 0; j < gb->w; j++) {
            gb->tiles[i][j] = tile_create(
                gc,
                td,
                src_texture,
                tt,
                tv,
                i * DEFAULT_TILE_DIMENSION,
                j * DEFAULT_TILE_DIMENSION
            );
        }
    }
}

void GB_draw(Game_Board* gb, SDL_Renderer* rend)
{
    // Draw tiles
    // Columns
    for (int i = 0; i < gb->h; i++) {
        // Rows
        for (int j = 0; j < gb->w; j++) {
            if (gb->tiles[i][j] != NULL) {
                tile_draw(gb->tiles[i][j], rend);
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