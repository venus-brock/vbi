#ifndef BACKEND_H
#define BACKEND_H

#include <stdbool.h>
#include <stdint.h>

void init_field(char *input, int *counter, int64_t **ptr,
    unsigned int *size, char *output);
bool step();

#endif
