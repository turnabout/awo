#include <stdio.h>

#include "Console/console.h"

int main(int argc, char** argv)
{
    Console* console = create_console();

    send_console_command(console, "dr");

    if (console != NULL) {
        run_console(console);
    }

    free_console(console);

    return 0;
}