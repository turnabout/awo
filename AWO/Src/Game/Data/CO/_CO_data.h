#pragma once

#include "Game/Data/CO/CO_data.h"
#include "Game/Data/Enums/army_type.h"
#include "Game/Data/Animation/Frame/frame.h"

typedef struct CO_Type_Data {

    // The CO's name.
    char* name;

    // The CO's army.
    Army_Type army;

    // The CO's frames source.
    Frame* frames[4];

} CO_Type_Data;

struct CO_Data {

    // Data for all COs.
    CO_Type_Data* COs[CO_Count];

};