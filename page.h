#ifndef PAGE_H
#define PAGE_H

#include <stdio.h>

typedef enum {
    PAGE_LEAF,
    PAGE_INTERNAL
} PageType;

void leaf_page_init(uint32_t);

#endif