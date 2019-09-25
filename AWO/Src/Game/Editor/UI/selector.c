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
    int active;               // Whether the selector is currently active or not
    SDL_Rect draw_rect;       // The tile selector's outer rectangle
    SDL_Rect inner_draw_rect; // The tile selector's inner rectangle
    Tile_Selection sel_tiles[TILE_TYPE_BASIC_COUNT]; // Tile selections shown in selector
};

// Create the tile selector.
Selector* tile_selector_create(Tiles_Data* td)
{
    Selector* sel = malloc(sizeof(Selector));

    sel->active = 1;

    // Set outer and inner draw rectangles
    SDL_Rect draw_rect = {
        0 + SELECTOR_OUTER_PADDING, 
        0 + SELECTOR_OUTER_PADDING, 
        SELECTOR_WIDTH - (SELECTOR_OUTER_PADDING * 2), 
        SELECTOR_HEIGHT - (SELECTOR_OUTER_PADDING * 2),
    };

    SDL_Rect inner_draw_rect = {
        draw_rect.x + SELECTOR_INNER_PADDING,
        draw_rect.y + SELECTOR_INNER_PADDING,
        draw_rect.w - (SELECTOR_INNER_PADDING * 2),
        draw_rect.h - (SELECTOR_INNER_PADDING * 2)
    };

    sel->draw_rect = draw_rect;
    sel->inner_draw_rect = inner_draw_rect;

    // Add tile frames
    int cur_y = inner_draw_rect.y;
    int tiles_w = inner_draw_rect.w;
    int size_multiplier = tiles_w / DEFAULT_TILE_DIMENSION; // Multiplier to get tiles' height

    for (Tile_Type tt = TILE_TYPE_FIRST; tt < TILE_TYPE_BASIC_COUNT; tt++) {
        Tile_Var default_var = default_tile_vars[tt];

        // Add source rectangle
        SDL_Rect* src_rect = TD_gather_tile_data(td, tt, default_var, NULL, NULL);

        // Add draw rectangle
        Tile_Selection tile = {
            src_rect,
            {
                inner_draw_rect.x, 
                cur_y, 
                tiles_w, 
                src_rect->h * size_multiplier
            }
        };

        cur_y += tile.draw_rect.h + SELECTOR_INNER_PADDING;

        sel->sel_tiles[tt] = tile;
    }

    // Close off the selector box
    cur_y -= SELECTOR_INNER_PADDING;
    sel->draw_rect.h = cur_y;
    sel->inner_draw_rect.h = cur_y - (SELECTOR_INNER_PADDING * 2);

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
        SDL_SetRenderDrawColor(rend, 0, 0, 0, EDITOR_UI_ALPHA);
        SDL_RenderFillRect(rend, &sel->draw_rect);

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