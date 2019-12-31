#pragma once

typedef struct Console Console;

Console* create_console();

void run_console(Console* console);

void free_console(Console* console);
