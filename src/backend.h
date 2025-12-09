#ifndef BACKEND_H
#define BACKEND_H

#include <stdbool.h>
#include <stdint.h>

void init_field(char *input, int64_t **ptr, int32_t *size, char *output);
bool step();

#endif
