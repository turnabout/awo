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

    return controller;
}

void free_game_editor_controller(Game_Editor_Controller* controller)
{
    if (controller == NULL) {
        return;
    }

    free(controller);
}