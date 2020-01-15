#pragma once

#include "Include/types.h"
#include "Include/Game_Data/game_data.h"

/*! @brief Module used to retrieve texture data for individual entities, with palettes applied.
 */
typedef struct Entity_Texture_Reader Entity_Texture_Reader;

/*! @brief Creates an entity texture reader.
 *
 *  @param[in] game_data Reference to the game data module.
 *  @return The created entity texture reader.
 */
Entity_Texture_Reader* create_entity_texture_reader(Game_Data* game_data);

/*! @brief Reads the texture of a neutral tile and returns its pixel data in a new buffer.
 *
 *  @param[in] reader The entity texture reader.
 *  @param[in] type The type of the tile to read.
 *  @param[in] variation The variation of the tile to read.
 *  @param[in] weather The weather palette to apply to the tile.
 *  @param[out] texture_w Filled in with the width of the read texture.
 *  @param[out] texture_h Filled in with the height of the read texture.
 */
/*
Uint8* read_neutral_tile_texture(
    Entity_Texture_Reader* reader,
    Tile_Type type,
    Tile_Variation variation,
    Weather weather,
    int* texture_w,
    int* texture_h
);
*/

/*! @brief Frees an entity texture reader's memory.
 *
 *  @param[in] reader The reader to free.
 */
void free_entity_texture_reader(Entity_Texture_Reader* reader);