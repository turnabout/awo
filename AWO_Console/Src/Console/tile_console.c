#include <windows.h>

#include "Utilities/utilities.h"
#include "Console/_console.h"

void tile_console(Console* console)
{
    if (console->game == NULL) {
        return;
    }

    // Get handle to game's window
    LPWSTR win_name = L"AWO";
    HWND handle = FindWindow(NULL, win_name);

    int windows_w = 1050;
    int windows_h = 900;
    int windows_y = 100;

    // Move console window
    MoveWindow(
        GetConsoleWindow(),
        0,
        windows_y,
        windows_w,
        windows_h,
        TRUE
    );

    // Move game window
    int game_win_w = 800;
    int game_win_h = 800;

    MoveWindow(
        handle,
        windows_w,
        windows_y,
        windows_w,
        windows_h,
        TRUE
    );

    update_game_window_dimensions(console->game, game_win_w, game_win_h);
}