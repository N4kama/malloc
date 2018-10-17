#ifndef SETUP_H
# define SETUP_H

#define _GNU_SOURCE

#include <string.h>
#include <stdint.h>
#include <sys/mman.h>

#include "size.h"

struct f_meta
{
    void *prev;
    void *next;
};

struct b_meta
{
    enum size size;
};

struct p_meta
{
    enum size size;
    void *f_list;
};


extern void *get_head(void);

#endif /* !SETUP_H */