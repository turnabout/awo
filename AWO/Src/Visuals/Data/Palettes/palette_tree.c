#include <stdio.h>
#include <stdlib.h>

#include "palette_tree.h"

int compare_p_node_keys(int left, int right)
{
    if (left > right)
        return 1;
    if (left < right)
        return -1;
    return 0;
}

Palette_Node* create_p_node(Uint32 key, Uint32 val)
{
    Palette_Node* new_node = (Palette_Node*)malloc(sizeof(Palette_Node));

    if (new_node == NULL) {
        printf("Error: Out of memory while creating palette node\n");
        exit(1);
    }

    new_node->key = key;
    new_node->val = val;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

Palette_Node* insert_p_node(Palette_Node* root, int key, int val)
{
    if (root == NULL) {
        root = create_p_node(key, val);
        return root;
    }

    int is_left = 0;
    int res = 0;
    Palette_Node* cursor = root;
    Palette_Node* prev = NULL;

    while (cursor != NULL) {
        prev = cursor;

        if ((res = compare_p_node_keys(key, cursor->key)) < 0) {
            is_left = 1;
            cursor = cursor->left;
        }
        else if (res > 0) {
            is_left = 0;
            cursor = cursor->right;
        }
        else {
            return root;
        }
    }

    if (is_left) {
        prev->left = create_p_node(key, val);
    }
    else {
        prev->right = create_p_node(key, val);
    }

    return root;
}

Uint32 get_p_node_val(Palette_Node* root, int key)
{
    if (root == NULL) {
        return -1;
    }

    int res;
    Palette_Node* cursor = root;

    while (cursor != NULL) {
        if ((res = compare_p_node_keys(key, cursor->key)) < 0) {
            cursor = cursor->left;
        }
        else if (res > 0) {
            cursor = cursor->right;
        }
        else {
            return cursor->val;
        }
    }

    return -1;
}

void dispose_p_tree(Palette_Node* root)
{
    if (root != NULL) {
        dispose_p_tree(root->left);
        dispose_p_tree(root->right);
        free(root);
    }
}

Palette_Node* generate_palette_tree(const cJSON* palette_json, ...)
{
    Palette_Node* palette_root = NULL;
    SDL_PixelFormat* mapping_format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
    va_list args_ptr;

    va_start(args_ptr, palette_json);

    while (palette_json->type == cJSON_Object) {
        const cJSON* palette_item_json;

        cJSON_ArrayForEach(palette_item_json, palette_json)
        {
            Uint32 color_key = SDL_atoi(palette_item_json->string);

            Uint32 color_val = SDL_MapRGBA(
                mapping_format, 
                cJSON_GetArrayItem(palette_item_json, 0)->valueint,
                cJSON_GetArrayItem(palette_item_json, 1)->valueint, 
                cJSON_GetArrayItem(palette_item_json, 2)->valueint, 
                0xFF
            );

            palette_root = insert_p_node(palette_root, color_key, color_val);
        }

        palette_json = va_arg(args_ptr, const cJSON*);
    }

    va_end(args_ptr);

    SDL_FreeFormat(mapping_format);
    return palette_root;
}
