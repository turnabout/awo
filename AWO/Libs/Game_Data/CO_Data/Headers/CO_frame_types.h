#include "Utilities/utilities.h"

#define FOREACH_CO_FRAME_TYPE(FRAME_TYPE) \
    FRAME_TYPE(Body) \
    FRAME_TYPE(FaceNeutral) \
    FRAME_TYPE(FaceGood) \
    FRAME_TYPE(FaceBad) \

typedef enum {FOREACH_CO_FRAME_TYPE(GENERATE_ENUM)} CO_Frame_Type;
static const char* co_frame_type_str[] = {FOREACH_CO_FRAME_TYPE(GENERATE_STRING)};

#define CO_FRAME_TYPE_FIRST Body
#define CO_FRAME_TYPE_LAST FaceBad
#define CO_FRAME_TYPE_COUNT CO_FRAME_TYPE_LAST + 1
