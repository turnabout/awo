#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Game/Data/Tile/tiles_data.h"
#include "Game/Data/Unit/units_data.h"

/*! @brief Module used to retrieve texture data for individual entities, with palettes applied.
 */
typedef struct Entity_Texture_Reader Entity_Texture_Reader;

/*! @brief Creates an entity texture reader.
 *
 *  @param[in] tiles_data Reference to the game's tiles data module.
 *  @param[in] units_data Reference to the game's units data module.
 *  @param[in] game_raw_palette The game's raw palette texture.
 *  @param[in] sprite_sheet The game's sprite sheet texture.
 *  @param[in] sprite_sheet_w Sprite sheet's width.
 *  @param[in] sprite_sheet_h Sprite sheet's height.
 *  @return The created entity texture reader.
 */
Entity_Texture_Reader* create_entity_texture_reader(
    Tiles_Data* tiles_data,
    Units_Data* units_data,
    GLuint game_raw_palette,
    GLuint sprite_sheet,
    int sprite_sheet_w,
    int sprite_sheet_h
);

/*! @brief Reads the texture of a neutral tile and returns its pixel data in a new buffer.
 *
 *  @param[in] reader The entity texture reader.
 *  @param[in] type The type of the tile to read.
 *  @param[in] variation The variation of the tile to read.
 *  @param[in] weather The weather palette to apply to the tile.
 *  @param[out] texture_w Filled in with the width of the read texture.
 *  @param[out] texture_h Filled in with the width of the read texture.
 */
Uint8* read_neutral_tile_texture(
    Entity_Texture_Reader* reader,
    Tile_Type type,
    Tile_Variation variation,
    Weather weather,
    int* texture_w,
    int* texture_h
);

/*! @brief Frees an entity texture reader's memory.
 *
 *  @param[in] reader The reader to free.
 */
void free_entity_texture_reader(Entity_Texture_Reader* reader);
