#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "page.h"
#include "common.h"

/**
 * Common Page Header Layout
 */
const uint32_t PAGE_TYPE_SIZE = sizeof(uint8_t);
const uint32_t PAGE_TYPE_OFFSET = 0;
const uint32_t IS_ROOT_SIZE = sizeof(uint8_t);
const uint32_t IS_ROOT_OFFSET = PAGE_TYPE_SIZE;
const uint32_t PARENT_POINTER_SIZE = sizeof(uint32_t);
const uint32_t PARENT_POINTER_OFFSET = PAGE_TYPE_OFFSET + IS_ROOT_SIZE;
const uint8_t COMMON_PAGE_HEADER_SIZE = PAGE_TYPE_SIZE + IS_ROOT_SIZE + PARENT_POINTER_SIZE;

void set_page_type(void* page, PageType type) {
    uint8_t value = type;
    *((uint8_t *)(page + PAGE_TYPE_OFFSET)) = value;
}

void set_page_root(void* page, bool is_root) {
    uint8_t value = is_root;
    *((uint8_t *)(page + IS_ROOT_OFFSET)) = value;
}

PageType get_page_type(void *page) {
    uint8_t value = *((uint8_t *)(page + PAGE_TYPE_OFFSET));
    return (PageType)value;
}

bool is_page_root(void* page) {
    uint8_t value = *((uint8_t *)(page + IS_ROOT_OFFSET));
    return (bool)value;
}

/* Common Page Header ends here*/
/* ----------------------------------------------------------------------------------------------------------------*/
/* Leaf Page starts here*/

/**
 * Leaf Page Header Layout
 */
const uint32_t LEAF_PAGE_NUM_CELLS_SIZE = sizeof(uint32_t);
const uint32_t LEAF_PAGE_NUM_CELLS_OFFSET = COMMON_PAGE_HEADER_SIZE;
const uint32_t LEAF_PAGE_NEXT_LEAF_SIZE = sizeof(uint32_t);
const uint32_t LEAF_PAGE_NEXT_LEAF_OFFSET = LEAF_PAGE_NUM_CELLS_OFFSET + LEAF_PAGE_NEXT_LEAF_SIZE;
const uint32_t LEAF_PAGE_HEADER_SIZE = COMMON_PAGE_HEADER_SIZE + LEAF_PAGE_NUM_CELLS_SIZE + LEAF_PAGE_NEXT_LEAF_SIZE;

/**
 * Leaf Page Body Layout
 */

uint32_t LEAF_PAGE_KEY_SIZE = sizeof(uint32_t);
uint32_t LEAF_PAGE_KEY_OFFSET = 0;
uint32_t LEAF_PAGE_VALUE_SIZE = 0;
uint32_t LEAF_PAGE_VALUE_OFFSET = 0;
uint32_t LEAF_PAGE_CELL_SIZE = 0;
uint32_t LEAF_PAGE_SPACE_FOR_CELLS = 0;
uint32_t LEAF_PAGE_MAX_CELLS = 0;

void leaf_page_init(uint32_t row_size)
{
    LEAF_PAGE_VALUE_SIZE = row_size;
    LEAF_PAGE_CELL_SIZE = LEAF_PAGE_KEY_SIZE + LEAF_PAGE_VALUE_SIZE;
    LEAF_PAGE_SPACE_FOR_CELLS = PAGE_SIZE - LEAF_PAGE_HEADER_SIZE;
    LEAF_PAGE_MAX_CELLS = LEAF_PAGE_SPACE_FOR_CELLS / LEAF_PAGE_CELL_SIZE;
}

uint32_t* leaf_page_num_cells(void* page) {
    return page + LEAF_PAGE_NUM_CELLS_OFFSET;
}

uint32_t* leaf_page_cell(void* page, uint32_t cell_num) {
    return page + LEAF_PAGE_HEADER_SIZE + cell_num * LEAF_PAGE_CELL_SIZE;
}

uint32_t* leaf_page_key(void* page, uint32_t cell_num) {
    return leaf_page_cell(page, cell_num);
}

void* leaf_page_value(void* page, uint32_t cell_num) {
    return leaf_page_cell(page, cell_num) + LEAF_PAGE_KEY_SIZE;
}

uint32_t* leaf_page_next_leaf(void* page) {
    return page + LEAF_PAGE_NEXT_LEAF_OFFSET;
}

/* Leaf Page ends here*/
/* ----------------------------------------------------------------------------------------------------------------*/
/* Internal Page starts here*/

/**
 * Internal Page Header Layout
 */
const uint32_t INTERNAL_PAGE_NUM_KEYS_SIZE = sizeof(uint32_t);
const uint32_t INTERNAL_PAGE_NUM_KEYS_OFFSET = COMMON_PAGE_HEADER_SIZE;
const uint32_t INTERNAL_PAGE_RIGHT_CHILD_SIZE = sizeof(uint32_t);
const uint32_t INTERNAL_PAGE_RIGHT_CHILD_OFFSET = INTERNAL_PAGE_NUM_KEYS_OFFSET + INTERNAL_PAGE_NUM_KEYS_SIZE;
const uint32_t INTERNAL_PAGE_HEADER_SIZE = COMMON_PAGE_HEADER_SIZE + INTERNAL_PAGE_NUM_KEYS_SIZE + INTERNAL_PAGE_RIGHT_CHILD_SIZE;

/**
 * Internal Page Body Layout
 */
const uint32_t INTERNAL_PAGE_CHILD_SIZE = sizeof(uint32_t);
const uint32_t INTERNAL_PAGE_KEY_SIZE = sizeof(uint32_t);
const uint32_t INTERNAL_PAGE_CELL_SIZE = INTERNAL_PAGE_CHILD_SIZE + INTERNAL_PAGE_KEY_SIZE;

uint32_t* internal_page_num_keys(void* page) {
    return page + INTERNAL_PAGE_NUM_KEYS_OFFSET;
}

uint32_t* internal_page_right_child(void* page) {
    return page + INTERNAL_PAGE_RIGHT_CHILD_OFFSET;
}

uint32_t* internal_page_cell(void* page, uint32_t cell_num) {
    return page + INTERNAL_PAGE_HEADER_SIZE + cell_num * INTERNAL_PAGE_CELL_SIZE;
}

uint32_t* internal_page_key(void* page, uint32_t key_num) {
    return internal_page_cell(page, key_num) + INTERNAL_PAGE_CHILD_SIZE;
}