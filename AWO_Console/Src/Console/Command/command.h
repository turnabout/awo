#pragma once

#include "Console/Command/command_descriptor.h"

typedef struct Command Command;

typedef enum Command_Ret_Val {
    CMD_Ret_Error  =  0,
    CMD_Ret_OK   =  1,
    CMD_Ret_Exit = -1,
} Command_Ret_Val;

/*! @brief Function held by a command.
 *
 *  @param[in] module_arg The module calling this command. Can be used to pass `Console` reference
 *  to the command's function.
 *  @param[in] payload List of arguments sent to the function, in the form of an array of generic
 *  pointers.
 *  @return Return value of the command function.
 */
typedef Command_Ret_Val (*Command_Function)(void* module_arg, void* payload[CMD_ARG_MAX_COUNT]);

Command* create_command(Command_Descriptor descriptor);

char* get_command_name(Command* command);
int get_command_arg_count(Command* command);

int load_command_arguments(Command* command, char* args_raw[CMD_ARG_MAX_COUNT]);

int execute_command_function(Command* command, void* module);

void free_command(Command* command);
