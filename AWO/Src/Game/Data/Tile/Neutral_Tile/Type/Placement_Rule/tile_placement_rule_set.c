#include <stdlib.h>

#include "Game/Data/Tile/Neutral_Tile/Type/Placement_Rule/_tile_placement_rule.h"

Tile_Placement_Rule_Set* create_tile_placement_rule_set(cJSON* JSON)
{
    Tile_Placement_Rule_Set* rule_set = malloc(sizeof(Tile_Placement_Rule_Set));

    if (rule_set == NULL) {
        return NULL;
    }

    // Get the count of rules in this set
    rule_set->rule_count = cJSON_GetArraySize(JSON);

    if (rule_set->rule_count < 1) {
        free_tile_placement_rule_set(rule_set);
        return NULL;
    } else {
        rule_set->rules = malloc(sizeof(Tile_Placement_Rule*) * rule_set->rule_count);
    }

    // Get the rules themselves
    for (int i = 0; i < rule_set->rule_count; i++) {
        rule_set->rules[i] = create_tile_placement_rule(
            cJSON_GetArrayItem(JSON, i)
        );
    }

    return rule_set;
}

void free_tile_placement_rule_set(Tile_Placement_Rule_Set* rule_set)
{
    if (rule_set == NULL) {
        return;
    }

    if (rule_set->rules != NULL) {
        for (int i = 0; i < rule_set->rule_count; i++) {
            free_tile_placement_rule(rule_set->rules[i]);
        }

        free(rule_set->rules);
    }

    free(rule_set);
}
