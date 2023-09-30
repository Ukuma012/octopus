#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "disk.h"
#include "common.h"

Pager* pager_open(const char* filename) {
    int fd;
    Pager* pager;

    if((fd = open(filename, O_RDWR | O_CREAT, S_IWUSR | S_IRUSR)) < 0) {
        fprintf(stderr, "malloc failed in pager_open");
        exit(1);
    }

    off_t file_length = lseek(fd, 0, SEEK_END);

    if((pager = malloc(sizeof(Pager))) == NULL) {
        fprintf(stderr, "malloc failed in pager_open");
        exit(1);
    }

    pager->fd = fd;
    pager->file_length = file_length;
    pager->num_of_pages = (file_length / PAGE_SIZE);

    if(file_length % PAGE_SIZE != 0) {
        fprintf(stderr, "DB file is not a whole number of pages. Mabe Corrupt file\n");
        exit(1);
    }

    for(uint32_t i = 0; i < TABLE_MAX_PAGES; i++) {
        pager->pages[i] = NULL;
    }

    return pager;
}

void* read_page(Pager* pager, uint32_t page_num) {
    if(page_num > TABLE_MAX_PAGES) {
        printf("Tried to fetch page number out of bounds. %d > %d\n", page_num, TABLE_MAX_PAGES);
        exit(1);
    }

    // Cache miss
    if(pager->pages[page_num] == NULL) {
        void* page;
        if((page = malloc(PAGE_SIZE)) == NULL) {
            fprintf(stderr, "malloc failed in get_page\n");
            exit(1);
        }
        uint32_t num_of_pages = pager->file_length / PAGE_SIZE;

        if(pager->file_length % PAGE_SIZE) {
            num_of_pages += 1;
        }

        if(page_num <= num_of_pages) {
            lseek(pager->fd, page_num * PAGE_SIZE, SEEK_SET);
            ssize_t bytes_read = read(pager->fd, page, PAGE_SIZE);
            if(bytes_read == -1) {
                fprintf(stderr, "Error reading file\n");
                exit(1);
            }
        }

        pager->pages[page_num] = page;

        if(page_num > pager->num_of_pages) {
            pager->num_of_pages = page_num + 1;
        }
    }

    return pager->pages[page_num];
}

uint32_t allocate_page(Pager* pager) {
    return pager->num_of_pages;
}

void write_page(Pager* pager, uint32_t page_num) {
    if (pager->pages[page_num] == NULL) {
        fprintf(stderr, "Tried to flush null page\n");
        exit(1);
    }

    off_t offset = lseek(pager->fd, page_num * PAGE_SIZE, SEEK_SET);
    if(offset == -1) {
        fprintf(stderr, "Error seeking in pager_flush\n");
        exit(1);
    }

    ssize_t bytes_written = write(pager->fd, pager->pages[page_num], PAGE_SIZE);
    if (bytes_written == -1) {
        fprintf(stderr, "Error writing in pager_flush\n");
        exit(1);
    }
}