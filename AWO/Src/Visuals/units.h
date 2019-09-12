#include "../utils/macros.h"

// Unit Type enum & strings
#define FOREACH_UNIT_TYPE(UNIT) \
    UNIT(Infantry) \
    UNIT(Mech) \
    UNIT(Recon) \
    UNIT(Tank) \
    UNIT(MdTank) \
    UNIT(NeoTank) \
    UNIT(APC) \
    UNIT(Artillery) \
    UNIT(Rockets) \
    UNIT(Missiles) \
    UNIT(AntiAir) \
    UNIT(Battleship) \
    UNIT(Cruiser) \
    UNIT(Lander) \
    UNIT(Sub) \
    UNIT(Fighter) \
    UNIT(Bomber) \
    UNIT(BattleCopter) \
    UNIT(TransportCopter) \

enum unit_type {FOREACH_UNIT_TYPE(GENERATE_ENUM)};
static const char* unit_type_str[] = {FOREACH_UNIT_TYPE(GENERATE_STRING)};

// Unit Variation enum & strings
#define FOREACH_UNIT_VAR(UNITVAR) \
    UNITVAR(OS) \
    UNITVAR(BM) \
    UNITVAR(GE) \
    UNITVAR(YC) \
    UNITVAR(BH) \

enum unit_var {FOREACH_UNIT_VAR(GENERATE_ENUM)};
static const char* unit_var_str[] = {FOREACH_UNIT_VAR(GENERATE_STRING)};

// Unit Animation enum & strings
#define FOREACH_UNIT_ANIM(UNITANIM) \
    UNITANIM(Idle) \
    UNITANIM(Right) \
    UNITANIM(Up) \
    UNITANIM(Down) \
    UNITANIM(Done) \
    UNITANIM(Left) \

enum unit_anim {FOREACH_UNIT_ANIM(GENERATE_ENUM)};
static const char* unit_anim_str[] = {FOREACH_UNIT_ANIM(GENERATE_STRING)};
