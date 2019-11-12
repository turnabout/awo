#include <stdlib.h>

#include "conf.h"
#include "Game/Board/game_board.h"
#include "Game/Entity/Tile/Factory/tile_factory.h"
#include "Game/Data/Palette/palette.h"

typedef Tile** Tile_Row;

// An entry representing a tile within the game board.
typedef struct Tile_Entry {

    // Pointer to the tile itself.
    Tile* tile;

    // Where the tile entry is located in the game board.
    Uint8 x, y;

} Tile_Entry;

// A list of entries representing a clock tile within the game board.
typedef struct Tile_Entry_List {

    // How many tile entries are in this list.
    int count;

    // The tile entries.
    Tile_Entry* tile_entries;

} Tile_Entry_List;

struct Game_Board {
    // Amount of tile columns and lines making up the game board
    int width, height;

    // Contains all tiles on the game board. tiles[board_y][board_x]
    Tile_Row* tiles_grid;

    // Factory responsible for getting new tiles
    Tile_Factory* tile_factory;

    // Indices of the currently active tile and fog tile palettes.
    GLfloat active_tile_palette_index, active_fog_tile_palette_index;

    // Lists of every clock tiles, sorted by their animation clock data.
    // All subscribe to the game clock publisher.
    Tile_Entry_List* clock_tiles_subscriber[ANIMATION_CLOCK_COUNT][MINIMAL_ANIMATION_SUB_CLOCK_COUNT];
};

Game_Board* create_game_board(
    Tiles_Data* tiles_data, 
    Game_Clock* game_clock, 
    int width, 
    int height
)
{
    Game_Board* game_board = malloc(sizeof(Game_Board));

    game_board->width = width;
    game_board->height   = height;

    game_board->tile_factory = create_tile_factory(tiles_data, game_clock);

    game_board->active_tile_palette_index = get_active_tile_palette_index(0);
    game_board->active_fog_tile_palette_index = get_active_tile_palette_index(1);

    // Allocate space for tiles
    game_board->tiles_grid = (Tile_Row*)malloc(sizeof(Tile_Row) * game_board->height);

    for (int i = 0; i < game_board->height; i++) {
        game_board->tiles_grid[i] = (Tile**)malloc(sizeof(Tile*) * game_board->width);
    }

    // Allocate space for game clock tiles subscriber
    for (int i = 0; i < ANIMATION_CLOCK_COUNT; i++) {
        for (int j = 0; j < MINIMAL_ANIMATION_SUB_CLOCK_COUNT; j++) {
            game_board->clock_tiles_subscriber[i][j] = malloc(sizeof(Tile_Entry_List));
            game_board->clock_tiles_subscriber[i][j]->count = 0;
        }
    }

    return game_board;
}

void update_game_board(Game_Board* game_board)
{
}

void render_game_board(Game_Board* game_board, Game_Renderer* renderer)
{
    /*
    for (int y = (game_board->height - 1); y >= 0; y--) {
        for (int x = (game_board->width - 1); x >= 0; x--) {
            render_tile(
                game_board->tiles_grid[y][x], 
                renderer, 
                x, 
                y, 
                game_board->active_tile_palette_index
            );
        }
    }
    */
}

void add_game_board_tile(Game_Board* game_board, Tile* tile, int x, int y)
{
    // Add tile to tiles grid
    game_board->tiles_grid[y][x] = tile;

    // Create tile entry wrapping the tile
    Tile_Entry tile_entry = { tile, x, y };

    // Add tile entry to game clock tiles subscriber
    Animation_Clock_Index clock_index;
    Animation_Sub_Clock_Index sub_clock_index;

    get_tile_clock_data(tile, &clock_index, &sub_clock_index);

    Tile_Entry_List* entry_list = game_board->clock_tiles_subscriber[clock_index][sub_clock_index];

    int index = entry_list->count++;

    entry_list->tile_entries = realloc(entry_list->tile_entries, entry_list->count * sizeof(Tile_Entry));
    entry_list->tile_entries[index] = tile_entry;
}

void fill_game_board_tiles(Game_Board* game_board, Tile_Type type, Tile_Variation variation)
{
    // Get tile of given type and variation
    Tile* tile = get_tile_factory_tile(game_board->tile_factory, type, variation);

    for (int y = 0; y < game_board->height; y++) {
        for (int x = 0; x < game_board->width; x++) {
            add_game_board_tile(game_board, tile, x, y);
        }
    }
}

void edit_game_board_tile(
    Game_Board* game_board,
    int board_x,
    int board_y,
    Tile_Type type,
    Tile_Variation variation
)
{
    // Ensure board_x/board_y are within the game board tile boundaries
    if (board_x <= game_board->width && board_y <= game_board->height) {
        game_board->tiles_grid[board_y][board_x] = get_tile_factory_tile(game_board->tile_factory, type, variation);
    }
}

Tile_Type get_game_board_tile_type(Game_Board* gb, int x, int y)
{
    if (x < 0 || x >= gb->width || y < 0 || y >= gb->height) {
        return OOB;
    }

    return get_tile_type(gb->tiles_grid[y][x]);
}

void free_game_board(Game_Board* game_board)
{
    if (game_board != NULL) {
        free_tile_factory(game_board->tile_factory);

        // TODO: fully deallocate clock_tiles_subscriber

        free(game_board);
    }
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
