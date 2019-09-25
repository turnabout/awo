#include <stdio.h>
#include "conf.h"
#include "selector.h"

#pragma warning( disable : 6011 )

// A tile selection within the tile selector.
typedef struct Tile_Selection {
    SDL_Rect* src_rect; // The tile's source rectangle
    SDL_Rect draw_rect; // The tile's draw (destination) rectangle
} Tile_Selection;

// UI element for selecting a tile to add.
struct Tile_Selector {
    int active;          // Whether the selector is currently active or not
    SDL_Rect outer_rect; // The tile selector's outer rectangle
    SDL_Rect inner_rect; // The tile selector's inner rectangle
    Tile_Selection sel_tiles[TILE_TYPE_BASIC_COUNT]; // Tile selections shown in selector
};

// Create the tile selector.
Selector* tile_selector_create(Tiles_Data* td)
{
    Selector* sel = malloc(sizeof(Selector));

    sel->active = 1;

    // Set inner and outer rectangles
    SDL_Rect inner_rect = {
        TILE_SELECTOR_X + TILE_SELECTOR_PADDING,
        TILE_SELECTOR_Y + TILE_SELECTOR_PADDING,
        TILE_SELECTOR_WIDTH,
        0
    };

    SDL_Rect outer_rect = {
        TILE_SELECTOR_X,
        TILE_SELECTOR_Y,
        TILE_SELECTOR_WIDTH + (TILE_SELECTOR_PADDING * 2),
        0
    };

    // Add tile frames
    int cur_y = inner_rect.y;
    int sels_w = inner_rect.w;
    int size_multiplier = sels_w / DEFAULT_TILE_DIMENSION; // Multiplier to get selections' height

    for (Tile_Type tt = TILE_TYPE_FIRST; tt < TILE_TYPE_BASIC_COUNT; tt++) {

        // Get default variation for this tile type
        Tile_Var default_var = default_tile_vars[tt];

        // Add source rectangle
        SDL_Rect* src_rect = TD_gather_tile_data(td, tt, default_var, NULL, NULL);

        // Add tile with draw rectangle
        Tile_Selection tile = {
            src_rect,
            {
                inner_rect.x, 
                cur_y, 
                sels_w, 
                src_rect->h * size_multiplier
            }
        };

        cur_y += tile.draw_rect.h + TILE_SELECTOR_PADDING;

        sel->sel_tiles[tt] = tile;
    }

    // Close off the selector box
    cur_y -= TILE_SELECTOR_PADDING;
    outer_rect.h = cur_y;
    inner_rect.h = cur_y - (TILE_SELECTOR_PADDING * 2);

    sel->inner_rect = inner_rect;
    sel->outer_rect = outer_rect;

    return sel;
}

// Update the selector.
void tile_selector_update(Selector* sel)
{
}

// Draw the selector UI.
void tile_selector_draw(Selector* sel, SDL_Renderer* rend, SDL_Texture* tiles_tex)
{
    if (sel->active) {

        // Draw UI rectangle
        SDL_SetRenderDrawColor(rend, EDITOR_UI_R, EDITOR_UI_G, EDITOR_UI_B, EDITOR_UI_ALPHA);
        SDL_RenderFillRect(rend, &sel->outer_rect);

        // Draw selections
        for (Tile_Type tt = TILE_TYPE_FIRST; tt < TILE_TYPE_BASIC_COUNT; tt++) {
            SDL_RenderCopy(
                rend, 
                tiles_tex, 
                sel->sel_tiles[tt].src_rect, 
                &sel->sel_tiles[tt].draw_rect
            );
        }

        SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
    }
}