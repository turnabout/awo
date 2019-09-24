#include <SDL_ttf.h>
#include "conf.h"
#include "selector.h"

struct Selector {
    SDL_Rect draw_rect;
};

// Create the entity selector.
Selector* selector_create(Tiles_Data* td)
{
    Selector* sel = malloc(sizeof(Selector));

    SDL_Rect draw_rect = {
        0, 0, SELECTOR_WIDTH, SELECTOR_HEIGHT
    };

    sel->draw_rect = draw_rect;

    return sel;
}

// Update the selector.
void selector_update(Selector* sel)
{
}

// Draw the selector UI.
void selector_draw(Selector* sel, SDL_Renderer* rend)
{
    SDL_SetRenderDrawColor(rend, 0, 0, 0, EDITOR_UI_ALPHA);
    SDL_SetRenderDrawBlendMode(rend, SDL_BLENDMODE_BLEND);

    // SDL_RenderDrawRect(rend, &sel->draw_rect);
    SDL_RenderFillRect(rend, &sel->draw_rect);

    SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
}