#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "utils.h"
#include "page.h"

const uint32_t ROW_SIZE = 293;

int main(int argc, char* argv[]) {
    InputBuffer* input = new_buffer();

    while(1) {
        prompt();
        read_cmd(input);

        if(strcmp(input->buffer, "exit") == 0) {
            printf("%s\n", "Bye");
            break;
        }
        
        leaf_page_init(ROW_SIZE);
        printf("%s\n", input->buffer);
    }

    return 0;
}