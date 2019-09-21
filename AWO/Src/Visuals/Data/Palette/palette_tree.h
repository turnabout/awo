#pragma once
#include <stdarg.h>
#include <SDL.h>

#include "cJSON.h"

// A palette tree holding data for a palette.
typedef struct Palette_Node Palette_Tree;

// Generates an entire palette tree from one or many cJSON nodes holding a palette object.
Palette_Tree* PT_create_from_JSON(const cJSON* palettes_json, ...);

// Gets value in the given palette tree corresponding to the given key.
// Returns the value associated with the given key or -1 if no value was found.
Uint32 PT_get_value(Palette_Tree* tree, int key);

// Frees a palette tree's allocated memory.
void PT_free(Palette_Tree* tree);