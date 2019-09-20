#include <stdlib.h>
#include "ss_metadata.h"

#pragma warning( disable : 6011 )

struct SS_Metadata
{
    int src_x;
    int src_y;
    int src_w;
    int src_h;
    int dst_w;
    int dst_h;
};

SS_Metadata* SS_Meta_create_from_JSON(const cJSON* json)
{
    // Attempt to get every possible field from the given JSON object
    SS_Metadata* metadata = malloc(sizeof(SS_Metadata));

    // Source fields
    if (cJSON_HasObjectItem(json, "srcX")) {
        metadata->src_x = cJSON_GetObjectItemCaseSensitive(json, "srcX")->valueint;
    }

    if (cJSON_HasObjectItem(json, "srcY")) {
        metadata->src_y = cJSON_GetObjectItemCaseSensitive(json, "srcY")->valueint;
    }

    if (cJSON_HasObjectItem(json, "srcWidth")) {
        metadata->src_w = cJSON_GetObjectItemCaseSensitive(json, "srcWidth")->valueint;
    }

    if (cJSON_HasObjectItem(json, "srcHeight")) {
        metadata->src_h = cJSON_GetObjectItemCaseSensitive(json, "srcHeight")->valueint;
    }

    // Destination fields
    if (cJSON_HasObjectItem(json, "dstWidth")) {
        metadata->dst_w = cJSON_GetObjectItemCaseSensitive(json, "dstWidth")->valueint;
    }

    if (cJSON_HasObjectItem(json, "dstHeight")) {
        metadata->dst_h = cJSON_GetObjectItemCaseSensitive(json, "dstHeight")->valueint;
    }

    return metadata;
}

void SS_Meta_free(SS_Metadata* metadata)
{
    free(metadata);
}
