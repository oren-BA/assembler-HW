#include <stdlib.h>
#include <memory.h>
#include "BinaryCommand.h"

BinaryCommand *createBinary(size_t size, char* payload){
    BinaryCommand* command_ptr = malloc(sizeof(BinaryCommand));
    command_ptr->payload = malloc(size);
    memcpy(command_ptr->payload, payload, size);
    command_ptr->size = size;
    return command_ptr;
}

void destroyBinary(BinaryCommand b){
    free(b.payload);
}