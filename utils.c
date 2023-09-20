#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void prompt() {
    printf("%s", "OCTOPUS >> ");
}

InputBuffer* new_buffer() {
    InputBuffer* inbuffer;
    if((inbuffer = calloc(1, sizeof(InputBuffer))) == NULL) {
        fprintf(stderr, "calloc faild\n");
        exit(1);
    }
    return  inbuffer;
}

void read_cmd(InputBuffer* inbuffer) {
    ssize_t n = getline(&(inbuffer->buffer), &(inbuffer->buffer_len), stdin);
    if (n < 0) {
        fprintf(stderr, "failed to read cmd\n");
        exit(1);
    }

    // remove a trailing newline
    inbuffer->input_len = n - 1;
    inbuffer->buffer[n - 1] = 0;
}