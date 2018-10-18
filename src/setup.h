#ifndef SETUP_H
# define SETUP_H

#define _GNU_SOURCE

#define NB_SIZE 8

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
    void *unused;
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
    size_t count_sized_list;
};

void setup_f_list(void *f_list);
void allocate_new_page(struct p_meta *p_meta);
void create_page_meta(size_t size);
void *get_head(void);

#endif /* !SETUP_H */