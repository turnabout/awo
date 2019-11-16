#include <stdlib.h>
#include <cglm/cglm.h>

#include "conf.h"
#include "Game/Data/Animation/Frame/_frame.h"

Frame* create_frame(const cJSON* frame_JSON, int ss_width, int ss_height)
{
    Frame* frame = (Frame*)malloc(sizeof(Frame));
    populate_frame(frame, frame_JSON, (float)ss_width, (float)ss_height);

    return frame;
}

void populate_frame(
    Frame* frame_ptr,
    const cJSON* frame_JSON,
    float ss_width,
    float ss_height
)
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
