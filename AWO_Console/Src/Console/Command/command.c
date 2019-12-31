#include <stdlib.h>
#include <string.h>

#include "Utilities/utilities.h"
#include "Console/Command/command.h"

struct Command {

    // The name of this command.
    char name[CMD_NAME_MAX_LENGTH];

    // The count of commands.
    int arg_count;

    // The type of the command's arguments.
    Command_Arg_Type arg_types[CMD_ARG_MAX_COUNT];

    // The command's currently-loaded arguments, given to its function as a payload
    void* loaded_args[CMD_ARG_MAX_COUNT];

    // Function that should be called by this command.
    Command_Function function;

};

Command* create_command(Command_Descriptor descriptor)
{
    Command* command = malloc(sizeof(Command));

    if (command == NULL) {
        return NULL;
    }

    command->function = descriptor.function;

    // Set name
    strcpy_s(command->name, strlen(descriptor.name) + 1, descriptor.name);

    // Gather command argument data
    for (int i = 0; i < CMD_ARG_MAX_COUNT; i++) {
        if (descriptor.arg_types[i] == Command_Arg_None || i == CMD_ARG_MAX_COUNT) {
            command->arg_count = i;
            break;
        }

        command->arg_types[i] = descriptor.arg_types[i];
    }

    // Initialize all initially-loaded arguments to NULL
    for (int i = 0; i < CMD_ARG_MAX_COUNT; i++) {
        command->loaded_args[i] = NULL;
    }

    return command;
}

int load_command_arguments(Command* command, char* args_raw[CMD_ARG_MAX_COUNT])
{
    for (int i = 0; i < command->arg_count; i++) {

        // Free old argument if it exists
        if (command->loaded_args[i] != NULL) {
            free(command->loaded_args[i]);
            command->loaded_args[i] = NULL;
        }

        // Load new argument
        switch (command->arg_types[i]) {

        case Command_Arg_Int:

            // Validate raw string argument represents an integer
            if (!str_is_int(args_raw[i])) {
                return 0;
            }

            // Argument is an integer, store its integer value in a new pointer
            command->loaded_args[i] = malloc(sizeof(int));

            if (command->loaded_args[i] != NULL) {
                *((int*)command->loaded_args[i]) = atoi(args_raw[i]);
            }

            break;

        case Command_Arg_String:

            // Argument is a string, just copy the raw argument over
            command->loaded_args[i] = malloc( strlen(args_raw[i] + 1) );

            if (command->loaded_args[i] != NULL) {
                strcpy_s(
                    command->loaded_args[i], 
                    strlen(args_raw[i] + 1), 
                    args_raw[CMD_ARG_MAX_COUNT]
                );
            }

            break;
        }
    }

    return 1;
}

int execute_command_function(Command* command, void* module)
{
    return command->function(module, command->loaded_args);
}

char* get_command_name(Command* command)
{
    return command->name;
}

int get_command_arg_count(Command* command)
{
    return command->arg_count;
}

void free_command(Command* command)
{
    if (command == NULL) {
        return;
    }

    // Free loaded arguments
    for (int i = 0; i < command->arg_count; i++) {
        if (command->loaded_args[i] != NULL) {
            free(command->loaded_args[i]);
        }
    }

    free(command);
}