#pragma once

#include "Utilities/macros.h"

// COs enum
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

#define CO_FIRST Andy
#define CO_LAST Sturm
#define CO_COUNT CO_LAST + 1

// CO frame type enum
#define FOREACH_CO_FRAME_TYPE(FRAME_TYPE) \
    FRAME_TYPE(Body) \
    FRAME_TYPE(FaceNeutral) \
    FRAME_TYPE(FaceGood) \
    FRAME_TYPE(FaceBad) \

typedef enum {FOREACH_CO_FRAME_TYPE(GENERATE_ENUM)} CO_Frame_Type;
static const char* co_frame_type_str[] = {FOREACH_CO_FRAME_TYPE(GENERATE_STRING)};

#define CO_FRAME_TYPE_FIRST Body
#define CO_FRAME_TYPE_LAST FaceBad
#define CO_FRAME_TYPE_COUNT CO_LAST + 1
