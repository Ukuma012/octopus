#ifndef DISK_H
#define DISK_H

#include <stdint.h>
#include "common.h"

typedef struct {
    int fd;
    uint32_t file_length;
    uint32_t num_of_pages;
    void* pages[TABLE_MAX_PAGES];
} Pager;

Pager* pager_open(const char*);
void* read_page(Pager*, uint32_t);
uint32_t allocate_page(Pager*);
void write_page(Pager*, uint32_t);

#endif