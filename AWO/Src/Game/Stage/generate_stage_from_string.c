#include "Utilities/utilities.h"
#include "Game/Stage/_stage.h"

void load_stage_name(Uint8* stage_data, size_t* i, char* stage_name)
{
    while (1) {
        if (stage_data[*i] == STAGE_STRING_SEPARATOR_CHARACTER) {
            stage_name[*i] = '\0';
            (*i)++;
            break;
        }

        stage_name[*i] = stage_data[*i];
        (*i)++;
    }
}

void load_stage_players_data(
    Uint8* stage_data, 
    size_t* i, 
    Army_Type player_armies[MAX_PLAYER_COUNT]
)
{
    Uint8 player_i = 0;

    // Initialize player armies to NONE
    for (int j = 0; j < MAX_PLAYER_COUNT; j++) {
        player_armies[j] = ARMY_TYPE_NONE;
    }

    // Process player armies from stage data
    while (1) {

        Army_Type player_army = stage_data[(*i)++];

        if (player_army == STAGE_STRING_SEPARATOR_CHARACTER) {
            break;
        }

        player_armies[player_i++] = player_army;
    }
}

Stage* generate_stage_from_string(char* stage_str, Tiles_Data* tiles_data)
{
    // Translate the hex string into a useable data bytes array & validate
    Uint8* stage_data;
    size_t data_length;
 
    if ((stage_data = hex_string_to_data(stage_str, &data_length)) == NULL || 
         !validate_stage_string_data(stage_data, data_length, tiles_data)
    ) {
        return NULL;
    }

    size_t i = 0;

    // Load stage name
    char stage_name[STAGE_NAME_MAX_LENGTH];
    load_stage_name(stage_data, &i, stage_name);

    // Load players data
    Army_Type player_armies[MAX_PLAYER_COUNT];
    load_stage_players_data(stage_data, &i, player_armies);

    // Create empty stage
    Stage* stage = create_stage(
        stage_name,
        stage_data[i++], // Width
        stage_data[i++], // Height
        player_armies
    );

    i++; // Point index after the separator

    // Load tiles
    for (Uint8 y = 0; y < stage->height; y++) {
        for (Uint8 x = 0; x < stage->width; x++) {
            edit_stage_tile(stage, x, y, stage_data[i], stage_data[i + 1]);
            i += 2;
        }
    }

    return stage;
}

