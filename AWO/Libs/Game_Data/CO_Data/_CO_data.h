#pragma once

#include "Game_Data/Headers/army_types.h"
#include "Game_Data/CO_Data/CO_data.h"
#include "Game_Data/Animation/animation.h"

typedef struct CO_Type_Data {

    // The CO's name.
    char* name;

    // The CO's army.
    Army_Type army;

    // The CO's frames source.
    Animation* frames;

} CO_Type_Data;

struct CO_Data {

    // Data for all COs.
    CO_Type_Data* COs[CO_COUNT];

};