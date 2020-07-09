#pragma once

#include "macros.h"

#define FOREACH_UNIT_TYPE(UNIT_TYPE) \
    UNIT_TYPE(Infantry) \
    UNIT_TYPE(Mech) \
    UNIT_TYPE(Recon) \
    UNIT_TYPE(Tank) \
    UNIT_TYPE(MdTank) \
    UNIT_TYPE(NeoTank) \
    UNIT_TYPE(APC) \
    UNIT_TYPE(Artillery) \
    UNIT_TYPE(Rockets) \
    UNIT_TYPE(Missiles) \
    UNIT_TYPE(AntiAir) \
    UNIT_TYPE(Battleship) \
    UNIT_TYPE(Cruiser) \
    UNIT_TYPE(Lander) \
    UNIT_TYPE(Sub) \
    UNIT_TYPE(Fighter) \
    UNIT_TYPE(Bomber) \
    UNIT_TYPE(BattleCopter) \
    UNIT_TYPE(TransportCopter) \

typedef enum {FOREACH_UNIT_TYPE(GENERATE_ENUM)} Unit_Type;
static const char* unit_type_str[] = {FOREACH_UNIT_TYPE(GENERATE_STRING)};

#define UNIT_TYPE_FIRST Infantry
#define UNIT_TYPE_LAST TransportCopter
#define UNIT_TYPE_COUNT UNIT_TYPE_LAST + 1
