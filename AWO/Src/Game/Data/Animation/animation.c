#include <stdio.h>
#include <stdlib.h>
#include <cglm/cglm.h>

#include "conf.h"
#include "Game/Data/Animation/animation.h"

void create_animation_frame(Frame* frame_ptr, const cJSON* frame_JSON, mat4 projection)
{
    // Gather dimensions
    float x = (float)cJSON_GetObjectItemCaseSensitive(frame_JSON, "x")->valueint;
    float y = (float)cJSON_GetObjectItemCaseSensitive(frame_JSON, "y")->valueint;

    float w = (cJSON_HasObjectItem(frame_JSON, "w"))
                ? (float)cJSON_GetObjectItemCaseSensitive(frame_JSON, "w")->valueint
                : (float)DEFAULT_TILE_DIMENSION;

    float h = (cJSON_HasObjectItem(frame_JSON, "h"))
                ? (float)cJSON_GetObjectItemCaseSensitive(frame_JSON, "h")->valueint
                : (float)DEFAULT_TILE_DIMENSION;

    frame_ptr->dimensions[0] = w;
    frame_ptr->dimensions[1] = h;

    vec4 top_left     = { x,     y,     0.0f, 1.0f };
    vec4 top_right    = { x + w, y,     0.0f, 1.0f };
    vec4 bottom_left  = { x,     y + h, 0.0f, 1.0f };
    vec4 bottom_right = { x + w, y + h, 0.0f, 1.0f };

    // Transform frame data into Normalized Device Coordinates
    glm_mat4_mulv(projection, top_left, top_left);
    glm_mat4_mulv(projection, top_right, top_right);
    glm_mat4_mulv(projection, bottom_left, bottom_left);
    glm_mat4_mulv(projection, bottom_right, bottom_right);

    // Texture coordinates are mapped between 0,0 and 1,1.
    // The above transformation leaves us with coordinates between -1,-1 and 1,1, so we need
    // to transform them so they all fit between 0,0 and 1,1.
    // Dividing each vertex by 2 and adding 0.5 does the trick.
    top_left[0]     = (top_left[0] / 2) + 0.50f;
    top_left[1]     = (top_left[1] / 2) + 0.50f;
    top_right[0]    = (top_right[0] / 2) + 0.50f;
    top_right[1]    = (top_right[1] / 2) + 0.50f;
    bottom_left[0]  = (bottom_left[0] / 2) + 0.50f;
    bottom_left[1]  = (bottom_left[1] / 2) + 0.50f;
    bottom_right[0] = (bottom_right[0] / 2) + 0.50f;
    bottom_right[1] = (bottom_right[1] / 2) + 0.50f;

    glm_vec4_copy(top_left, frame_ptr->top_left);
    glm_vec4_copy(top_right, frame_ptr->top_right);
    glm_vec4_copy(bottom_left, frame_ptr->bottom_left);
    glm_vec4_copy(bottom_right, frame_ptr->bottom_right);
}

Animation* create_animation(const cJSON* animation_JSON, mat4 projection)
{
    Animation* animation = malloc(sizeof(Animation));

    animation->count = cJSON_GetArraySize(animation_JSON);
    Frame* frames = (Frame*)malloc( sizeof(Frame) * animation->count );

    // Gather data from every frame and populate the allocated frames
    cJSON* frame_JSON = NULL;
    cJSON_ArrayForEach(frame_JSON, animation_JSON)
    {
        create_animation_frame(frames, frame_JSON, projection);
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
            "\t(Dimensions): %.2f | %.2f\n", 
            animation->frames->dimensions[0], 
            animation->frames->dimensions[1]
        );

        printf("\t},\n");
    }

    printf("]\n");
}
#endif
