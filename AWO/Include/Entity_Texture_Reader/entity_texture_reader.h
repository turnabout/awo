#pragma once

/*! @brief Reads the texture data from a game entity.
 *
 *  @note The returned buffer must be freed by the user.
 *
 *  @param[in] reader The entity texture reader instance.
 *  @param[in] kind The kind of the game entity to read from.
 *  @param[in] type The type of the entity. Tile_Type/Property_Type/Unit_Type
 *  @param[in] variation The variation of the entity. Determines the visual style to get.
 *  For neutral tiles: Tile_Variation. For properties & units: Army_Variation.
 *  @param[in] palette_variation The palette variation. Determines the colors applied.
 *  For neutral tiles: Weather. For properties & units: Army_Variation.
 *
 *  @param[out] texture_width The loaded texture's width.
 *  @param[out] texture_height The loaded texture's height.
 *  @return Buffer containing the entity's texture data.
 */
/*
unsigned char* read_game_entity_texture(
    Entity_Texture_Reader* reader,
    Entity_Kind kind,
    int type,
    int variation,
    int palette_variation,
    int* texture_width,
    int* texture_height
);
*/