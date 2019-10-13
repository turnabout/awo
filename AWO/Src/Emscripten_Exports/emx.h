#pragma once

#ifdef __EMSCRIPTEN__
#include <emscripten.h>

// Marks a function as an emscripten exported function.
// Must be added before all functions that are to be exported.
#define EMX EMSCRIPTEN_KEEPALIVE
#endif