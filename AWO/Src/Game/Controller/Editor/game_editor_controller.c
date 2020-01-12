#include <stdlib.h>

#include "Game/Controller/Editor/_game_editor_controller.h"

Game_Editor_Controller* create_game_editor_controller(
    Game_Data* game_data,
    Stage* stage,
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

    // Process the given stage, if any
    if (stage != NULL) {

        if (!validate_stage(stage)) {
            free_game_editor_controller(controller);
            return NULL;
        }

        controller->stage = stage;

    } else {
        controller->stage = generate_filled_stage(Plain, Default, 25, 25);
    }

    // Process other modules
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

    // controller->stage_renderer = create_stage_renderer();
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

    return controller;
}

void free_game_editor_controller(Game_Editor_Controller* controller)
{
    if (controller == NULL) {
        return;
    }

    free_game_camera(controller->camera);
    free_game_clock(controller->clock);
    // free_stage_renderer(controller->stage_renderer);
    free_extras_renderer(controller->extras_renderer);
    free_stage(controller->stage);

    free(controller);
}