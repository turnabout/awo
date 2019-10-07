#pragma once
#include "Utilities/macros.h"

// Unit Type
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

typedef enum {FOREACH_UNIT_TYPE(GENERATE_ENUM)} Unit_Type;
static const char* unit_type_str[] = {FOREACH_UNIT_TYPE(GENERATE_STRING)};

#define UNIT_TYPE_FIRST Infantry
#define UNIT_TYPE_LAST TransportCopter
#define UNIT_TYPE_COUNT UNIT_TYPE_LAST + 1

// Unit Variation
#define FOREACH_UNIT_VAR(UNITVAR) \
    UNITVAR(OS) \
    UNITVAR(BM) \
    UNITVAR(GE) \
    UNITVAR(YC) \
    UNITVAR(BH) \

typedef enum {FOREACH_UNIT_VAR(GENERATE_ENUM)} Unit_Var;
static const char* unit_var_str[] = {FOREACH_UNIT_VAR(GENERATE_STRING)};

#define UNIT_VAR_FIRST OS
#define UNIT_VAR_LAST BH
#define UNIT_VAR_COUNT UNIT_VAR_LAST + 1

// Unit Animation
#define FOREACH_UNIT_ANIM(UNITANIM) \
    UNITANIM(Idle) \
    UNITANIM(Right) \
    UNITANIM(Up) \
    UNITANIM(Down) \

typedef enum {FOREACH_UNIT_ANIM(GENERATE_ENUM)} Unit_Anim;
static const char* unit_anim_str[] = {FOREACH_UNIT_ANIM(GENERATE_STRING)};

#define UNIT_ANIM_FIRST Idle
#define UNIT_ANIM_LAST Down
#define UNIT_ANIM_COUNT UNIT_ANIM_LAST + 1
