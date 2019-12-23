#include "emx.h"
#include "Game/_game.h"

void EMX update_game_editor_selected_entity(
    Game* game, 
    Game_Editor_Entity_Kind kind, 
    int type, 
    int variation
)
{
    update_editor_selected_entity(game->editor, kind, type, variation);
}