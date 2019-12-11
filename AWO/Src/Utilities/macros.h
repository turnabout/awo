#pragma once

// Macros for generating enums and enum strings
#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

// Macro for safely using pragmas specific to Visual Studio
#if defined(_MSC_VER)
#    define PRAGMA(PRAG) __pragma(PRAG)
#else
#    define PRAGMA(PRAG)
#endif

// Transforms a macro's value into a string
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
