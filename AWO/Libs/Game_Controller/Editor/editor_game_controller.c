#include <stdlib.h>

#include "Game/Controller/Editor/_game_editor_controller.h"
#include "GL_Helpers/gl_helpers.h"

Game_Editor_Controller* create_game_editor_controller(
    Game_Data* game_data,
    int* window_width,
    int* window_height
)
{
    Game_Editor_Controller* controller = malloc(sizeof(Game_Editor_Controller));

    if (controller == NULL) {
        return NULL;
    }

    controller->camera = NULL;
    controller->clock = NULL;
    controller->stage_renderer = NULL;
    controller->extras_renderer = NULL;

    controller->stage = generate_filled_stage(Plain, Default, 25, 25);

    // Set modules
    controller->palette = create_game_palette_texture(
        game_data->raw_palette, 
        WEATHER_DEFAULT, 
        stage->player_armies
    );

    controller->camera = create_game_camera(
        window_width, 
        window_height, 
        controller->stage->width,
        controller->stage->height
    );

    controller->stage_renderer = create_stage_renderer(controller->stage, game_data);
    controller->extras_renderer = create_extras_renderer(game_data->sprite_sheet);

    controller->clock = create_game_clock(game_data->clock);

    // Error if any of the modules were NULL
    if (
        controller->camera == NULL || 
        controller->clock == NULL ||
        controller->stage_renderer == NULL ||
        controller->extras_renderer ||
        controller->stage == NULL
    ) {
        free_game_editor_controller(controller);
        return NULL;
    }

    // Update grid shader's matrices
    mat4 initial_projection;
    create_projection_matrix(*window_width, *window_height, initial_projection);

    update_stage_renderer_projection(controller->stage_renderer, initial_projection);
    update_extras_renderer_projection(controller->extras_renderer, initial_projection);

    return controller;
}

void free_game_editor_controller(Game_Editor_Controller* controller)
{
    if (controller == NULL) {
        return;
    }

    free_game_camera(controller->camera);
    free_game_clock(controller->clock);
    free_stage_renderer(controller->stage_renderer);
    free_extras_renderer(controller->extras_renderer);
    free_stage(controller->stage);

    free(controller);
}