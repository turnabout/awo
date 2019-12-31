#include <stdio.h>

#include "Console/_console.h"

#define DEFAULT_WINDOW_W 500
#define DEFAULT_WINDOW_H 500

void init(Console* console, void* payload[CMD_ARG_MAX_COUNT])
{
    // Ignore if game was already set
    if (console->game != NULL) {
        // TODO: error
        return;
    }

    // Unpack the payload's values
    int window_w = (payload[0] != NULL) ? *((int*)payload[0]) : DEFAULT_WINDOW_W;
    int window_h = (payload[1] != NULL) ? *((int*)payload[1]) : DEFAULT_WINDOW_H;

    console->game = create_game(window_w, window_h);
}