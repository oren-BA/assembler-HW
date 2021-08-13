#include "BinaryCommand.h"

BinaryCommand *createCommand(enum CommandType t){
    BinaryCommand* command_ptr = malloc(sizeof(BinaryCommand));
    command_ptr->command = 0;
    command_ptr->mask = 0;
    command_ptr->type = t;
    return command_ptr;
}