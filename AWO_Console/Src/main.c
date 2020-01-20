#include "Console/console.h"

int main(int argc, char** argv)
{
    Console* console = create_console();

    if (console) {
        send_console_command(console, "dr");
        run_console(console);
    }

    free_console(console);

    return 0;
}