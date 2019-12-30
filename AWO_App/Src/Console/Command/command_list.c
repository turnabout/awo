#include <stdlib.h>
#include <c_hashmap.h>

#include "Console/Command/command_list.h"
#include "Console/Command/command.h"

#pragma warning(disable: 6011 )

typedef struct Command_List {

    // Hashmap containing every command.
    map_t commands;

} Command_List;

Command_List* create_commands_list(Command_Descriptor command_descriptors[MAX_CMD_COUNT])
{
    Command_List* list = malloc(sizeof(Command_List));

    list->commands = hashmap_new();

    for (int i = 0; i < MAX_CMD_COUNT; i++) {

        // Reached first non-command, stop
        if (command_descriptors[i].name[0] == '\0') {
            break;
        }

        Command* command = create_command(command_descriptors[i]);

        if (hashmap_put(list->commands, get_command_name(command), command) != MAP_OK) {
            free_command_list(list);
            return NULL;
        }

    }

    return list;
}

Command* get_command_by_name(Command_List* list, char* name)
{
    Command* command;

    if (hashmap_get(list->commands, name, (void**)(&command)) != MAP_OK) {
        return NULL;
    }

    return command;
}

int free_command_list_items(void* map, void* command)
{
    int res = hashmap_remove(map, get_command_name((Command*)command));

    if (res == MAP_OK) {
        free(command);
    }

    return res;
}

void free_command_list(Command_List* list)
{
    if (list == NULL) {
        return;
    }

    if (list->commands != NULL) {
        hashmap_iterate(list->commands, free_command_list_items, list->commands);
        hashmap_free(list->commands);
    }

    free(list);
}
