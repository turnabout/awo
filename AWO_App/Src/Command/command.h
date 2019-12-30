#pragma once

#define COMMAND_ARG_MAX_COUNT 3

typedef enum Command_Arg_Type {
    Command_Arg_None,
    Command_Arg_Number,
    Command_Arg_String,
} Command_Arg_Type;

typedef struct Command {

    // The name of this command.
    char* name;

    // The count of commands.
    int arg_count;

    // The type of the command's arguments.
    Command_Arg_Type arg_types[COMMAND_ARG_MAX_COUNT];

    // Function that should be called by this command.
    void* function;

} Command;

Command* create_command(
    const char* name,
    Command_Arg_Type arg_types[COMMAND_ARG_MAX_COUNT],
    void* function
);
