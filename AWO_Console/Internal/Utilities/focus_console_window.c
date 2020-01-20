#include <windows.h>

void focus_console_window()
{
    SetForegroundWindow(GetConsoleWindow());
}