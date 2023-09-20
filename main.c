#include <stdio.h>
#include <string.h>
#include "utils.h"

int main(int argc, char* argv[]) {
    InputBuffer* buffer = new_buffer();

    while(1) {
        prompt();
        read_cmd(buffer);

        if(strcmp(buffer->buffer, "exit") == 0) {
            printf("%s\n", "Bye");
            break;
        }
        
        printf("%s\n", buffer->buffer);
    }

    return 0;
}