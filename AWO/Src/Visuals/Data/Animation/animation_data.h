#pragma once
#include "conf.h"
#include "cJSON.h"

typedef struct Animation_Data Animation_Data;

/**
 *  \brief Creates and populates an Animation_Data struct using data from a cJSON animation array.
 *
 *  \param animation_json Pointer to the cJSON animation array.
 *
 *  \return Returns pointer to the allocated Animation_Data struct.
 */
Animation_Data* AD_create_from_JSON(const cJSON* animation_json);

/**
 *  \brief Destroys an Animation_Data's allocated memory.
 *
 *  \param animation_data Pointer to the allocated Animation_Data.
 */
void AD_free(Animation_Data* animation_data);

/**
 *  \brief Prints an Animation_Data's contents.
 *
 *  \param animation_data Pointer to the allocated Animation_Data.
 */
void AD_print(Animation_Data* animation_data);
