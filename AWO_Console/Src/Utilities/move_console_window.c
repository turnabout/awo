#include <windows.h>

void tile_console_window()
{
    // SetForegroundWindow(GetConsoleWindow());
    MoveWindow(
        GetConsoleWindow(),
        0,
        0,
        500,
        500,
        TRUE
    );
}