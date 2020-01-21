#include <stdio.h>
#include <AWO/Include/awo.h>

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
    Game_Data* data = create_game_data();
    Game_Window* window = create_game_window(0, 0);

    char c;
    while ((c = getchar()) != 'x') {
        int limit = (c == 'b') ? 100 : 1;

        for (int i = 0; i < limit; i++) {
            Game* game = create_editor_game(data, window);

            printf("a");

            /*
            show_game_window(window);
            run_game(game, window, test_cb, NULL);
            hide_game_window(window);
            */

            free_editor_game(game);
        }

        printf("\n");
    }

    /*
    show_game_window(window);
    run_game(game, window, test_cb, NULL);
    hide_game_window(window);
    */

    free_game_data(data);
    free_game_window(window);
}