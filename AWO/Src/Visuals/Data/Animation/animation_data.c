#include <stdio.h>
#include <SDL.h>

#include "animation_data.h"

#pragma warning( disable : 6011 )

struct Animation_Data
{
    int count;
    SDL_Rect* frames;
};

Animation_Data* AD_create_from_JSON(const cJSON* anim_json)
{
    Animation_Data* anim = malloc(sizeof(Animation_Data));

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

void AD_free(Animation_Data* ad)
{
    // TODO
}

void AD_print(Animation_Data* ad)
{
    printf("\n[\n");
    for (int i = 0; i < ad->count; i++) {
        printf(
            "{x: %d, y: %d, w: %d, h: %d},\n", 
            ad->frames[i].x,
            ad->frames[i].y,
            ad->frames[i].w,
            ad->frames[i].h
        );

    }
    printf("]\n");
}
