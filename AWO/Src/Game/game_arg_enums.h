#pragma once

// Flags passed to game init function, decides game parameters along with which textures are 
// necessary to initialize.

// Decides which weathers will be included during game
typedef enum {
    Game_Arg_Clear = 1 << 0,
    Game_Arg_Snow  = 1 << 1,
    Game_Arg_Rain  = 1 << 2,
} Game_Arg_Weathers;
