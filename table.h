#ifndef TABLE_H
#define TABLE_H

#include <stdint.h>
#include "pager.h"

#define COL_USERNAME_SIZE 32
#define COL_EMAIL_SIZE 255

#define size_of_attribute(Struct, Attribute) sizeof(((Struct *)0)->Attribute)

typedef struct {
    uint32_t id;
    char username[COL_USERNAME_SIZE + 1];
    char email[COL_EMAIL_SIZE + 1];
} Row;

typedef struct {
    Pager* pager;
    uint32_t root_page_num;
} Table;

uint32_t get_row_size();
void serialize_row(Row*, void*);
void deserialize_row(void*, Row*);
Table* db_open(const char*);

#endif