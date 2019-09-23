#include "conf.h"
#include "Game/Entities/Unit/unit.h"
#include "game_board.h"

#pragma warning( disable : 6011 )

struct Game_Board {
    int w, h;     // Dimensions of full game board

    Unit** units; // Contains all units on the game board.
    int u_count;  // How many units are on the game board.
};

Game_Board* GB_create()
{
    Game_Board* gb = malloc(sizeof(Game_Board));

    gb->u_count = 0;
    gb->units = malloc(sizeof(Unit*) * MAX_UNITS_PER_ARMY);

    return gb;
}

void GB_add_unit(Game_Board* gb, Unit* u)
{
    gb->units[gb->u_count] = u;
    gb->u_count++;
}

void GB_update(Game_Board* gb)
{
}

void GB_draw(Game_Board* gb, SDL_Renderer* rend)
{
    // Draw units
    for (int i = 0; i < gb->u_count; i++) {
        unit_draw(gb->units[i], rend);
    }
}

void GB_free(Game_Board* gb)
{
    free(gb);

    // TODO: Free all entities belonging to game board
}