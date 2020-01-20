#pragma once

// Curses color pairs
#define COLOR_PAIR_NONE    -1
#define COLOR_PAIR_INFO     1
#define COLOR_PAIR_ERROR    2
#define COLOR_PAIR_WARNING  3

// Console message
typedef struct Message Message;

Message* create_message(char* message_str, int color_pair);

void print_message(Message* message, int y, int x);

void free_message(Message* message);