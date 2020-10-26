====
TODO
====
Random dump of TODOs/notes I scribbled down.


AWO Data gen
================================================================================
* Rename Missiles -> Missile
* Organize weapon types separately in code & directories


AWO
================================================================================
Should we even have header files with Unit_Type enums, etc?
Or should we be gathering the unit type counts and stuff from the game data file 
instead?

Doing this would mean we can cut down on the amount of header files and access 
unit types, etc, the same way we do in C executable and in the web editor UI

* Use clang-format on entire project & integrate with clion
* Look into using valgrind with project/clion
* Perhaps it would make more sense to rename AWO directories:
    Internal -> Private
    Libs -> Public

* Remove the "Header" subdirectories, just place headers in the same dir



NOTES
================================================================================


For when we replace c_hashmap with hashmap.h
--------------------------------------------------------------------------------
https://github.com/sheredom/hashmap.h

// 
// START of External/hashmap.h (original hashmap.h should become hashmap_src.h)
// 
#pragma once

#include "hashmap_src.h"

// Additional definitions
typedef struct hashmap_s hashmap_s;
typedef struct hashmap_element_s hashmap_element_s;

#define map_t hashmap_s*

//
// END
//

Dependencies installation
--------------------------------------------------------------------------------

cJSON
--------------------------------------------------------------------------------
```
git clone https://github.com/DaveGamble/cJSON
mkdir build
cd build
cmake ..
make
make install
```

cglm
--------------------------------------------------------------------------------
```
git clone https://github.com/recp/cglm
mkdir build
cd build
cmake .. # [Optional] -DCGLM_SHARED=ON
make
sudo make install # [Optional]
sudo mkdir /usr/local/lib/cmake/cglm
sudo cp cglmConfig.cmake /usr/local/lib/cmake/cglm
```

freetype
--------------------------------------------------------------------------------

GLFW
--------------------------------------------------------------------------------

Glad
--------------------------------------------------------------------------------

