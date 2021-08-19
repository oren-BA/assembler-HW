#include <stdlib.h>
#include "BinaryCommand.h"

BinaryCommand *createBinary(size_t size, char* payload, char* mask){
    BinaryCommand* command_ptr = malloc(sizeof(BinaryCommand));
    command_ptr->payload = payload;
    command_ptr->mask = mask;
    command_ptr->size = size;
    return command_ptr;
}

void destroyBinary(BinaryCommand b){
    free(b.payload);
    free(b.mask);
}