#include <stdlib.h>

#include "Game/Board/_game_board.h"
#include "Game/Player/player.h"
#include "Game/Inputs/inputs.h"

PRAGMA( warning(disable: 6001) )

Game_Board* create_game_board(
    Game_Clock* game_clock,
    Game_Renderer* game_renderer,
    Stage* stage,
    CO_Type player_COs[MAX_PLAYER_COUNT],
    Tiles_Data* tiles_data,
    GLuint raw_palette_texture,
    GLuint game_palette_texture
)
{
    if (!validate_stage(stage)) {
        return NULL;
    }

    Game_Board* game_board = malloc(sizeof(Game_Board));

    game_board->tiles_data = tiles_data;
    game_board->raw_palette_texture = raw_palette_texture;
    game_board->game_palette_texture = game_palette_texture;
    game_board->game_renderer = game_renderer;

    // Set players
    game_board->player_count = stage->player_count;

    for (int i = 0; i < MAX_PLAYER_COUNT; i++) {
        game_board->players[i] = create_player(
            i,
            stage->player_armies[i],
            player_COs[i]
        );

        // Set player lists
        game_board->player_properties[i] = create_linked_list(NULL, 0);
        game_board->player_units[i] = create_linked_list(NULL, 0);
    }

    // Set neutral player, for holding neutral properties
    game_board->players[MAX_PLAYER_COUNT] = create_player(
        Player_Index_Neutral,
        ARMY_TYPE_NEUTRAL,
        Andy
    );
    game_board->player_properties[MAX_PLAYER_COUNT] = create_linked_list(NULL, 0);

    // Load the given stage
    load_game_board_stage(game_board, game_clock, tiles_data, stage);

    return game_board;
}

void update_game_board(Game_Board* game_board)
{
    if (get_key_state(KEY_3) == BUTTON_DOWN_START) {
        update_game_board_weather(game_board, Clear);
    }

    if (get_key_state(KEY_4) == BUTTON_DOWN_START) {
        update_game_board_weather(game_board, Snow);
    }

    if (get_key_state(KEY_5) == BUTTON_DOWN_START) {
        update_game_board_weather(game_board, Rain);
    }
}

void free_game_board(Game_Board* game_board)
{
    if (game_board == NULL) {
        return;
    }

    // Free tiles grid
    if (game_board->tiles_grid != NULL) {
        for (int i = 0; i < game_board->stage->height; i++) {
            if (game_board->tiles_grid[i] != NULL) {
                free(game_board->tiles_grid[i]);
            }
        }

        free(game_board->tiles_grid);
    }

    // Free units grid
    if (game_board->units_grid != NULL) {
        for (int i = 0; i < game_board->stage->height; i++) {
            if (game_board->units_grid[i] != NULL) {
                free(game_board->units_grid[i]);
            }
        }

        free(game_board->units_grid);
    }

    // Free players & player-owned lists
    for (int i = 0; i < MAX_PLAYER_COUNT; i++) {
        free_player(game_board->players[i]);
        free_linked_list(game_board->player_properties[i]);

        // No "neutral" player units list
        if (i != MAX_PLAYER_COUNT) {
            free_linked_list(game_board->player_units[i]);
        }
    }

    // Free neutral properties list
    free_linked_list(game_board->player_properties[MAX_PLAYER_COUNT]);

    free(game_board);
}
