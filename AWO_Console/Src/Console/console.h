#pragma once

typedef struct Console Console;

Console* create_console();

void run_console(Console* console);
void send_console_command(Console* console, char* user_command);

void free_console(Console* console);
