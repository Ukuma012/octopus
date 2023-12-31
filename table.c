#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "table.h"

const uint32_t ID_SIZE = size_of_attribute(Row, id);
const uint32_t USERNAME_SIZE = size_of_attribute(Row, username);
const uint32_t EMAIL_SIZE = size_of_attribute(Row, email);
const uint32_t ID_OFFSET = 0;
const uint32_t USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
const uint32_t EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_SIZE; 
const uint32_t ROW_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;

uint32_t get_row_size() {
    return ROW_SIZE;
}

void serialize_row(Row* source, void* dest) {
    memcpy(dest + ID_OFFSET, &(source->id), ID_SIZE);
    memcpy(dest + USERNAME_OFFSET, &(source->username), USERNAME_SIZE);
    memcpy(dest + EMAIL_OFFSET, &(source->email), EMAIL_SIZE);
}

void deserialize_row(void* source, Row* dest) {
    memcpy(&(dest->id), source + ID_OFFSET, ID_SIZE);
    memcpy(&(dest->username), source + USERNAME_OFFSET, USERNAME_SIZE);
    memcpy(&(dest->email), source + EMAIL_OFFSET, EMAIL_SIZE);
}

Table* db_open(const char* filename) {
    Pager* pager = pager_open(filename);

    Table* table;
    if((table = malloc(sizeof(Table))) == NULL) {
        fprintf(stderr, "malloc failed in db_open\n");
        exit(1);
    }

    table->pager = pager;
    table->root_page_num = 0;

    if(pager->num_of_pages == 0) {
        // New Database file
        printf("%s\n", "need to initialize new database");
    }

    return table;
}