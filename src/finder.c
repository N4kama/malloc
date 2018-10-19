#include "finder.h"

size_t max_blk(struct b_meta *b_meta)
{
    //size of page 4096 minus sizeof metadata (32)
    size_t size = b_meta->size;
    size_t max = (4096 - sizeof(struct b_meta)) / size;
    return max;
}

struct b_meta *find_b_meta(void *ptr)
{
    uintptr_t addr = (uintptr_t)ptr;
    uintptr_t page_addr = get_page_addr(addr);
    void *tmp = (void *)page_addr;
    struct b_meta *res = tmp;
    return res;
}

unsigned int no_space_in_page(void *last_f_block)
{
    //No space in page if there is not enough space to put a new block
    struct f_meta *f_meta = last_f_block;
    struct b_meta *b_meta = find_b_meta(f_meta);
    size_t max = max_blk(b_meta);
    if (max == b_meta->nb_blk)
    {
	return 1;
    }
    return 0;
}

void update_free_ptr(struct p_meta *p_meta)
{
    void * f_list = p_meta->f_list;
    if (no_space_in_page(f_list))
    {
	p_meta->f_list = NULL;
    }
    else
    {
	struct f_meta *f_meta = p_meta->f_list;
	struct f_meta *new = NULL;
	if (f_meta->prev == f_meta)
	{
	    //Last ptr was the only one, the new one is also solo then
	    new = (struct f_meta *)((uintptr_t)f_meta + p_meta->size);
	    setup_f_list(new);
	}
	else
	{
	    new = f_meta->next;
	    f_meta->prev->next = new;
	    new->prev =f_meta->prev;
	}
	p_meta->f_list = new;
    }
}

struct p_meta *find_p_meta(size_t size)
{
    struct sized_f_list_meta *sized_l = get_head();
    struct p_meta *meta = caster(sized_l + 1);
    unsigned int i = 0;
    for (; i < sized_l->count_sized_list; i++)
    {
	if (meta->size == size)
	{
	    break;
	}
	meta += 1;
    }
    if (i == sized_l->count_sized_list)
    {
	create_page_meta(size);
    }
    return meta;
}

void update_nb_blk(void *ptr)
{
    struct b_meta *b_meta = find_b_meta(ptr);
    b_meta->nb_blk += 1;
}

void *get_free_space(struct p_meta *p_meta)
{
    if (!p_meta->f_list)
    {
	allocate_new_page(p_meta);
    }
    void *free_ptr = p_meta->f_list;
    update_nb_blk(free_ptr);
    update_free_ptr(p_meta);
    return free_ptr;
}