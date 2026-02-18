#ifndef BACKEND_H
#define BACKEND_H

#include <stdbool.h>
#include <stdint.h>

void init_field(char *input, int *counter, int64_t **ptr,
    unsigned int *size, char *output);
void set_inputs(char (*char_in)(void), int64_t (*int_in)(void));
bool step();

#define BLOCK_SIZE 256
#define PROG_W 80
#define PROG_H 25

#endif
