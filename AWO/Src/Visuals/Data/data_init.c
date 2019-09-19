#include <SDL.h>
#include <stdio.h>

#include "conf.h"

#include "JSON/JSON_access.h"
#include "Units/units_data.h"
#include "Tiles/tiles_data.h"
#include "../data_access.h"

#pragma warning( disable : 6011 )


int init_visuals_data_structure(void)
{
    // Load visuals JSON contents into cJSON struct
    const cJSON* visuals_JSON;

    if (load_visuals_JSON(&visuals_JSON) == ERR) {
        return ERR;
    }

    // Load cJSON into the visuals data structures
    init_units_visual_data_structure(cJSON_GetObjectItemCaseSensitive(visuals_JSON, "units"));
    init_tiles_visual_data_structure(cJSON_GetObjectItemCaseSensitive(visuals_JSON, "tiles"));

    return OK;
}

Animation* get_JSON_anim(const cJSON* anim_json)
{
    Animation* anim = malloc(sizeof(Animation));

    anim->count = cJSON_GetArraySize(anim_json);
    SDL_Rect* frames = (SDL_Rect*)malloc(
        sizeof(SDL_Rect) * anim->count
    );

    cJSON* frame_json = NULL;

    // Gather data from every frame and populate the allocated frames
    cJSON_ArrayForEach(frame_json, anim_json)
    {
        frames->x = (cJSON_HasObjectItem(frame_json, "x"))
                        ? cJSON_GetObjectItemCaseSensitive(frame_json, "x")->valueint
                        : DEFAULT_TILE_DIMENSION;

        frames->y = (cJSON_HasObjectItem(frame_json, "y"))
                        ? cJSON_GetObjectItemCaseSensitive(frame_json, "y")->valueint
                        : DEFAULT_TILE_DIMENSION;

        frames->w = (cJSON_HasObjectItem(frame_json, "w"))
                        ? cJSON_GetObjectItemCaseSensitive(frame_json, "w")->valueint
                        : DEFAULT_TILE_DIMENSION;

        frames->h = (cJSON_HasObjectItem(frame_json, "h"))
                        ? cJSON_GetObjectItemCaseSensitive(frame_json, "h")->valueint
                        : DEFAULT_TILE_DIMENSION;

        frames++;
    }

    anim->frames = frames - anim->count;
    return anim;
}

void print_anim_contents(Animation* anim)
{
    printf("\n[\n");
    for (int i = 0; i < anim->count; i++) {
        printf(
            "{x: %d, y: %d, w: %d, h: %d},\n", 
            anim->frames[i].x,
            anim->frames[i].y,
            anim->frames[i].w,
            anim->frames[i].h
        );

    }
    printf("]\n");
}