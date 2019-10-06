#include <stdio.h>
#include "conf.h"
#include "tile_selector.h"

// A tile selection within the tile selector.
typedef struct Tile_Selection {
    SDL_Rect* src_rect;  // The tile's source rectangle
    SDL_Rect* draw_rect; // The tile's draw (destination) rectangle
} Tile_Selection;

// UI element for selecting a tile to add.
struct Tile_Selector {
    Uint8 active;         // Whether the selector is currently active or not
    SDL_Rect* outer_rect; // The tile selector's outer rectangle
    SDL_Rect* inner_rect; // The tile selector's inner rectangle
    Tile_Selection sel_tiles[TILE_TYPE_BASIC_COUNT]; // Tile selections shown in selector

    Tile_Type hovered_tile;       // Currently hovered tile
    Tile_Type selected_tile;      // Currently selected tile
    Tile_Type new_selected_tile;  // Newly selected tile, used to propagate to editor
};

// Create the tile selector.
Tile_Selector* tile_selector_create(Tiles_Data* td)
{
    Tile_Selector* sel = malloc(sizeof(Tile_Selector));

    sel->active = 1;
    sel->hovered_tile = sel->new_selected_tile = TILE_TYPE_NONE;
    sel->selected_tile = TILE_TYPE_FIRST;

    // Set inner and outer rectangles
    sel->inner_rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    sel->outer_rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));

    sel->inner_rect->x = TILE_SELECTOR_X + TILE_SELECTOR_PADDING;
    sel->inner_rect->y = TILE_SELECTOR_Y + TILE_SELECTOR_PADDING;
    sel->inner_rect->w = TILE_SELECTOR_WIDTH;

    sel->outer_rect->x = TILE_SELECTOR_X;
    sel->outer_rect->y = TILE_SELECTOR_Y;
    sel->outer_rect->w = TILE_SELECTOR_WIDTH + (TILE_SELECTOR_PADDING * 2);

    // Add tile frames
    int cur_y = sel->inner_rect->y;
    int sels_w = sel->inner_rect->w;
    float size_multiplier = (float)sels_w / (float)DEFAULT_TILE_DIMENSION; // Multiplier to get selections' height

    for (Tile_Type tt = TILE_TYPE_FIRST; tt < TILE_TYPE_BASIC_COUNT; tt++) {

        // Get default variation for this tile type
        Tile_Var default_var = default_tile_vars[tt];

        // Add source rectangle
        SDL_Rect* src_rect = TD_gather_tile_data(td, tt, default_var, NULL, NULL);

        // Add draw rectangle
        SDL_Rect* draw_rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));

        draw_rect->x = sel->inner_rect->x;
        draw_rect->y = cur_y;
        draw_rect->w = sels_w;
        draw_rect->h = (int)(src_rect->h * size_multiplier);

        // Add tile selection
        Tile_Selection tile = { src_rect, draw_rect };

        cur_y += tile.draw_rect->h + TILE_SELECTOR_PADDING;
        sel->sel_tiles[tt] = tile;
    }

    // Close off the selector box
    cur_y -= TILE_SELECTOR_PADDING;
    sel->outer_rect->h = cur_y;
    sel->inner_rect->h = cur_y - (TILE_SELECTOR_PADDING * 2);

    return sel;
}

// Update the selector.
void tile_selector_update(Tile_Selector* sel, Mouse_State* mouse)
{
    // Toggle tile selector on key press
    if (key_down_started(KEY_1)) {
        sel->active ^= 1;
    }

    // Don't update if inactive or mouse cursor is outside
    if (!sel->active || !SDL_PointInRect(mouse->pointer, sel->inner_rect)) {
        sel->hovered_tile = TILE_TYPE_NONE;
        return;
    }

    // Get hovered tile
    for (Tile_Type tt = TILE_TYPE_FIRST; tt < TILE_TYPE_BASIC_COUNT; tt++) {
        if (SDL_PointInRect(mouse->pointer, sel->sel_tiles[tt].draw_rect)) {
            sel->hovered_tile = tt;

            // Get whether hovered tile was selected
            if (mouse_down_started(mouse, MOUSE_LEFT)) {
                sel->new_selected_tile = sel->selected_tile = sel->hovered_tile;
            }

            break;
        }
    }
}

// Draw the selector UI.
void tile_selector_draw(Tile_Selector* sel, SDL_Renderer* rend, SDL_Texture* tiles_tex)
{
    if (sel->active) {

        // Draw wrapping UI selector rectangle
        SDL_SetRenderDrawColor(rend, EDITOR_UI_R, EDITOR_UI_G, EDITOR_UI_B, EDITOR_UI_ALPHA);
        SDL_RenderFillRect(rend, sel->outer_rect);
        SDL_SetRenderDrawColor(rend, 255, 0, 0, 155);

        // Draw tiles
        for (Tile_Type tt = TILE_TYPE_FIRST; tt < TILE_TYPE_BASIC_COUNT; tt++) {
            SDL_RenderCopy(
                rend, 
                tiles_tex, 
                sel->sel_tiles[tt].src_rect, 
                sel->sel_tiles[tt].draw_rect
            );
        }

        // Draw on hover TODO: draw something else
        if (sel->hovered_tile != TILE_TYPE_NONE) {
            SDL_RenderDrawRect(rend, sel->sel_tiles[sel->hovered_tile].draw_rect);
        }

        // Draw on selection TODO: draw something else
        if (sel->selected_tile != TILE_TYPE_NONE) {
            SDL_RenderFillRect(rend, sel->sel_tiles[sel->selected_tile].draw_rect);
        }

        SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
    }
}