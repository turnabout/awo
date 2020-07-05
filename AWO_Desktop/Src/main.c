#include <stdio.h>
#include <AWO/awo.h>

int quit = 0;

int test_cb(void* value)
{
    if (quit) {
        quit = 0;
        return -1;
    }

    return 0;
}

int main()
{
    Game_Data* data;
    printf("Test\n");
    /*
    Game_Data* data = create_game_data();
    Game_Window* window = create_game_window(0, 0);
    Game* game = create_editor_game(data, window);

    show_game_window(window);
    run_game(game, window, test_cb, NULL);
    hide_game_window(window);

    free_editor_game(game);
    free_game_data(data);
    free_game_window(window);
     */
}