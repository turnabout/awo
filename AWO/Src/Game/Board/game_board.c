#include <stdlib.h>

#include "conf.h"
#include "Game/Board/game_board.h"
#include "Game/Entity/Tile/Factory/tile_factory.h"

typedef Tile** Tile_Row;

struct Game_Board {
    // Amount of tile columns and lines making up the game board
    int n_columns, n_lines;

    // Contains all tiles on the game board. tiles[y][x]
    Tile_Row* tiles;

    // Factory responsible for getting new tiles
    Tile_Factory* tile_factory;
};

Game_Board* create_game_board(
    Tiles_Data* tiles_data, 
    Game_Clock* game_clock, 
    int width, 
    int height
)
{
    Game_Board* game_board = malloc(sizeof(Game_Board));

    game_board->n_columns = width;
    game_board->n_lines   = height;

    game_board->tile_factory = create_tile_factory(tiles_data, game_clock);

    // Allocate space for tiles
    game_board->tiles = (Tile_Row*)malloc(sizeof(Tile_Row) * game_board->n_lines);

    for (int i = 0; i < game_board->n_lines; i++) {
        game_board->tiles[i] = (Tile**)malloc(sizeof(Tile*) * game_board->n_columns);
    }

    return game_board;
}

void update_game_board(Game_Board* game_board)
{
}

void draw_game_board(Game_Board* game_board, Sprite_Batch* sprite_batch)
{
    // Draw tiles
    // Loop lines
    for (int y = 0; y < game_board->n_lines; y++) {

        // Loop columns
        for (int x = 0; x < game_board->n_columns; x++) {
            if (game_board->tiles[y][x] != NULL) {
                /*
                tile_draw(
                    game_board->tiles[y][x], 
                    rend, 
                    tile_texture, 
                    x * DEFAULT_TILE_DIMENSION,
                    y * DEFAULT_TILE_DIMENSION
                );
                */
            }
        }
    }
}

void fill_game_board_tiles(Game_Board* game_board, Tile_Type type, Tile_Variation variation)
{
    // Get tile of given type and variation
    Tile* tile = get_tile_factory_tile(game_board->tile_factory, type, variation);

    // Loop lines
    for (int y = 0; y < game_board->n_lines; y++) {
        // Loop columns
        for (int x = 0; x < game_board->n_columns; x++) {
            game_board->tiles[y][x] = tile;
        }
    }
}

void edit_game_board_tile(Game_Board* gb, Tile_Type type, Tile_Variation var, int x, int y)
{
    // Ensure x/y are within the game board tile boundaries
    if (x <= gb->n_columns && y <= gb->n_lines) {
        gb->tiles[y][x] = get_tile_factory_tile(gb->tile_factory, type, var);
    }
}

Tile_Type get_game_board_tile_type(Game_Board* gb, int x, int y)
{
    if (x < 0 || x >= gb->n_columns || y < 0 || y >= gb->n_lines) {
        return OOB;
    }

    return get_tile_type(gb->tiles[y][x]);
}

void free_game_board(Game_Board* game_board)
{
    free_tile_factory(game_board->tile_factory);
    free(game_board);
}

void get_game_board_screen_coordinate_indices(
    int screen_x, 
    int screen_y, 
    int* board_x, 
    int* board_y
)
{
    *board_x = (int)((float)screen_x / (float)DEFAULT_TILE_DIMENSION);
    *board_y = (int)((float)screen_y / (float)DEFAULT_TILE_DIMENSION);
}
