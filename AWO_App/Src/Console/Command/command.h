#pragma once

#include "Console/Command/command_descriptor.h"

typedef struct Command Command;

Command* create_command(Command_Descriptor descriptor);

char* get_command_name(Command* command);
