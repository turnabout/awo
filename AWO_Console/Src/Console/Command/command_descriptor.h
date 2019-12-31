#pragma once

#define CMD_ARG_MAX_COUNT 3
#define MAX_CMD_COUNT 30
#define CMD_NAME_MAX_LENGTH 30

typedef enum Command_Arg_Type {
    Command_Arg_None,
    Command_Arg_Int,
    Command_Arg_String,
} Command_Arg_Type;

typedef struct Command_Descriptor {
    const char name[CMD_NAME_MAX_LENGTH];
    Command_Arg_Type arg_types[CMD_ARG_MAX_COUNT];
    void* function;
} Command_Descriptor;