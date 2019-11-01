#include <cglm/cglm.h>

#include "Game/Inputs/inputs.h"
#include "Game/Sprite_Batch/sprite_batch.h"
#include "Game/Data/Palette/palette.h"
#include "Game/_game.h"

void add_to_sprite_batch__test_palette(Sprite_Batch* sprite_batch, GLuint texture);

static Animation* test_tile_animation;
static Animation** test_unit_animation;
static GLuint test_texture;

void update_game(Game* game, float delta_time)
{
    update_keys_state();
    update_mouse_buttons_state();
    update_game_clock(game->clock, delta_time);
}

void test_palettes(Game* game)
{

    GLfloat unit_x = 500;
    for (Unit_Variation unit_var = UNIT_VAR_FIRST; unit_var < UNIT_VAR_COUNT; unit_var++) {
        add_to_sprite_batch(
            game->sprite_batches[SPRITES_SPRITE_BATCH], 
            (vec2) { unit_x, 500 }, 
            &(test_unit_animation[Right]->frames[0]),
            get_unit_palette_index(unit_var)
        );
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        unit_x += 25;
    }

    GLfloat tile_x = 500;
    for (Weather weather = WEATHER_FIRST; weather < WEATHER_COUNT; weather++) {
        add_to_sprite_batch(
            game->sprite_batches[SPRITES_SPRITE_BATCH], 
            (vec2) { tile_x, 550 }, 
            &test_tile_animation->frames[0],
            get_tile_palette_index(weather)
        );
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        tile_x += 25;
    }
}

void render_game(Game* game)
{
    // Draw main sprites
    begin_sprite_batch(game->sprite_batches[SPRITES_SPRITE_BATCH]);

    test_palettes(game);

    add_to_sprite_batch__test_palette(game->sprite_batches[SPRITES_SPRITE_BATCH], test_texture);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    end_sprite_batch(game->sprite_batches[SPRITES_SPRITE_BATCH]);
}

void run_game(Game* game)
{
    // Test drawing 
    test_tile_animation = gather_tile_data(
        game->tiles_data, 
        River, Horizontal, 
        NULL, 
        NULL
    );

    test_unit_animation = get_unit_animations(
        game->units_data,
        Bomber,
        OS
    );

    // --------------------------------------------------------------
    static float delta_time = 0.0f;      // Time between current frame and last frame.
    static float last_frame_time = 0.0f; // Time of last frame.

    // Use vSync
    glfwSwapInterval(1);

    // Reset the GLFW timer before starting the game loop
    glfwSetTime(0);

    while (!glfwWindowShouldClose(game->window)) {

        // Update delta time
        float current_frame_time = (float)glfwGetTime();
        delta_time = current_frame_time - last_frame_time;
        last_frame_time = current_frame_time;

        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        update_game(game, delta_time);
        render_game(game);

        glfwSwapBuffers(game->window);
    }
}
