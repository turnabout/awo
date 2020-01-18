#include "Game/_game.h"

/*
int EMX prepare_design_room_game(
    Game* game, 
    Game_Mode mode,
    Stage* stage, 
    int player_COs[MAX_PLAYER_COUNT]
)
{
    // Confirm the game state is valid
    if (game->state != Game_Initialized) {
        printe("Error: game state must be %d, was %d", Game_Initialized, game->state);
        return FALSE;
    }

    // Validate the given stage
    if (stage != NULL && !validate_stage(stage)) {
        printe("prepare_game: Given stage was invalid");
        return FALSE;
    }

    switch (mode) {

    case Design_Room_Mode:
        game->controller = (Game_Controller*)create_game_editor_controller(
            game->data,
            stage,
            &(game->window_width),
            &(game->window_height)
        );

        break;

    case Gameplay_Mode:
        printe("prepare_game: Game mode %d not yet supported", Gameplay_Mode);
        return FALSE;

    default:
        printe("prepare_game: Invalid game mode");
        return FALSE;
    }

    if (game->controller == NULL) {
        return FALSE;
    }

    game->mode = mode;
    return TRUE;

    // Prepare components used for rendering the game
    game->palette = create_game_palette_texture(
        game->data->raw_palette, 
        WEATHER_DEFAULT, 
        stage->player_armies
    );

    // Renderer
    game->renderer = create_game_renderer(
        stage->width,
        stage->height,
        game->palette,
        game->data->tiles,
        game->window_width,
        game->window_height
    );

    if (game->renderer == NULL) {
        printe("Error preparing game renderer");
        unprepare_game(game);
        return FALSE;
    }

    // Clock
    game->clock = create_game_clock(game->data->clock, game->renderer, &game->palette);

    // Camera
    game->camera = create_game_camera(
        game->renderer, 
        &game->window_width, 
        &game->window_height, 
        stage
    );

    if (game->camera == NULL) {
        printe("Error preparing game camera");
        unprepare_game(game);
        return FALSE;
    }

    // Board
    game->board = create_game_board(
        game->clock, 
        game->renderer,
        stage, 
        player_COs,
        game->data->tiles, 
        game->data->raw_palette,
        game->palette
    );

    if (game->board == NULL) {
        printe("Error preparing game");
        unprepare_game(game);
        return FALSE;
    }

    game->state = Game_Prepared;
}
*/

/*
int EMX prepare_design_room_game(Game* game)
{
    game->controller = (Game_Controller*)create_game_editor_controller(
        game->data,
        generate_filled_stage(Plain, Default, 25, 25),
        &(game->window_width),
        &(game->window_height)
    );

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
        // generate_custom_stage(),
        generate_filled_stage(Plain, Default, 10, 10),
        (CO_Type[MAX_PLAYER_COUNT]) { Andy, Olaf }
    );

    return TRUE;
}
*/