#pragma once

/*! @brief Module used to retrieve texture data for individual entities, with palettes applied.
 *  Can be used to get pixel data from AWO game entities.
 */
typedef struct Entity_Texture_Reader Entity_Texture_Reader;

/*! @brief Every existing kind of game entity.
 */
typedef enum Entity_Kind {

    // Neutral (non-property) tile
    Entity_Kind_Neutral_Tile,

    // Property tile
    Entity_Kind_Property,

    // Unit
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
// const char* get_next_game_tile_var(Game* game, int type, char* var);
