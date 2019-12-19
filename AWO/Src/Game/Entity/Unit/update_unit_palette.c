#include "Game/Entity/Unit/_unit.h"
#include "Game/Data/Palette/game_palette.h"

void update_unit_palette(Game_Renderer* renderer, void* unit, Bool done)
{
    update_tile_layer_pixel_high(
        renderer,
        UNIT_LAYER,
        ((Unit*)unit)->x,
        ((Unit*)unit)->y,
        (vec2) {
            get_player_unit_palette_index(((Unit*)unit)->player->index, done),
            0.0f
        }
    );
}
