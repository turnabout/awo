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

    // Gather data on this unit
    // Animation** get_unit_animations(Units_Data* units_data, Unit_Type type, Army_Type variation)

    unit->type = type;

    // Set callbacks
    unit->update_grid = update_unit_render_grid;
    unit->update_palette = update_unit_palette;
    unit->delete = delete_unit;

    return unit;
}