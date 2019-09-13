#include <stdio.h>

#include "JSON.h"
#include "load_units.h"
#include "../visuals_structure.h"
#include "../../conf.h"

#pragma warning( disable : 6011 )

int load_visuals_data_structure(void)
{
    // Load visuals JSON contents into cJSON struct
    const cJSON* visuals_JSON;

    if (load_visuals_JSON(&visuals_JSON) == ERR) {
        return ERR;
    }

    // Load cJSON into the visuals data structure
    load_units_visual_data_structure(cJSON_GetObjectItemCaseSensitive(visuals_JSON, "units"));

    return OK;
}

Animation* get_anim(const cJSON* anim_json)
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
        frames->x = cJSON_GetObjectItemCaseSensitive(frame_json, "x")->valueint;
        frames->y = cJSON_GetObjectItemCaseSensitive(frame_json, "y")->valueint;
        frames->w = cJSON_GetObjectItemCaseSensitive(frame_json, "w")->valueint;
        frames->h = cJSON_GetObjectItemCaseSensitive(frame_json, "h")->valueint;

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