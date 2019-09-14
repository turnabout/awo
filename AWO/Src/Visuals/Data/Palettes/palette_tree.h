#pragma once
#include <stdarg.h>
#include <SDL.h>
#include "../JSON/cJSON.h"

/**
 * \brief A node in a palette tree, holding data for a palette.
 */
typedef struct Palette_Node
{
    Uint32 key;
    Uint32 val;

    struct Palette_Node* left;
    struct Palette_Node* right;
} Palette_Node;

/**
 *  \brief Generate an entire palette tree from one or multiple cJSON nodes holding a palette 
 *         object.
 *
 *  \param palettes_json palettes_json The cJSON node(s) holding a palette object to add to the tree.
 *
 *  \return Returns the root node of the generated tree.
 */
Palette_Node* generate_palette_tree(const cJSON* palettes_json, ...);

/**
 *  \brief Searches for a node by key and retrieves its value.
 *
 *  \param root The palette tree's root node.
 *
 *  \param key The key of the node to find.
 *
 *  \return Returns the value associated with the given key. -1 if no value was found.
 */
Uint32 get_p_node_val(Palette_Node* root, int key);

/**
 *  \brief Disposes of a palette tree.
 *
 *  \param root The palette tree's root node.
 */
void dispose_p_tree(Palette_Node* root);