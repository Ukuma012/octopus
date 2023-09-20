#ifndef UTILS_H
#define UTILS_H

#include <unistd.h>

typedef struct {
    char *buffer;
    size_t buffer_len;
    ssize_t input_len;
} InputBuffer;

void prompt();
InputBuffer* new_buffer();
void read_cmd(InputBuffer*);

#endif