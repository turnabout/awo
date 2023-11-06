#include "Game/Entity/Unit/_unit.h"

void delete_unit(
    Game_Renderer* game_renderer,
    Clock* game_clock,
    void* unit_arg,
    void* units_data
)
{
    if (unit_arg == NULL) {
        return;
    }

    Unit* unit = (Unit*)unit_arg;

    clear_tile_layers_pixel(game_renderer, unit->x, unit->y);

    free(unit_arg);
}
