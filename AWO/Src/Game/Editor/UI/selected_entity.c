#include <SDL.h>
#include "conf.h"
#include "Game/Entities/Tile/enums.h"
#include "selected_entity.h"

#define SELECTED_ENTITY_WIDTH DEFAULT_TILE_DIMENSION
#define SELECTED_ENTITY_HEIGHT DEFAULT_TILE_DIMENSION
#define SELECTED_ENTITY_INNER_PADDING SELECTED_ENTITY_WIDTH / 2
#define SELECTED_ENTITY_OUTER_PADDING SELECTED_ENTITY_HEIGHT / 2

typedef enum {
    SEP_Bottom_Left,
    SEP_Bottom_Right,
} Selected_Entity_Position;

struct Selected_Entity {

    SDL_Rect outer_draw_rect;
    SDL_Rect inner_draw_rect;

    // Currently selected tile
    Tile_Type selected_tile_type;
    Tile_Var selected_tile_var;

    // Pointers to the game's full screen width/height
    int* screen_w, * screen_h;

    // The selected entity's current position
    Selected_Entity_Position position;
};

void SE_change_position(Selected_Entity* se, Selected_Entity_Position position)
{
    switch (position) {
    case SEP_Bottom_Left:
        se->outer_draw_rect.x = 0 + SELECTED_ENTITY_OUTER_PADDING;
        break;
    case SEP_Bottom_Right:
        se->outer_draw_rect.x = *se->screen_w - se->inner_draw_rect.w - (SELECTED_ENTITY_OUTER_PADDING * 2);
        break;
    }

    se->outer_draw_rect.y = *se->screen_h - se->inner_draw_rect.h - (SELECTED_ENTITY_OUTER_PADDING * 2);
    se->inner_draw_rect.x = se->outer_draw_rect.x + SELECTED_ENTITY_INNER_PADDING;
    se->inner_draw_rect.y = se->outer_draw_rect.y + SELECTED_ENTITY_INNER_PADDING;

    se->position = position;
}

Selected_Entity* SE_create(int* screen_w, int* screen_h)
{
    Selected_Entity* se = malloc(sizeof(Selected_Entity));

    se->screen_w = screen_w;
    se->screen_h = screen_h;
    se->selected_tile_type = TILE_TYPE_DEFAULT;
    se->selected_tile_var = TILE_VAR_DEFAULT;

    // Set dimensions
    se->inner_draw_rect.w = SELECTED_ENTITY_WIDTH;
    se->inner_draw_rect.h = SELECTED_ENTITY_HEIGHT;
    se->outer_draw_rect.w = se->inner_draw_rect.w + (SELECTED_ENTITY_INNER_PADDING * 2);
    se->outer_draw_rect.h = se->inner_draw_rect.h + (SELECTED_ENTITY_INNER_PADDING * 2);

    // Initialize position
    SE_change_position(se, SEP_Bottom_Left);

    return se;
}

void SE_change_tile(Selected_Entity* se, Tile_Type type, Tile_Var var)
{
    se->selected_tile_type = type;
    se->selected_tile_var = var;
}

void SE_update(Selected_Entity* se, Mouse_State* mouse)
{
    // Change selected entity position if mouse hovers on it
    if (SDL_PointInRect(mouse->pointer, &se->outer_draw_rect)) {
        Selected_Entity_Position new_pos = (se->position == SEP_Bottom_Left)
            ? SEP_Bottom_Right
            : SEP_Bottom_Left;

        SE_change_position(se, new_pos);
    }
}

void SE_draw(Selected_Entity* se, SDL_Renderer* rend)
{
    // Draw outer rectangle
    SDL_SetRenderDrawColor(rend, EDITOR_UI_R, EDITOR_UI_G, EDITOR_UI_B, EDITOR_UI_A);
    SDL_RenderFillRect(rend, &se->outer_draw_rect);

    // Draw entity's inner rectangle
    SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
    SDL_RenderFillRect(rend, &se->inner_draw_rect);
}