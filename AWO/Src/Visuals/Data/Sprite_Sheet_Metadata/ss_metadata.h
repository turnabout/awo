#pragma once
#include "cJSON.h"

// Holds metadata for a sprite sheet.
typedef struct SS_Metadata
{
    int src_x;
    int src_y;
    int src_w;
    int src_h;
    int dst_w;
    int dst_h;
} SS_Metadata;

// Create a sprite sheet metadata object from a cJSON object.
SS_Metadata* SS_Meta_create_from_JSON(const cJSON* json);

// Free a sprite sheet metadata object.
void SS_Meta_free(SS_Metadata* metadata);
