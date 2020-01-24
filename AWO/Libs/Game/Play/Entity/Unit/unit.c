#include <stdlib.h>

#include "Game/Entity/Unit/_unit.h"

Unit* create_unit(
    Game_Clock* game_clock,
    Units_Data* units_data,
    Unit_Type type,
    Player* player,
    Uint8 x,
    Uint8 y
)
{
    Unit* unit = malloc(sizeof(Unit));

    // Set unit data
    unit->x = x;
    unit->y = y;
    unit->type = type;
    unit->player = player;

    unit->idle_animation = get_unit_animation(
        units_data,
        type,
        player->CO->army,
        Unit_Idle
    );

    // Set callbacks
    unit->update_grid = update_unit_render_grid;
    unit->update_palette = update_unit_palette;
    unit->delete = delete_unit;

    return unit;
}