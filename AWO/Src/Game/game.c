#include "Visuals/visuals_data.h"
#include "Visuals/visuals_processing.h"
#include "game.h"

void draw_tiles_test(Game* game);
void draw_armies_test(Game* game);

void run_game(Game* game)
{
    // draw_tiles_test(&game);
    // draw_armies_test(&game);
    UD_print(game->ud, UD_DST);

    while (1) {
        SDL_Event event;
        Uint32 start_ticks = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                exit_game(game);
                return;
            }
        }

        // If frame finished early, wait remaining time
        int frame_ticks = SDL_GetTicks() - start_ticks;

        if (frame_ticks < SCREEN_TICKS_PER_FRAME) {
            SDL_Delay(SCREEN_TICKS_PER_FRAME - frame_ticks);
        }
    }
}

void draw_unit_test(
    Game* game, 
    SDL_Texture* unit_tex, 
    unit_type u_type, 
    unit_anim u_anim, 
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
    dst.w = frame->w;
    dst.h = frame->h;

    SDL_RenderCopy(game->rend, unit_tex, frame, &dst);
*/
}

void draw_armies_test(Game* game)
{
    /*
    // Gather all basic army unit textures
    SDL_Texture* armies[UNIT_VAR_AMOUNT] = {
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

    for (unit_var v = UNIT_VAR_FIRST; v <= UNIT_VAR_LAST; v++) {
        for (unit_type u = UNIT_TYPE_FIRST; u <= UNIT_TYPE_LAST; u++) {
            draw_unit_test(game, armies[v], u, Idle, 0, u * col_size, v * row_size);
        }
    }

    // Draw a second group, darkened for "done" units
    for (unit_var v = UNIT_VAR_FIRST; v <= UNIT_VAR_LAST; v++) {
        // SDL_SetTextureAlphaMod(armies[v], 250);
        SDL_SetTextureColorMod(armies[v], 137, 137, 137);
    }

    int group_2_start_y = (UNIT_VAR_LAST + 2) * row_size;

    for (unit_var v = UNIT_VAR_FIRST; v <= UNIT_VAR_LAST; v++) {
        for (unit_type u = UNIT_TYPE_FIRST; u <= UNIT_TYPE_LAST; u++) {
            draw_unit_test(game, armies[v], u, Idle, 0, u * col_size, group_2_start_y + (v * row_size));
        }
    }

    // Draw every units texture
    int units_start_y = group_2_start_y * 2;
    int tex_w, tex_h;

    // Reset the darkened color mod
    for (unit_var v = UNIT_VAR_FIRST; v <= UNIT_VAR_LAST; v++) {
        SDL_SetTextureColorMod(armies[v], 255, 255, 255);
    }

    SDL_QueryTexture(armies[OS], NULL, NULL, &tex_w, &tex_h);

    for (unit_var v = UNIT_VAR_FIRST; v <= UNIT_VAR_LAST; v++) {
        SDL_Rect dst = {tex_w * v, units_start_y, tex_w, tex_h};
        SDL_RenderCopy(game->rend, armies[v], NULL, &dst);
    }

    SDL_RenderPresent(game->rend);
*/
}


void draw_tiles_test(Game* game)
{
    // debug_print_tile_data(Plain);
    // debug_print_tile_data(Shore);
    // debug_print_tile_data(Sea);
}