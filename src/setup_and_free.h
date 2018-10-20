#ifndef SETUP_AND_FREE_H
# define SETUP_AND_FREE_H

#define _GNU_SOURCE

#include <string.h>
#include <stdint.h>
#include <sys/mman.h>

#include "size.h"
#include "caster.h"

struct f_meta
{
    struct f_meta *prev;
    struct f_meta *next;
};

struct b_meta
{
    size_t size;
    struct b_meta *prev;
    struct b_meta *next;
    size_t nb_blk;
};

struct p_meta
{
    size_t size;
    struct b_meta *prev;
    struct b_meta *next;
    struct f_meta *f_list;
};

struct sized_f_list_meta
{
    size_t page_len;
    size_t count_sized_list;
};

void setup_f_list(void *f_list);
void new_free_ptr(struct p_meta *p_meta, struct f_meta *f_meta);
void *allocate_big_page(size_t size);
unsigned int allocate_new_page(struct p_meta *p_meta);
unsigned int create_page_meta(size_t size);
void *get_head(void);

#endif /* !SETUP_AND_FREE_H */