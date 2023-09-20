#include <stdio.h>
#include <string.h>
#include "utils.h"

int main(int argc, char* argv[]) {
    InputBuffer* input = new_buffer();

    while(1) {
        prompt();
        read_cmd(input);

        if(strcmp(input->buffer, "exit") == 0) {
            printf("%s\n", "Bye");
            break;
        }
        
        printf("%s\n", input->buffer);
    }

    return 0;
}