#include <cglm/cglm.h>

#include "Game/_game.h"
#include "Game/Sprite_Batch/sprite_batch.h"

static Animation* test_animation;

void update_game(Game* game, float delta_time)
{
}

void render_game(Game* game)
{
    // Draw main sprites
    begin_sprite_batch(game->sprite_batches[SPRITES_SPRITE_BATCH]);

    add_to_sprite_batch(
        game->sprite_batches[SPRITES_SPRITE_BATCH], 
        (vec2) { 0, 0 }, 
        &test_animation->frames[0]
    );
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    end_sprite_batch(game->sprite_batches[SPRITES_SPRITE_BATCH]);
}

void run_game(Game* game)
{
    // Test drawing 
    test_animation = gather_tile_data(
        game->tiles_data, 
        Sea, Middle, 
        NULL, 
        NULL
    );

    static float delta_time = 0.0f;      // Time between current frame and last frame.
    static float last_frame_time = 0.0f; // Time of last frame.

    glfwSwapInterval(1);

    while (!glfwWindowShouldClose(game->window)) {

        // Update delta time
        float current_frame_time = (float)glfwGetTime();
        delta_time = current_frame_time - last_frame_time;
        last_frame_time = current_frame_time;

        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        render_game(game);

        glfwSwapBuffers(game->window);
    }
}
