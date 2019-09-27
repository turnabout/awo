#include <stdio.h>

#include "Visuals/visuals_data.h"
#include "Visuals/visuals_processing.h"
#include "Entities/Unit/unit.h"
#include "Entities/Tile/tile.h"
#include "Game/game.h"

#include "conf.h"

void update_game(Game* game);
void draw_game(Game* game);

#ifdef __EMSCRIPTEN__
void run_game(void* game)
{
    SDL_Event event;

    if (SDL_PollEvent(&event) && event.type == SDL_QUIT) {
        exit_game(game);
        return;
    }

    update_game(game);
    draw_game(game);
}
#else
void run_game(Game* game)
{
    while (1) {
        SDL_Event event;
        Uint32 start_ticks = SDL_GetTicks();

        if (SDL_PollEvent(&event) && event.type == SDL_QUIT) {
            exit_game(game);
            return;
        }

        update_game(game);
        draw_game(game);

        // If frame finished early, wait remaining time
        int frame_ticks = SDL_GetTicks() - start_ticks;

        if (frame_ticks < SCREEN_TICKS_PER_FRAME) {
            SDL_Delay(SCREEN_TICKS_PER_FRAME - frame_ticks);
        }
    }
}
#endif

void update_game(Game* game)
{
    input_state_update();
    GC_update(game->clock);

    tile_selector_update(game->sel, game->mouse_state);
}

void draw_game(Game* game)
{
    SDL_RenderClear(game->rend);

    // Draw all on-screen content
    GB_draw(game->board, game->rend, game->tile_textures[game->current_weather]);

    // Draw UI elements
    tile_selector_draw(game->sel, game->rend, game->tile_textures[game->current_weather]);

    SDL_RenderPresent(game->rend);
}

void draw_unit_test(
    Game* game, 
    SDL_Texture* unit_tex, 
    Unit_Type u_type, 
    Unit_Anim u_anim, 
    int index,
    int x,
    int y
)
{
    /*
    SDL_Rect* frame = &access_unit_dst_anims(u_type)[u_anim]->frames[index];

    SDL_Rect dst;

    dst.x = x;
    dst.y = y;
    dst.n_columns = frame->n_columns;
    dst.n_lines = frame->n_lines;

    SDL_RenderCopy(game->rend, unit_tex, frame, &dst);
*/
}

void draw_armies_test(Game* game)
{
    /*
    // Gather all basic army unit textures
    SDL_Texture* armies[UNIT_VAR_COUNT] = {
        create_units_texture(game, OS, OS),
        create_units_texture(game, BM, BM),
        create_units_texture(game, GE, GE),
        create_units_texture(game, YC, YC),
        create_units_texture(game, BH, BH)
    };

    SDL_SetRenderDrawColor(game->rend, 255, 255, 255, 255);
    SDL_RenderClear(game->rend);

    // draw_unit_test(game, armies[OS], Tank, Idle, 0, 120, 120);

    // Draw every unit of every army
    int col_size = 20;
    int row_size = 20;

    for (Unit_Var v = UNIT_VAR_FIRST; v <= UNIT_VAR_LAST; v++) {
        for (Unit_Type u = UNIT_TYPE_FIRST; u <= UNIT_TYPE_LAST; u++) {
            draw_unit_test(game, armies[v], u, Idle, 0, u * col_size, v * row_size);
        }
    }

    // Draw a second group, darkened for "done" units
    for (Unit_Var v = UNIT_VAR_FIRST; v <= UNIT_VAR_LAST; v++) {
        // SDL_SetTextureAlphaMod(armies[v], 250);
        SDL_SetTextureColorMod(armies[v], 137, 137, 137);
    }

    int group_2_start_y = (UNIT_VAR_LAST + 2) * row_size;

    for (Unit_Var v = UNIT_VAR_FIRST; v <= UNIT_VAR_LAST; v++) {
        for (Unit_Type u = UNIT_TYPE_FIRST; u <= UNIT_TYPE_LAST; u++) {
            draw_unit_test(game, armies[v], u, Idle, 0, u * col_size, group_2_start_y + (v * row_size));
        }
    }

    // Draw every units texture
    int units_start_y = group_2_start_y * 2;
    int tex_w, tex_h;

    // Reset the darkened color mod
    for (Unit_Var v = UNIT_VAR_FIRST; v <= UNIT_VAR_LAST; v++) {
        SDL_SetTextureColorMod(armies[v], 255, 255, 255);
    }

    SDL_QueryTexture(armies[OS], NULL, NULL, &tex_w, &tex_h);

    for (Unit_Var v = UNIT_VAR_FIRST; v <= UNIT_VAR_LAST; v++) {
        SDL_Rect dst = {tex_w * v, units_start_y, tex_w, tex_h};
        SDL_RenderCopy(game->rend, armies[v], NULL, &dst);
    }

    SDL_RenderPresent(game->rend);
*/
}
