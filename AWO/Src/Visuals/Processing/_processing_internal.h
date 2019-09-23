#include <SDL.h>
#include "Visuals/Data/Palette/palette_tree.h"

// Apply the given palette to the current texture target of the given renderer
SDL_Texture* apply_palette(SDL_Renderer* rend, Palette_Tree* palette, int w, int h);