#pragma once

#include "Command/command_descriptor.h"
#include "Command/command.h"

typedef struct Command_List Command_List;

Command_List* create_commands_list(Command_Descriptor command_descriptors[MAX_CMD_COUNT]);

Command* get_command_by_name(Command_List* list, char* name);

void free_command_list(Command_List* list);