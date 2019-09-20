#pragma once
#include <stdarg.h>
#include <SDL.h>

#include "cJSON.h"

/**
 * \brief A node in a palette tree, holding data for a palette.
 */
typedef struct Palette_Node Palette_Tree;

/**
 *  \brief Generate an entire palette tree from one or multiple cJSON nodes holding a palette 
 *         object.
 *
 *  \param palettes_json The cJSON node(s) holding a palette object to add to the tree.
 *
 *  \return Returns the root node of the generated tree.
 */
Palette_Tree* PT_create_from_JSON(const cJSON* palettes_json, ...);

/**
 *  \brief Gets value in the given palette tree corresponding to the given key.
 *
 *  \param root The palette tree.
 *
 *  \param key The key of the node to find.
 *
 *  \return Returns the value associated with the given key. -1 if no value was found.
 */
Uint32 PT_get_value(Palette_Tree* tree, int key);

/**
 *  \brief Disposes of a palette tree.
 *
 *  \param root The palette tree's root node.
 */
void PT_free(Palette_Tree* tree);