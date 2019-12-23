#include "emx.h"
#include "Game/_game.h"

int EMX prepare_design_room_game(Game* game)
{
    game->editor = create_game_editor(
        game->data->tiles,
        game->data->units,
        &game->window_width,
        &game->window_height
    );

    if (game->editor == NULL) {
        return FALSE;
    }

    return prepare_game(
        game, 
        generate_custom_stage(),
        (CO_Type[MAX_PLAYER_COUNT]) { Andy, Olaf }
    );
}