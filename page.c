#include <stdint.h>
#include "page.h"

#define PAGE_SIZE 4096

// Temporary number (id, username, email_address)
#define ROW_SIZE 293

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

const uint32_t LEAF_PAGE_KEY_SIZE = sizeof(uint32_t);
const uint32_t LEAF_PAGE_KEY_OFFSET = 0;
const uint32_t LEAF_PAGE_VALUE_SIZE = ROW_SIZE;
const uint32_t LEAF_PAGE_VALUE_OFFSET = LEAF_PAGE_KEY_OFFSET + LEAF_PAGE_KEY_SIZE;
const uint32_t LEAF_PAGE_CELL_SIZE = LEAF_PAGE_KEY_SIZE + LEAF_PAGE_VALUE_SIZE;
const uint32_t LEAF_PAGE_SPACE_FOR_CELLS = PAGE_SIZE - LEAF_PAGE_HEADER_SIZE;
const uint32_t LEAF_PAGE_MAX_CELLS = LEAF_PAGE_SPACE_FOR_CELLS / LEAF_PAGE_CELL_SIZE;