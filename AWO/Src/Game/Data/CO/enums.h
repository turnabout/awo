#pragma once

#include "Utilities/macros.h"

#define FOREACH_CO_TYPE(CO) \
    CO(Andy) \
    CO(Max) \
    CO(Sami) \
    CO(Olaf) \
    CO(Grit) \
    CO(Eagle) \
    CO(Drake) \
    CO(Kanbei) \
    CO(Sonja) \
    CO(Flak) \

typedef enum {FOREACH_CO_TYPE(GENERATE_ENUM)} CO_Type;
static const char* co_type_str[] = {FOREACH_CO_TYPE(GENERATE_STRING)};