#include "conf.h"
#include "selector.h"

#pragma warning( disable : 6011 )

struct Selector {
    int active;
    SDL_Rect draw_rect;
    FC_Font* font;
};

// Create the entity selector.
Selector* selector_create(Tiles_Data* td, SDL_Renderer* rend)
{
    Selector* sel = malloc(sizeof(Selector));

    sel->active = 1;

    SDL_Rect draw_rect = {
        0, 0, SELECTOR_WIDTH, SELECTOR_HEIGHT
    };

    sel->draw_rect = draw_rect;

    // Add font
    sel->font = FC_CreateFont();

    FC_LoadFont(
        sel->font, 
        rend, 
        FONT_PATH, 
        EDITOR_FONT_SIZE, 
        FC_MakeColor(255, 255, 255, 255), 
        TTF_STYLE_NORMAL
    );

    return sel;
}

// Update the selector.
void selector_update(Selector* sel)
{
}

// Draw the selector UI.
void selector_draw(Selector* sel, SDL_Renderer* rend)
{
    if (sel->active) {
        SDL_SetRenderDrawColor(rend, 0, 0, 0, EDITOR_UI_ALPHA);
        SDL_SetRenderDrawBlendMode(rend, SDL_BLENDMODE_BLEND);

        // SDL_RenderDrawRect(rend, &sel->draw_rect);
        SDL_RenderFillRect(rend, &sel->draw_rect);

        FC_Draw(sel->font, rend, 5, 5, tile_type_str[Plain]);

        SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
    }
}