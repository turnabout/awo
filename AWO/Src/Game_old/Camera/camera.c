#include <SDL.h>
#include "camera.h"

struct Game_Camera {
    SDL_Rect rect;  // Rectangle delimiting the camera's current viewport.
};

Game_Camera* create_Game_Camera(int game_w, int game_h)
{
    Game_Camera* camera = malloc(sizeof(Game_Camera));

    // Initialize to be the game's full dimensions
    SDL_Rect rect = {
        0, 0, game_w, game_h
    };

    camera->rect = rect;

    return camera;
}

void zoom_Game_Camera(Game_Camera* camera, int scale)
{
    // TODO
}