#pragma once

#include "AWO/Include/game.h"

typedef struct Console Console;

Console* create_console();

void update_console(Console* console, Game* game);

void free_console(Console* console);
