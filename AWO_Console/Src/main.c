#include "Console/console.h"

int main(int argc, char** argv)
{
    /*
    Game_Window* window = create_game_window(0, 0);
    Game_Data* data = create_game_data();
    Game* game = create_editor_game(data, window);

    run_game(game, window, test_cb, NULL);

    free_editor_game(game);
    free_game_data(data);
    free_game_window(window);
*/

    Console* console = create_console();

    send_console_command(console, "dr");

    if (!console) {
        run_console(console);
    }

    free_console(console);

    return 0;
}