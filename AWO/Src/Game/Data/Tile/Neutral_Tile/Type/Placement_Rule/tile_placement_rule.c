#include <stdlib.h>

#include "Game/Data/Tile/Neutral_Tile/Type/Placement_Rule/_tile_placement_rule.h"

Tile_Placement_Rule* create_tile_placement_rule(cJSON* JSON)
{
    Tile_Placement_Rule* rule = malloc(sizeof(Tile_Placement_Rule));

    if (rule == NULL) {
        return NULL;
    }

    // Get amount of components
    rule->component_count = cJSON_GetArraySize(JSON);

    if (rule->component_count < 1) {
        free_tile_placement_rule(rule);
        return NULL;
    }

    // Allocate space for components
    rule->components = malloc(sizeof(Tile_Placement_Rule_Component) * rule->component_count);

    if (rule->components == NULL) {
        free_tile_placement_rule(rule);
        return NULL;
    }

    // Set all components' values
    for (int i = 0; i < rule->component_count; i++) {
        cJSON* component_JSON = cJSON_GetArrayItem(JSON, i);

        rule->components[i].offset_x = cJSON_GetObjectItem(component_JSON, "offsetX")->valueint;
        rule->components[i].offset_y = cJSON_GetObjectItem(component_JSON, "offsetY")->valueint;
        rule->components[i].blocked_tiles = cJSON_GetObjectItem(component_JSON, "tiles")->valueint;
    }

    return rule;
}

void free_tile_placement_rule(Tile_Placement_Rule* rule)
{
    if (rule == NULL) {
        return;
    }

    if (rule->components != NULL) {
        free(rule->components);
    }

    free(rule);
}