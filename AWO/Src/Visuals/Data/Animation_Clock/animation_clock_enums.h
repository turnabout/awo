#pragma once

/**
 * \brief Enumeration for every possible animation clock.
 */
typedef enum {
    Sea_Clock,
    River_Clock,
    Units_Clock,

    // None
    No_Clock = -1,
} Animation_Clock_Index;

/**
 * \brief Enumeration for every possible animation sub clock.
 */
typedef enum {
    // Sea Clock
    Pyramid1 = 0,
    Pyramid2 = 1,
    Ten      = 2,

    // River Clock
    Eight    = 0,

    // None
    No_Sub_Clock = -1,
} Animation_Sub_Clock_Index;
