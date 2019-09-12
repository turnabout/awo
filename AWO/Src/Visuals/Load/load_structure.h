#pragma once
#include "../visuals_structure.h"
#include "cJSON/cJSON.h"

/**
 *  \brief Populates and gets an Animation struct from a cJSON animation array.
 *
 *  \param anim_json Pointer to the cJSON animation array.
 *
 *  \return Returns pointer to the allocated Animation struct.
 *
 *  \sa init_game()
 */
Animation* get_anim(const cJSON* anim_json);

/**
 *  \brief Prints the contents of an animation.
 *
 *  \param game Pointer to the animation instance.
 *
 *  \sa print_anim_contents()
 */
void print_anim_contents(Animation* anim);
