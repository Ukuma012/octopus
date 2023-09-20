#include <stdio.h>
#include "utils.h"

int main(int argc, char* argv[]) {
    InputBuffer* buffer = new_buffer();

    while(1) {
        prompt();
        read_cmd(buffer);
        printf("%s\n", buffer->buffer);
    }
}