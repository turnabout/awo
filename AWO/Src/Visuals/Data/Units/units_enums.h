#pragma once
#include "utils/macros.h"

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

typedef enum unit_type {FOREACH_UNIT_TYPE(GENERATE_ENUM)} unit_type;
static const char* unit_type_str[] = {FOREACH_UNIT_TYPE(GENERATE_STRING)};

#define UNIT_TYPE_FIRST Infantry
#define UNIT_TYPE_LAST TransportCopter
#define UNIT_TYPE_AMOUNT UNIT_TYPE_LAST + 1

// Unit Variation enum & strings
#define FOREACH_UNIT_VAR(UNITVAR) \
    UNITVAR(OS) \
    UNITVAR(BM) \
    UNITVAR(GE) \
    UNITVAR(YC) \
    UNITVAR(BH) \

typedef enum unit_var {FOREACH_UNIT_VAR(GENERATE_ENUM)} unit_var;
static const char* unit_var_str[] = {FOREACH_UNIT_VAR(GENERATE_STRING)};

#define UNIT_VAR_FIRST OS
#define UNIT_VAR_LAST BH
#define UNIT_VAR_AMOUNT UNIT_VAR_LAST + 1

// Unit Animation enum & strings
#define FOREACH_UNIT_ANIM(UNITANIM) \
    UNITANIM(Idle) \
    UNITANIM(Right) \
    UNITANIM(Up) \
    UNITANIM(Down) \
    UNITANIM(Done) \
    UNITANIM(Left) \

typedef enum unit_anim {FOREACH_UNIT_ANIM(GENERATE_ENUM)} unit_anim;
static const char* unit_anim_str[] = {FOREACH_UNIT_ANIM(GENERATE_STRING)};

#define UNIT_ANIM_FIRST Idle
#define UNIT_ANIM_LAST Down
#define UNIT_ANIM_AMOUNT UNIT_ANIM_LAST + 1

#define UNIT_ANIM_FULL_FIRST Idle
#define UNIT_ANIM_FULL_LAST Left
#define UNIT_ANIM_FULL_AMOUNT UNIT_ANIM_FULL_LAST + 1
