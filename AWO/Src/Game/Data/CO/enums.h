#pragma once

#include "Utilities/macros.h"

#define FOREACH_CO_TYPE(CO) \
    CO(Andy) \
    CO(Max) \
    CO(Sami) \
    CO(Nell) \
    CO(Hachi) \
    CO(Olaf) \
    CO(Grit) \
    CO(Colin) \
    CO(Eagle) \
    CO(Drake) \
    CO(Jess) \
    CO(Kanbei) \
    CO(Sonja) \
    CO(Sensei) \
    CO(Flak) \
    CO(Adder) \
    CO(Lash) \
    CO(Hawke) \
    CO(Sturm) \

typedef enum {FOREACH_CO_TYPE(GENERATE_ENUM)} CO_Type;
static const char* co_type_str[] = {FOREACH_CO_TYPE(GENERATE_STRING)};