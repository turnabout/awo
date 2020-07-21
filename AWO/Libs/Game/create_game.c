#include "Game/_game.h"
#include "GL_Helpers/gl_helpers.h"

Game* EMX create_game(Game_Data* game_data, Game_Window* game_window)
{
    Game* game = malloc(sizeof(Game));

    if (game == NULL) {
        return NULL;
    }

    // TODO: set
    game->update = NULL;
    game->render = NULL;
    game->update_dimensions = NULL;

    game->data = game_data;

    // game->stage = generate_filled_stage(Sea, Middle, 25, 25);
    game->stage = generate_custom_stage();

    // Set the sprite sheet texture
    game->sprite_sheet = get_sprite_sheet_GL_texture(game_data->sprite_sheet);

    // Set the palette texture
    game->palette = create_game_palette_texture(
        game_data->palette,
        Clear,
        (Army_Type[]){ OS, BM, GE, YC }
    );

    // Set modules
    int* window_width, * window_height;
    get_game_window_dimensions_ptrs(game_window, &window_width, &window_height);

    game->camera = create_game_camera(
        window_width,
        window_height,
        game->stage->width,
        game->stage->height
    );

    game->clock = create_clock(game_data->clock);

    game->stage_renderer = create_stage_renderer(
        game->stage,
        game->palette,
        game->sprite_sheet,
        game->data
    );

    game->extras_renderer = create_extras_renderer(game->sprite_sheet);

    // Initially call game's dimensions update function
    game->update_dimensions(game, *window_width, *window_height);

    // Initially set the view matrices for renderers
    update_extras_renderer_view(game->extras_renderer, 100, 100, 16.0f);
    update_stage_renderer_view(game->stage_renderer, 0, 0, 16.0f);

    // Inputs
    game->keyboard_state = create_keyboard_state();
    game->mouse_state = create_mouse_state();
    create_keyboard_handler(game_window);
    create_mouse_handler(game_window);

    return game;
}

void EMX free_game(Game* game)
{
    if (game == NULL) {
        return;
    }

    delete_texture(game->sprite_sheet);
    delete_texture(game->palette);

    free_stage(game->stage);
    free_game_camera(game->camera);
    free_clock(game->clock);
    free_extras_renderer(game->extras_renderer);
    free_stage_renderer(game->stage_renderer);

    free_keyboard_state(game->keyboard_state);
    free_mouse_state(game->mouse_state);
    free_keyboard_handler();
    free_mouse_handler();
    free(game);
}
