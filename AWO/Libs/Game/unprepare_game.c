#include "Game/_game.h"

void EMX unprepare_game(Game* game)
{
    game->state = Game_Initialized;

    /*
    switch (game->mode) {

    case Design_Room_Mode:
        free_game_editor_controller((Game_Editor_Controller*)game->controller);
        game->controller = NULL;
        break;
    case Gameplay_Mode:
        break;
    }
    */

    game->mode = No_Game_Mode;
}
