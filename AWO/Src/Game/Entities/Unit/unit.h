#include "Game/game.h"
#include "Visuals/Data/Units/units_data.h"

typedef struct Unit Unit;

// Create a unit entity.
Unit* unit_create(Game* game, SDL_Texture* src_texture, unit_type u_type);

// Update a unit.
void unit_update(Unit* u);

// Draw a unit.
void unit_draw(Unit* u);
