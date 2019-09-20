#include "../JSON/cJSON.h"

typedef struct SS_Metadata SS_Metadata;


/**
 *  \brief Create a sprite sheet metadata object from a cJSON object.
 *
 *  \param json The cJSON node holding the metadata values.
 *
 *  \return Returns the created SS_Metadata object.
 */
SS_Metadata* SS_Meta_create_from_JSON(const cJSON* json);

/**
 *  \brief Free a sprite sheet metadata object.
 *
 *  \param palettes_json palettes_json The cJSON node holding the metadata values.
 *
 *  \return Returns the created SS_Metadata object.
 */
void SS_Meta_free(SS_Metadata* metadata);
