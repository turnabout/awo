#include <stdio.h>
#include <SDL.h>

#include "conf.h"
#include "animation.h"

#pragma warning( disable : 6011 )

struct Animation {
    int count;
    SDL_Rect* frames;
};

Animation* anim_create_from_JSON(const cJSON* anim_json)
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

SDL_Rect* anim_get_frames(Animation* anim, int* count)
{
    if (count != NULL) {
        *count = anim->count;
    }

    return anim->frames;
}

void anim_free(Animation* anim)
{
    // TODO
}

#ifdef _DEBUG
void anim_print(Animation* anim)
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
#endif
