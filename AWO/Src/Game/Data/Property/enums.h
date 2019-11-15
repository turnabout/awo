#pragma once

#include "Utilities/macros.h"

// Property Type
#define FOREACH_PROPERTY_TYPE(PROPERTY_TYPE) \
    PROPERTY_TYPE(HQ) \
    PROPERTY_TYPE(City) \
    PROPERTY_TYPE(Base) \
    PROPERTY_TYPE(Airport) \
    PROPERTY_TYPE(Port) \

typedef enum {FOREACH_PROPERTY_TYPE(GENERATE_ENUM)} Property_Type;
static const char* property_type_str[] = {FOREACH_PROPERTY_TYPE(GENERATE_STRING)};

#define PROPERTY_TYPE_FIRST HQ
#define PROPERTY_TYPE_LAST Port
#define PROPERTY_TYPE_COUNT PROPERTY_TYPE_LAST + 1

// Property Weather Variations
#define FOREACH_PROPERTY_VARIATION(PROPERTY_VARIATION) \
    PROPERTY_VARIATION(Property_Clear) \
    PROPERTY_VARIATION(Property_Snow) \

typedef enum {FOREACH_PROPERTY_VARIATION(GENERATE_ENUM)} Property_Variation;
static const char* property_variation_str[] = {FOREACH_PROPERTY_VARIATION(GENERATE_STRING)};

#define PROPERTY_VARIATION_FIRST Property_Clear
#define PROPERTY_VARIATION_LAST  Property_Snow
#define PROPERTY_VARIATION_COUNT PROPERTY_VARIATION_LAST + 1
