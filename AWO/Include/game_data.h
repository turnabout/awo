#pragma once

#include "game.h"

/*! @brief Module used to retrieve texture data for individual entities, with palettes applied.
 *  Can be used to get pixel data from AWO game entities.
 */
typedef struct Entity_Texture_Reader Entity_Texture_Reader;

/*! @brief Every existing kind of game entity.
 */
typedef enum Entity_Kind {
    Entity_Kind_Neutral_Tile,
    Entity_Kind_Property,
    Entity_Kind_Unit,
} Entity_Kind;

/*! @brief Gets the next neutral tile type.
 *
 *  @note Must be called continuously until it returns NULL.
 *
 *  @param[out] type Filled in with the neutral tile type's value.
 *  @return The tile type's string.
 */
const char* get_next_game_tile_type(int* type);

/*! @brief Gets the next neutral tile variation for a type.
 *
 *  @note Must be called continuously until it returns NULL.
 *
 *  @param[in] game The game instance.
 *  @param[in] type The type from which to get the next variation.
 *  @param[out] var Filled in with the neutral tile variation's value.
 *  @return The tile variation's string.
 */
const char* get_next_game_tile_var(Game* game, int type, char* var);

/*! @brief Creates an entity texture reader from the game.
 *
 *  @param[in] game The game instance.
 *  @return Handle to the created entity texture reader.
 */
Entity_Texture_Reader* create_game_entity_texture_reader(Game* game);

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
unsigned char* read_game_entity_texture(
    Entity_Texture_Reader* reader,
    Entity_Kind kind,
    int type,
    int variation,
    int palette_variation,
    int* texture_width,
    int* texture_height
);

/*! @brief Frees a created entity texture reader.
 *
 *  @param[in] reader The entity texture reader to free.
 */
void free_game_entity_visuals_reader(Entity_Texture_Reader* reader);
