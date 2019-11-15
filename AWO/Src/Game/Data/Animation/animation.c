#include <stdio.h>
#include <stdlib.h>
#include <cglm/cglm.h>

#include "conf.h"
#include "Game/Data/Animation/animation.h"

void create_animation_frame(Frame* frame_ptr, const cJSON* frame_JSON, float ss_width, float ss_height)
{
    // Gather dimensions
    float x = (float)cJSON_GetObjectItemCaseSensitive(frame_JSON, "x")->valueint;
    float y = (float)cJSON_GetObjectItemCaseSensitive(frame_JSON, "y")->valueint;

    Uint8 w = (cJSON_HasObjectItem(frame_JSON, "w"))
                ? cJSON_GetObjectItemCaseSensitive(frame_JSON, "w")->valueint
                : DEFAULT_TILE_SIZE;

    Uint8 h = (cJSON_HasObjectItem(frame_JSON, "h"))
                ? cJSON_GetObjectItemCaseSensitive(frame_JSON, "h")->valueint
                : DEFAULT_TILE_SIZE;

    frame_ptr->width = w;
    frame_ptr->height = h;

    vec4 top_left     = { (x    ) / ss_width, (y)     / ss_height, 0.0f, 1.0f };
    vec4 top_right    = { (x + w) / ss_width, (y)     / ss_height, 0.0f, 1.0f };
    vec4 bottom_left  = { (x    ) / ss_width, (y + h) / ss_height, 0.0f, 1.0f };
    vec4 bottom_right = { (x + w) / ss_width, (y + h) / ss_height, 0.0f, 1.0f };

    vec2 raw_top_left = { x, y };

    glm_vec4_copy(top_left, frame_ptr->top_left);
    glm_vec4_copy(top_right, frame_ptr->top_right);
    glm_vec4_copy(bottom_left, frame_ptr->bottom_left);
    glm_vec4_copy(bottom_right, frame_ptr->bottom_right);

    frame_ptr->raw_top_left[0] = raw_top_left[0];
    frame_ptr->raw_top_left[1] = raw_top_left[1];
}

Animation* create_animation(const cJSON* animation_JSON, int ss_width, int ss_height)
{
    Animation* animation = malloc(sizeof(Animation));

    animation->count = cJSON_GetArraySize(animation_JSON);
    Frame* frames = (Frame*)malloc( sizeof(Frame) * animation->count );

    // Gather data from every frame and populate the allocated frames
    cJSON* frame_JSON = NULL;
    cJSON_ArrayForEach(frame_JSON, animation_JSON)
    {
        create_animation_frame(frames, frame_JSON, (float)ss_width, (float)ss_height);
        frames++;
    }

    animation->frames = frames - animation->count;
    return animation;

}

void free_animation(Animation* animation)
{
    free(animation->frames);
    free(animation);
}

#ifdef _DEBUG
void print_animation(Animation* animation)
{
    printf("\nFrames [\n");

    for (int i = 0; i < animation->count; i++) {
        printf("\t{\n");
        printf("\tTop left\n\t");
        glm_vec3_print(animation->frames->top_left, stdout);

        printf("\tTop right\n\t");
        glm_vec3_print(animation->frames->top_right, stdout);

        printf("\tBottom left\n\t");
        glm_vec3_print(animation->frames->bottom_left, stdout);

        printf("\tBottom right\n\t");
        glm_vec3_print(animation->frames->bottom_right, stdout);
        
        printf(
            "\t(Dimensions): %d | %d\n", 
            animation->frames->width, 
            animation->frames->height
        );

        printf("\t},\n");
    }

    printf("]\n");
}
#endif
