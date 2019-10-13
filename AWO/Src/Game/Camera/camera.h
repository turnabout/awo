#pragma once

// Represents the game's camera viewport.
typedef struct Game_Camera Game_Camera;

// Creates the game camera instance.
Game_Camera* create_Game_Camera(int game_w, int game_h);

// Zooms the game camera.
void zoom_Game_Camera(Game_Camera* camera, int scale);