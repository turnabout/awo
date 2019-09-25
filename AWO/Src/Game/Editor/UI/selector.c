#include <stdio.h>
#include "conf.h"
#include "selector.h"

#pragma warning( disable : 6011 )

typedef struct Selector_Tile {

    SDL_Rect* src_rect; // Tile frames shown in selector
    SDL_Rect draw_rect;   // 
} Selector_Tile;

struct Selector {
    int active;
    SDL_Rect draw_rect;
    // SDL_Rect* tile_frames[TILE_TYPE_BASIC_COUNT]; 
    Selector_Tile sel_tiles[TILE_TYPE_BASIC_COUNT]; // Tile frames shown in selector
};

// Create the entity selector.
Selector* selector_create(Tiles_Data* td)
{
    Selector* sel = malloc(sizeof(Selector));

    sel->active = 1;

    SDL_Rect draw_rect = {
        0, 0, SELECTOR_WIDTH, SELECTOR_HEIGHT
    };

    sel->draw_rect = draw_rect;

    // Add tile frames
    int cur_y = 0;

    for (Tile_Type tt = TILE_TYPE_FIRST; tt < TILE_TYPE_BASIC_COUNT; tt++) {
        Tile_Var default_var = default_tile_vars[tt];

        SDL_Rect* src_rect = TD_gather_tile_data(td, tt, default_var, NULL, NULL);

        Selector_Tile tile = {
            src_rect,
            {0, cur_y, DEFAULT_TILE_DIMENSION, src_rect->h}
        };

        cur_y += tile.draw_rect.h;

        sel->sel_tiles[tt] = tile;
    }

    return sel;
}

// Update the selector.
void selector_update(Selector* sel)
{
}

// Draw the selector UI.
void selector_draw(Selector* sel, SDL_Renderer* rend, SDL_Texture* tiles_tex)
{
    if (sel->active) {
        SDL_SetRenderDrawColor(rend, 0, 0, 0, EDITOR_UI_ALPHA);

        // Draw UI rectangle
        SDL_RenderFillRect(rend, &sel->draw_rect);

        // Draw selector tiles
        for (Tile_Type tt = TILE_TYPE_FIRST; tt < TILE_TYPE_BASIC_COUNT; tt++) {
            SDL_RenderCopy(
                rend, 
                tiles_tex, 
                sel->sel_tiles[tt].src_rect, 
                &sel->sel_tiles[tt].draw_rect
            );
        }

        SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);

        /*

        // Draw tiles selector
        for (Tile_Type tt = TILE_TYPE_FIRST; tt < TILE_TYPE_BASIC_COUNT; tt++) {
            SDL_Rect draw_rect = {
                0, 
                tt * DEFAULT_TILE_DIMENSION,
                DEFAULT_TILE_DIMENSION, 
                DEFAULT_TILE_DIMENSION
            };

            SDL_RenderCopy(rend, tiles_tex, sel->tile_frames[tt], &draw_rect);
        }

        SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
*/
    }
}