#include <cglm/cglm.h>

#include "Game/_game.h"
#include "Game/Data/Palette/game_palette.h"

#include "Game/Renderer/Sprite_Batch/sprite_batch.h"
#include "GL_Helpers/gl_helpers.h"

static GLfloat scale = 16.0f;
Sprite_Batch* sb;

mat4 view = GLM_MAT4_IDENTITY_INIT;
mat4 project = GLM_MAT4_IDENTITY_INIT;

void render_game(Game* game)
{
    static int flag = 0;
    static Frame* frame;

    if (!flag) {
        // Get test frame
        Animation* test = get_UI_element_frames(game->UI_data, TileCursor);
        frame = &test->frames[0];

        /*
        // Matrices
        glm_ortho(
            0.0f, 
            (float)game->window_width, 
            (float)game->window_height, 
            0.0f, 
            -1.0f, 
            1.0f, 
            project
        );

        glm_translate(
            view,
            (vec3) { (float)0, (float)0, 0.0f }
        );

        glm_scale(
            view,
            (vec3) { 2.0f, 2.0f, 1.0f }
        );


        // Create shader/ss texture
        GLuint shader_program = create_shader_program(
            SHADERS_PATH "sprite.vert",
            SHADERS_PATH "sprite.frag"
        );

        int ss_width, ss_height;
        GLuint ss_tex = create_texture_object(
            SPRITE_SHEET_PATH, 
            &ss_width, 
            &ss_height
        );

        glUseProgram(shader_program);

        // Set uniforms
        glUniformMatrix4fv(
            glGetUniformLocation(shader_program, "projection"), 
            1, 
            GL_FALSE, 
            project[0]
        );

        glUniformMatrix4fv(
            glGetUniformLocation(shader_program, "view"), 
            1, 
            GL_FALSE, 
            view[0]
        );

        // Sprite batch
        sb = create_sprite_batch(shader_program, ss_tex, 0, 10);
        */
        
        flag = 1;
    }



    // begin_sprite_batch(sb);
    // add_to_sprite_batch__test_palette(sb);
    // add_to_sprite_batch(sb, (vec2) { 25.0, 25.0 }, frame, 17);
    // end_sprite_batch(sb);


    /*
    batch_sprite(
        (vec2){0.0, 0.0},
        frame,
        0
    );

    */

    // Render the main grids
    render_game_renderer_grids(game->renderer);

    // Queue extras for render
    // render_pointer(game->pointer, game->renderer);
    // queue_extra(game->renderer, (vec2) { 85.0, 0.0 }, frame);

    render_extras(game->renderer);


    /*
    if (get_key_state(KEY_A) == BUTTON_DOWN_START) {
        update_active_tile_palette(Clear, game->palette_texture, game->raw_palette_texture);
    }

    if (get_key_state(KEY_S) == BUTTON_DOWN_START) {
        update_active_tile_palette(Rain, game->palette_texture, game->raw_palette_texture);
    }

    if (get_key_state(KEY_D) == BUTTON_DOWN_START) {
        update_active_tile_palette(Snow, game->palette_texture, game->raw_palette_texture);
    }

    if (get_key_state(KEY_1) == BUTTON_DOWN_START) {
        update_game_palette_property_lights(game->palette_texture, TRUE);
    }

    if (get_key_state(KEY_2) == BUTTON_DOWN_START) {
        update_game_palette_property_lights(game->palette_texture, FALSE);
    }
    */

    // Draw main sprites
    // begin_sprite_batch(game->sprite_batches[SPRITES_SPRITE_BATCH]);
    // draw_game_board(game->board, game->sprite_batches[SPRITES_SPRITE_BATCH]);
    // end_sprite_batch(game->sprite_batches[SPRITES_SPRITE_BATCH]);
}
